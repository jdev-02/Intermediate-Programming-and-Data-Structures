/*
User_info Module:
•	Parse data from user
•	Read in and store stock ticker as key and an instance of the class Security as the value (where each field responsible for calculating the users selected investment calculation is populated either by cache or api upon instantiation)
•	Portfolio management and user data storage
•	Calculation orchestration
•	Interface between GUI and data processing modules
o	Logic for something like peter lynch peg - undervalued, > 1.0 = overvalued X% of users stocks are undervalued/overvalued based on this metric. (use the value from math library method)
*/

#include <iostream>
#include <string>
#include <map>
#include "../include/Stock_info.h"
#include "../include/Security.h"
#include "..include/Math.h"

using namespace std;

class User_info {
private:
	string username; //input from user
	map<string, Security> portfolio; //map of stock ticker to security instance
	InvestorMath math; //instance of math class to do calculations on user's portfolio
	int share_count; //number of shares for each stock in portfolio
	int cost_basis; //cost basis (average) for each stock in portfolio
	int total_investment; //multiply sharecount by cost basis for each stock
	int time_horizon; //input from user for investment time horizon (short (2-3 years), medium (4-7 years), long (8+ years
public:
	User_info(string user) : username(user), share_count(0), cost_basis(0), total_investment(0) {}
	//constructor for user_info class (based on the username input from the user)
	//then we add methods to populate the portfolio map and do calculations based on input

	void add_stock(string ticker, Security symbol, int shares, int basis) {
		//this medthod adds a stock to the user's portfolio so we can do calcs on it
		portfolio[ticker] = symbol;
		share_count += shares;
		cost_basis += basis;
		total_investment += shares * basis;
	}
	void calc_portfolio_current_value() {
		//this method calcs the current value of users portfolio
		double current_value = 0.0;
		for (Securrity& security : portfolio) {
			current_value += security.price * share_count; //price is a field in Security class from security.h
		}
		cout << "Current value of portfolio: $" << current_value << endl; //call this in the gui 
	}
	void calc_peterLynchPEG() {
		//this method is used if user picks peter lynch PEG calculation (growth at resonable price)

		double epsGrowthRateTotal = 0.0;
		double peRatioTotal = 0.0;
		double currentPriceTotal = 0.0;
		for (Security& security : portfolio) {
			epsGrowthRatetotal += security.eps; //eps is field in security class from security.h
			peRatioTotal += security.pe; //pe is field in security class from security.h
			currentPriceTotal += security.price; //price is field in security class from security.h
		}
		cout << "Peter Lynch PEG value for this current portfolio is: $"
			<< math.peterLynchPEG(epsgrowthRatetotal, peRatioTotal, currentPriceTotal) << endl;
		//call this ins the gui and then use the starting value and ending value to draw the trend line
		cout << "Peter Lynch PEG value for portfolio in " << time_horizon << "years: $"
			<< math.peterLynchPEG(epsgrowthRatetotal, peRatioTotal, currentPriceTotal) * time_horizon << endl; 
	}
	void calc_benjaminGrahamInstrinsicValue() {
		//this method is used if user picks benjamin graham instrinsic value calculation (deep value investing)
		double epsTotal = 0.0;
		double expectedGrowthRateTotal = 0.0;
		for (Security& security : portfolio) {
			epstotal += security.eps;
			expectedGrowthRatetotal += security.estimatedEPSAvg; //this is a field in analyst estimates struct in security.h
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
		for (Security& security : portfolio) {
			annualDividendTotal += security.eps * 0.5; //assuming 50% payout ratio for simplicity
			requiredRateofReturnTotal += 0.07; //assuming 7% required rate of return for simplicity
			dividendGrowthRatetotal += security.estimatedEPSAvg * 0.1; //assuming 10% growth rate for simplicity
		}
		cout << "Dividend Discount Model value for this current portfolio is: $"
			<< math.dividendDiscountModel(annualDividendTotal, requiredRateofReturnTotal, dividendGrowthRateTotal) << endl;
		//call this ins the gui and then use the starting value and ending value to draw the trend line
		cout << "Dividend Discount Model value for portfolio in " << time_horizon << "years: $"
			<< math.dividendDiscountModel(annualDividendTotal, requiredRateofReturnTotal, dividendGrowthRateTotal) * time_horizon << endl;
	}
};