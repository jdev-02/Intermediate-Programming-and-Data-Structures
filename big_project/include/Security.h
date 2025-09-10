#ifndef SECURITY_H
#define SECURITY_H
#include <string>
#include <iostream>
#include <list>  
#include <stdexcept> 
#include "Stock_info.h"
#include "json.hpp"

using json = nlohmann::json;

// ------------------------------------------------------
// File: Security.h
//
// Author: Jonathan Goohs, John Rolfe
//
// Description: Container class for information on each 
// company that was pulled down from the API. 
// ------------------------------------------------------

class Security {
public:
    std::string symbol;
    std::string name;
    double currentPrice;
    double eps;
    //double pe;                       
    double peRatio;
    double quarterlyDividendPerShare;
    double estimatedEPSAvg;

    void print();

    // Helper: robustly convert a json scalar (number or string) to double
    static double to_double(const json& x) {
        if (x.is_number_float() || x.is_number_integer() || x.is_number_unsigned()) {
            return x.get<double>();
        }
        if (x.is_string()) {
            const std::string& s = x.get_ref<const std::string&>();
            if (s.empty()) return 0.0;
            try {
                size_t pos = 0;
                double d = std::stod(s, &pos);
                return d;
            } catch (...) {
                return 0.0;
            }
        }
        return 0.0;
    }

    // Constructor that takes JSON for quote and analyst estimates
    Security(std::string ticker) {
        Stock_info si;
        std::list<std::string> stock_data = si.getStockInfo(ticker);

        if (stock_data.size() < 2) {
            throw std::runtime_error("Stock_info::getStockInfo() did not return both JSON blobs");
        }

        // If getStockInfo pushed {stock_quote, analyst_estimates_json} in that order:
        std::string analyst_estimates_json = stock_data.back(); 
        stock_data.pop_back();
        std::string stock_quote            = stock_data.back();     
        stock_data.pop_back();
    
        // ---- Quote ----
        json j = json::parse(stock_quote);
        if (!j.is_object()) {
            throw std::runtime_error("Unexpected Quote JSON shape (expected object)");
        }
        const auto& obj = j;

        symbol                       = obj["Symbol"].get<std::string>();
        name                         = obj["Name"].get<std::string>();
        currentPrice                 = to_double(obj["50DayMovingAverage"].get<std::string>());
        eps                          = to_double(obj["EPS"].get<std::string>());
        peRatio                      = to_double(obj["PERatio"].get<std::string>());
        quarterlyDividendPerShare    = to_double(obj["DividendPerShare"].get<std::string>());

        // ---- Analyst Estimates ----
        json je = json::parse(analyst_estimates_json);
        if (!je.is_object()) {
            throw std::runtime_error("Unexpected Analyst JSON shape (expected object)");
        }

        estimatedEPSAvg = 0.0; // default if nothing matches

        auto it = je.find("estimates");
        if (it != je.end() && it->is_array()) {
            for (const auto& e : *it) {
                if (!e.is_object()) continue;
                const std::string horizon = e.value("horizon", "");
                if (horizon == "current fiscal quarter") {
                    const auto& v = e["eps_estimate_average"];
                    if (!v.is_null()) {
                        estimatedEPSAvg = to_double(v);  
                    }
                    break; // stop at the first match
                }
            }
        }
    }
};

inline void Security::print() {
    std::cout << "----------------------------------------\n";
    std::cout << "Symbol:                     " << symbol << "\n";
    std::cout << "Name:                       " << name << "\n";
    std::cout << "Current Price:              " << currentPrice << "\n";
    std::cout << "Earnings per Share (EPS):   " << eps << "\n";
    std::cout << "P/E Ratio:                  " << peRatio << "\n";
    std::cout << "Quarterly Dividend/Share:   " << quarterlyDividendPerShare << "\n";
    std::cout << "Estimated EPS (Current Qtr):" << estimatedEPSAvg << "\n";
    std::cout << "----------------------------------------\n";
}

#endif // SECURITY_H
