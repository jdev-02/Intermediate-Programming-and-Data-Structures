#ifndef MATH_H
#define MATH_H

#include <iostream>
#include "Security.h"
#define ERRVAL -1
using namespace std;

// ------------------------------------------------------
//File: math.h
//
//Author: Jonathan Goohs, John Rolfe
//
//Description: Math.h contains eligible custom calcualtions from popular
//investors, including Peter Lynch's PEG ratio fair value calculation,
// benjhamin grahams intrinsic value calculation, and teh dividend
//  discount model of stock value
// ----------------------------------------------------

//Math Interface
class InvestorMath
{
private:
	double epsGrowthRate;
	double peRatio;
	double currentPrice;
	double eps;
	double expectedGrowthRate;
	double annualDividend;
	double requiredRateofReturn;
	double dividendGrowthRate;

public:
	InvestorMath() {};
	double peterLynchPEG(double epsGrowthRate, double peRatio, double currentPrice);
	double benjaminGrahamIntrinsicValue(double eps, double expectedGrowthRate);
	double dividendDiscountModel(double annualDividend, double requiredRateofReturn, double  dividendGrowthRate);
};

double InvestorMath::peterLynchPEG(double epsGrowthRate, double peRatio, double currentPrice) {
	if (epsGrowthRate <= 0) {
		cerr << "Error: EPS growth rate must be greater than 0. May be an API error, please try again." << endl;
		return ERRVAL;
	}	return (epsGrowthRate / peRatio) * currentPrice;
}

double InvestorMath::benjaminGrahamIntrinsicValue(double eps, double expectedGrowthRate) {
	if (eps <= 0) {
		cerr << "Error: EPS must be greater than 0. May be an API error, please try again." << endl;
		return ERRVAL;
	}
	return (eps * (8.5 + 2 * expectedGrowthRate));
}

double InvestorMath::dividendDiscountModel(double annualDividend, double requiredRateofReturn, double dividendGrowthRate) {
	if (requiredRateofReturn <= dividendGrowthRate) {
		cerr << "Error: Required rate of return must be greater than dividend growth rate." << endl;
		return -1;
	}
	return (annualDividend / requiredRateofReturn - dividendGrowthRate);
}

#endif