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
#include <format>
#include <sstream>
#include <iomanip>
#include "../include/Stock_info.h"
#include "../include/Security.h"
#include "../include/Math.h"

#define QUARTERLY_DIVIDEND_MULT 4
#define CSV_BUF 4096


using namespace std;

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
#define ASSUMED_ROR 0.07
#define MAXROWELEMENTS 3


using namespace std;

class User_info {
private:
	string username; //input from user
	string ticker;
	map<string, Security > portfolio; //map of stock ticker to security instance
	InvestorMath math; //instance of math class to do calculations on user's portfolio
	map<string, int> shareCount; //number of shares for each stock in portfolio
	map<string, double> costBasis; //cost basis (average) for each stock in portfolio
	int investment_value; //multiply sharecount by cost basis for each stock
	int time_horizon; //input from user for investment time horizon (short (2-3 years), medium (4-7 years), long (8+ years)
public:
	char csvInputBuffer[CSV_BUF] = {};
	double rate_of_return = ASSUMED_ROR; // Assumed value

	User_info(string user) : username(user), ticker(""), investment_value(0), time_horizon(0) {}
	//constructor for user_info class (based on the username input from the user)
	//then we add methods to populate the portfolio map and do calculations based on input

	
	void setUName(string user) {
		username = user;
	}

	void parseCSV(const std::string& csvData) {
		//this method will take the validated csv input from the user (from GUI) and parse it into the data members of this class in order to do calcs
		//csvData is provided by the GUI after validation
		istringstream requestUserInput(csvData); //convert provided string to istringstream for line parsing
		string line;
		while (getline(requestUserInput, line)) {
			stringstream ss(line); //string stream from current line
			string cell;
			vector<string> parsedRow;
			while (getline(ss, cell, ',')) { //for each cell in the row sepaated by commas
				cell.erase(remove_if(cell.begin(), cell.end(),::isspace), cell.end()); //remove whitespace from each cell
				parsedRow.push_back(cell); //push each cell from the row into a vector
			}
			//now that we have vectors of each row, we can populate the data members of class - ticker shares owned and cost basis
			if (parsedRow.size() < MAXROWELEMENTS) continue; //skip incomplete rows, should not happen bc validated in gui class
			string ticker = parsedRow[0];
			int share_count = stoi(parsedRow[1]);
			double cost_basis = stod(parsedRow[2]);
			Security symbol(ticker); //instantiate security class which will call api and populate fields from security.h class
			//add the stock to the user's portfolio using the add_stock method
			add_stock(ticker, symbol, share_count, cost_basis);
		}
	}

