#ifndef SECURITY_H
#define SECURITY_H
#include <string>
#include <iostream>
#include <list>  
#include <stdexcept> 
#include "Stock_info.h"
#include "json.hpp"

using json = nlohmann::json;

//--------------------------------------------------------
// File: Security.h
//
//Author: Jonathan Goohs, John Rolfe
//
// Defines a polymorphic base class (FinancialInstrument) and a concrete
// equity-like Security that pulls fields from Alpha Vantage JSON
//( via Stock_info) and exposes simple accessors.
//------------------------------------------------------

// ============================================================================
// Base: FinancialInstrument
// A minimal polymorphic interface for financial instruments (equity, etc.).
// ============================================================================
class FinancialInstrument {
public:
    virtual ~FinancialInstrument() = default; 
    
    //Print a human-readable summary. Must not modify object state.
    virtual void print() const = 0;

    //Instrument symbol/ticker (implementation-defined).
    virtual std::string getSymbol() const = 0;

    //return Human-readable instrument name.
    virtual std::string getName() const = 0;
};

// ============================================================================
// Derived: Security
// A concrete instrument populated from Alpha Vantage "OVERVIEW" and
// "EARNINGS_ESTIMATES" responses.
// ============================================================================
class Security: public FinancialInstrument {
public:
    std::string symbol;
    std::string name;
    double currentPrice;
    double eps;                       
    double peRatio;
    double quarterlyDividendPerShare;
    double estimatedEPSAvg;

    void print() const override;

    //Helper: robustly convert a json scalar (number or string) to double
    static double to_double(const json& x);



     // Constructs a Security by fetching and parsing Alpha Vantage JSON.
     //
     // Steps:
     //  1) Calls Stock_info::getStockInfo(ticker) which returns two JSON strings:
     //     - back()           => analyst_estimates_json ("EARNINGS_ESTIMATES")
     //     - second-from-back => stock_quote           ("OVERVIEW")
     //  2) Parses "OVERVIEW" object fields:
     //     - "Symbol", "Name" (std::string)
     //     - "50DayMovingAverage", "EPS", "PERatio", "DividendPerShare" (numbers / strings)
     //  3) Parses "EARNINGS_ESTIMATES" to extract the first estimate whose
     //     "horizon" equals "current fiscal quarter" and reads "eps_estimate_average".
     //
     // Throws:
     //  - std::runtime_error if either JSON blob is missing or of unexpected shape.
     //
    Security(std::string ticker); 
   
    //Simple getters
    std::string getSymbol() const override { return symbol; }
    std::string getName()   const override { return name;   }

private:
    // Validate the OVERVIEW (quote) JSON shape and required fields.
    // Requires an object with string fields: "Symbol" and "Name".
    static void validate_quote_json(const json& obj) {
        if (!obj.is_object()) {
            throw std::invalid_argument("Quote JSON is not an object");
        }
        if (!obj.contains("Symbol") || !obj.at("Symbol").is_string()) {
            throw std::invalid_argument("Quote JSON missing string field: Symbol");
        }
        if (!obj.contains("Name") || !obj.at("Name").is_string()) {
            throw std::invalid_argument("Quote JSON missing string field: Name");
        }
        // Numeric-like fields are optional; if present they must be string or number
        auto check_num_like = [&](const char* k) {
            if (!obj.contains(k)) return;
            const json& v = obj.at(k);
            if (!(v.is_string() || v.is_number())) {
                throw std::invalid_argument(std::string("Quote JSON field has invalid type: ") + k);
            }
        };
        check_num_like("50DayMovingAverage");
        check_num_like("EPS");
        check_num_like("PERatio");
        check_num_like("DividendPerShare");
    }

    // Validate the EARNINGS_ESTIMATES JSON shape (object; optional array field "estimates").
    static void validate_estimates_json(const json& obj) {
        if (!obj.is_object()) {
            throw std::invalid_argument("Estimates JSON is not an object");
        }
        auto it = obj.find("estimates");
        if (it != obj.end() && !it->is_array()) {
            throw std::invalid_argument("Estimates JSON: 'estimates' must be an array if present");
        }
    }


};

inline void Security::print() const{
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

Security::Security(std::string ticker) {
        // Fetch both JSON payloads
        Stock_info si;
        std::list<std::string> stock_data = si.getStockInfo(ticker);

        if (stock_data.size() < 2) {
            throw std::runtime_error("Stock_info::getStockInfo() did not return both JSON blobs");
        }

        //If getStockInfo pushed {stock_quote, analyst_estimates_json} in that order:
        std::string analyst_estimates_json = stock_data.back(); 
        stock_data.pop_back();
        std::string stock_quote            = stock_data.back();     
        stock_data.pop_back();

    
        // -----------------------------
        // Parse OVERVIEW (company info)
        // -----------------------------
        json j = json::parse(stock_quote);
        if (!j.is_object()) {
            throw std::runtime_error("Unexpected Quote JSON shape (expected object)");
        }
        const auto& obj = j;

        // Validate required/optional fields before accessing.
        validate_quote_json(obj);

        symbol = obj.at("Symbol").get<std::string>();
        name   = obj.at("Name").get<std::string>();
        currentPrice              = obj.contains("50DayMovingAverage") ? to_double(obj.at("50DayMovingAverage")) : 0.0;
        eps                       = obj.contains("EPS")               ? to_double(obj.at("EPS"))               : 0.0;
        peRatio                   = obj.contains("PERatio")           ? to_double(obj.at("PERatio"))           : 0.0;
        quarterlyDividendPerShare = obj.contains("DividendPerShare")   ? to_double(obj.at("DividendPerShare"))   : 0.0;

        // ---------------------------------------
        // Parse EARNINGS_ESTIMATES (analyst data)
        // ---------------------------------------
        json je = json::parse(analyst_estimates_json);
        if (!je.is_object()) {
            throw std::runtime_error("Unexpected Analyst JSON shape (expected object)");
        }
        validate_estimates_json(je);

        estimatedEPSAvg = 0.0; //default if nothing matches

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
                    break; //stop at the first match
                }
            }
        }
 
    }


    double Security::to_double(const json& x) {
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
#endif //SECURITY_H
