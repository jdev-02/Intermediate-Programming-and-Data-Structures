#pragma once

#ifndef USER_INFO_H
#define USER_INFO_H
/*
User_info Module:
�	Parse data from user
�	Read in and store stock ticker as key and an instance of the class Security as the value (where each field responsible for calculating the users selected investment calculation is populated either by cache or api upon instantiation)
�	Portfolio management and user data storage
�	Calculation orchestration
�	Interface between GUI and data processing modules
o	Logic for something like peter lynch peg - undervalued, > 1.0 = overvalued X% of users stocks are undervalued/overvalued based on this metric. (use the value from math library method)
*/

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>
#include "../include/Stock_info.h"
#include "../include/Security.h"
#include "../include/Math.h"

#define QUARTERLY_DIVIDEND_MULT 4
#define CSV_BUF 4096


using namespace std;

class User_info {
private:
	string username; //input from user
	string ticker;
	map<string, FinancialInstrument*> portfolio; //map of stock ticker to security instance
	InvestorMath math; //instance of math class to do calculations on user's portfolio
	map<string, int> shareCount; //number of shares for each stock in portfolio
	map<string, double> costBasis; //cost basis (average) for each stock in portfolio
	int investment_value; //multiply sharecount by cost basis for each stock
	int time_horizon; //input from user for investment time horizon (short (2-3 years), medium (4-7 years), long (8+ years)
public:
	char csvInputBuffer[CSV_BUF] = {};

	User_info(string user) : username(user), ticker(""), investment_value(0), time_horizon(0) {}
	//constructor for user_info class (based on the username input from the user)
	//then we add methods to populate the portfolio map and do calculations based on input
	~User_info() {
		//clean up all allocated FinancialInstrument objects
		for (auto& pair : portfolio) {
			delete pair.second;
		}
	}

	void setUName(string user) {
		username = user;
	}

	void parseCSV(GUI &gui) {
		//this method will take the validated csv input from the user (from GUI) and parse it into the data members of this class in order to do calcs
		//the csvInputBuffer is a char array in GUI, already validated and loaded by the GUI class
		istringstream requestUserInput(string(gui.csvInputBuffer)); //convert char array to string and then to istringstream for line parsing
		string line;
		while (getline(requestUserInput, line)) {
			stringstream ss(line); //string stream from current line
			string cell;
			vector<string> parsedRow;
			while (getline(ss, cell, ',')) { //for each cell in the row sepaated by commas
				cell.erase(remove_if(cell.begin(), cell.end(), ::isspace), cell.end()); //remove whitespace from each cell
				parsedRow.push_back(cell); //push each cell from the row into a vector
			}
			//now that we have vectors of each row, we can populate the data members of class - ticker shares owned and cost basis
			if (parsedRow.size() < 3) continue; //skip incomplete rows, should not happen bc validated in gui class
			string ticker = parsedRow[0];
			int share_count = stoi(parsedRow[1]);
			double cost_basis = stod(parsedRow[2]);
			Security symbol(ticker); //instantiate security class which will call api and populate fields from security.h class
			//add the stock to the user's portfolio using the add_stock method
			add_stock(ticker, symbol, share_count, cost_basis);
		}
	}

	void add_stock(string ticker, FinancialInstrument* symbol, int shares, double basis) {
		//this medthod adds a stock to the user's portfolio so we can do calcs on it
		portfolio[ticker] = symbol;
		shareCount[ticker] = shares;
		costBasis[ticker] = basis;
	}
	double calc_portfolio_current_value() {
		//this method calcs the current value of users portfolio
		double current_value = 0.0;
		for (auto& sets : portfolio) {
			current_value += sets.second.currentPrice * shareCount[sets.first]; //price is a field in Security class from security.h
		}
		return current_value;
	}
	void calc_peterLynchPEG() {
		//this method is used if user picks peter lynch PEG calculation (growth at resonable price)

		double epsGrowthRateTotal = 0.0;
		double peRatioTotal = 0.0;
		double currentPriceTotal = 0.0;
		for (auto& set : portfolio) {
			epsGrowthRateTotal += set.second.eps; //eps is field in security class from security.h
			peRatioTotal += set.second.peRatio; //pe is field in security class from security.h
			currentPriceTotal += set.second.currentPrice; //price is field in security class from security.h
		}
		cout << "Peter Lynch PEG value for this current portfolio is: $"
			<< math.peterLynchPEG(epsGrowthRateTotal, peRatioTotal, currentPriceTotal) << endl;
		//call this ins the gui and then use the starting value and ending value to draw the trend line
		cout << "Peter Lynch PEG value for portfolio in " << time_horizon << "years: $"
			<< math.peterLynchPEG(epsGrowthRateTotal, peRatioTotal, currentPriceTotal) * time_horizon << endl; 
	}
	void calc_benjaminGrahamInstrinsicValue() {
		//this method is used if user picks benjamin graham instrinsic value calculation (deep value investing)
		double epsTotal = 0.0;
		double expectedGrowthRateTotal = 0.0;
		for (auto& set : portfolio) {
			epsTotal += set.second.eps;
			expectedGrowthRateTotal += set.second.estimatedEPSAvg; //this is a field in analyst estimates struct in security.h
		}
		cout << "Benjamin Graham Intrinsic value for this current portfolio is: $"
			<< math.benjaminGrahamIntrinsicValue(epsTotal, expectedGrowthRateTotal) << endl;
		//call this ins the gui and then use the starting value and ending value to draw the trend line
		cout << "Benjamin Graham Intrinsic value for portfolio in " << time_horizon << "years: $"
			<< math.benjaminGrahamIntrinsicValue(epsTotal, expectedGrowthRateTotal) * time_horizon << endl;
	}
	void calc_dividendDiscountModel() {
		//this method is used if user picks dividend discount model calculation (income investing)
		double annualDividendTotal = 0.0;
		double requiredRateofReturnTotal = 0.0;
		double dividendGrowthRateTotal = 0.0;
		for (auto& set : portfolio) {
			//API pulls quarterly dividend, multiply by 4 to get annual dividend per share
			double annualDividendPerShare = set.second.quarterlyDividendPerShare * QUARTERLY_DIVIDEND_MULT;

			//Calculate total annual dividend for user's share count in this security
			annualDividendTotal += annualDividendPerShare * shareCount[set.first];

			//alternative calculation using EPS and payout ratio (assuming 50% payout ratio for simplicity)
			// This line calculates estimated annual dividend based on earnings
			double estimatedAnnualDividend = set.second.eps * 0.5 * shareCount[set.first];
			//note: You might want to use this as a comparison or fallback if annualDividendPerShare is not available

			requiredRateofReturnTotal += 0.07; //assuming 7% required rate of return for simplicity
			dividendGrowthRateTotal += set.second.estimatedEPSAvg * 0.1; //assuming 10% growth rate for simplicity
		}
		cout << "Dividend Discount Model value for this current portfolio is: $"
			<< math.dividendDiscountModel(annualDividendTotal, requiredRateofReturnTotal, dividendGrowthRateTotal) << endl;
		//call this ins the gui and then use the starting value and ending value to draw the trend line
		cout << "Dividend Discount Model value for portfolio in " << time_horizon << "years: $"
			<< math.dividendDiscountModel(annualDividendTotal, requiredRateofReturnTotal, dividendGrowthRateTotal) * time_horizon << endl;
	}	
	
};

#endif