	void add_stock(string ticker, Security symbol, int shares, double basis) {
		//this medthod adds a stock to the user's portfolio so we can do calcs on it
		portfolio.insert_or_assign(ticker, symbol);
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
	string calc_peterLynchPEG() {
		//this method is used if user picks peter lynch PEG calculation (growth at resonable price)

		double epsGrowthRateTotal = 0.0;
		double peRatioTotal = 0.0;
		double currentPriceTotal = 0.0;
		double lynchVal;
		int countunder = 0;
		string retString;
		for (auto& set : portfolio) {
			epsGrowthRateTotal += set.second.eps; //eps is field in security class from security.h
			peRatioTotal += set.second.peRatio; //pe is field in security class from security.h
			currentPriceTotal += set.second.currentPrice; //price is field in security class from security.h
			lynchVal = math.peterLynchPEG(set.second.eps,set.second.peRatio,set.second.currentPrice);
			if (lynchVal < 1.0 ) {
				retString += set.second.name; retString += " is undervalued.\n";
				countunder++;
			} else {
				retString += set.second.name; retString += " is overvalued.\n";
			}
		}
		retString += std::to_string((countunder/portfolio.size()*100));
		retString += '%';
		retString += " are undervalued stocks in your portfolio.\n";
		retString += "Peter Lynch PEG ratio value for this current portfolio is: " 
    		+ std::to_string(math.peterLynchPEG(epsGrowthRateTotal/portfolio.size(), peRatioTotal/portfolio.size(), currentPriceTotal/portfolio.size())) 
    		+ "\nThis metric is mostly useless but fun to see applied to an entire portfolio.\n";
		return retString;
	}

string calc_benjaminGrahamInstrinsicValue() {
	//this method is used if user picks benjamin graham intrinsic value calculation (deep value investing)
	
	if (portfolio.empty()) return "No holdings.\n"; //portfolio should never be empty bc the analysis cant be run on an empty input

	double totalIV = 0.0;
	int countunder = 0;
	string retString;
	std::ostringstream oss;
	string tempString;
	
	for (auto& set : portfolio) {
		double eps = set.second.eps; //eps is field in security class from security.h
		double g = set.second.estimatedEPSAvg; //analyst estimates field in security class from security.h
		
		//convert decimal to percent if needed (assuming estimatedEPSAvg comes as decimal like 0.079 for 7.9%)
		if (g > 0.0 && g < 1.0) g *= 100.0;
		
		double grahamVal = math.benjaminGrahamIntrinsicValue(eps, g);
		totalIV += grahamVal;
		
		oss << " intrinsic value: $" << std::fixed << std::setprecision(2) << grahamVal
    	<< " vs current price: $" << set.second.currentPrice;

		tempString = oss.str();
		oss.str(""); 
		oss.clear();
		retString += set.second.name + tempString;
		if (grahamVal > set.second.currentPrice) {
			retString += " - undervalued.\n";
			countunder++;
		} else {
			retString += " - overvalued.\n";
		}
	}

	//Fix integer division issue by casting to double
	double pctUnder = 100.0 * static_cast<double>(countunder) / static_cast<double>(portfolio.size());
	retString += std::to_string(static_cast<int>(pctUnder));
	retString += '%';
	retString += " are undervalued stocks in your portfolio.\n";

	oss << "Benjamin Graham intrinsic value (sum across holdings): $"  << std::fixed << std::setprecision(2) << totalIV
    	<< "\nThis metric provides a conservative estimate of stock value based on earnings and growth.\n";

	tempString = oss.str();
	retString += tempString;
	return retString;
}

	string calc_dividendDiscountModel() {
		//this method is used if user picks dividend discount model calculation (income investing)

		double annualDividendTotal = 0.0;
		double requiredRateofReturnTotal = 0.0;
		double dividendGrowthRateTotal = 0.0;
		double ddmVal;
		int countunder = 0;
		string retString;
		for (auto& set : portfolio) {
			double annualDividendPerShare = set.second.quarterlyDividendPerShare * QUARTERLY_DIVIDEND_MULT; //quarterly dividend field in security class from security.h
			annualDividendTotal += annualDividendPerShare * shareCount[set.first]; //total dividend dollars for portfolio
			requiredRateofReturnTotal += rate_of_return; //assumed rate of return
			dividendGrowthRateTotal += 4.0/100.0; //assumed dividend growth rate
			ddmVal = math.dividendDiscountModel(annualDividendPerShare, rate_of_return, 4.0/100.0);
			retString += set.second.name + " DDM value: $" + std::to_string(ddmVal) + " vs current price: $" + std::to_string(set.second.currentPrice);
			if (ddmVal > set.second.currentPrice) {
				retString += " - undervalued.\n";
				countunder++;
			} else {
				retString += " - overvalued.\n";
			}
		}
		retString += std::to_string((countunder/portfolio.size()*100));
		retString += '%';
		retString += " are undervalued stocks in your portfolio.\n";
		retString += "Dividend Discount Model with an assumed 4% dividend growth rate for this current portfolio is: $" 
			+ std::to_string(math.dividendDiscountModel(annualDividendTotal, requiredRateofReturnTotal/portfolio.size(), dividendGrowthRateTotal/portfolio.size())) 
			+ "\nThis metric values the entire portfolio based on expected future dividend payments.\n";
		
		return retString;
	}
};

#endif
