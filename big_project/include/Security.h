#ifndef SECURITY_H   // If SECURITY_H is not defined
#define SECURITY_H   // Define SECURITY_H
#include <string>
#include <iostream>
#include "json.hpp"

using json = nlohmann::json;

// ------------------------------------------------------
// File: Security.h
//
// Author: Jonathan Goohs, John Rolfe
//
// Description: Container class for information on each 
// company that was pulled down from the API. 
// 
// ------------------------------------------------------

//Security Interface
class Security {
public:
    std::string symbol;
    std::string name;
    double price;
    double changesPercentage;
    double change;
    double dayLow;
    double dayHigh;
    double yearHigh;
    double yearLow;
    long long marketCap;
    double priceAvg50;
    double priceAvg200;
    std::string exchange;
    long long volume;
    long long avgVolume;
    double open;
    double previousClose;
    double eps;
    double pe;
    std::string earningsAnnouncement;
    long long sharesOutstanding;
    long long timestamp;
    std::string history;

    void print();

    // Constructor that takes JSON
    Security(std::string stock_quote,std::string stock_history) {
        //Parse the string into json object
        json j = json::parse(stock_quote);
 
        if (!j.is_array() || j.empty() || !j[0].is_object()) {
            throw std::runtime_error("Unexpected JSON shape");
        }

        const auto& obj = j[0];

        symbol               = obj.value("symbol", "");
        name                 = obj.value("name", "");
        price                = obj.value("price", 0.0);
        changesPercentage    = obj.value("changesPercentage", 0.0);
        change               = obj.value("change", 0.0);
        dayLow               = obj.value("dayLow", 0.0);
        dayHigh              = obj.value("dayHigh", 0.0);
        yearHigh             = obj.value("yearHigh", 0.0);
        yearLow              = obj.value("yearLow", 0.0);
        marketCap            = obj.value("marketCap", 0LL);
        priceAvg50           = obj.value("priceAvg50", 0.0);
        priceAvg200          = obj.value("priceAvg200", 0.0);
        exchange             = obj.value("exchange", "");
        volume               = obj.value("volume", 0LL);
        avgVolume            = obj.value("avgVolume", 0LL);
        open                 = obj.value("open", 0.0);
        previousClose        = obj.value("previousClose", 0.0);
        eps                  = obj.value("eps", 0.0);
        pe                   = obj.value("pe", 0.0);
        earningsAnnouncement = obj.value("earningsAnnouncement", std::string{});
        sharesOutstanding    = obj.value("sharesOutstanding", 0LL);
        timestamp            = obj.value("timestamp", 0LL);

        history              =stock_history;
    }
};

void Security::print(){
    std::cout << this->symbol << " :" << this->name << std::endl;
    std::cout << this->history <<std::endl;
}

#endif //Security.h