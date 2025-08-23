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

// Struct for historical price bars
struct HistoricalBar {
    std::string date;          
    double open         = 0.0;
    double high         = 0.0;
    double low          = 0.0;
    double close        = 0.0;
    double adjClose     = 0.0;
    std::uint64_t volume = 0;
    std::uint64_t unadjustedVolume = 0;
    double change       = 0.0;
    double changePercent = 0.0;
    double vwap         = 0.0;
    std::string label;        
    double changeOverTime = 0.0;
};

// Struct for analyst estimates (projections)
struct AnalystEstimates {
    std::string symbol;
    std::string date;
    double estimatedRevenueLow = 0.0;
    double estimatedRevenueHigh = 0.0;
    double estimatedRevenueAvg = 0.0;
    double estimatedEbitdaLow = 0.0;
    double estimatedEbitdaHigh = 0.0;
    double estimatedEbitdaAvg = 0.0;
    double estimatedEbitLow = 0.0;
    double estimatedEbitHigh = 0.0;
    double estimatedEbitAvg = 0.0;
    double estimatedNetIncomeLow = 0.0;
    double estimatedNetIncomeHigh = 0.0;
    double estimatedNetIncomeAvg = 0.0;
    double estimatedSgaExpenseLow = 0.0;
    double estimatedSgaExpenseHigh = 0.0;
    double estimatedSgaExpenseAvg = 0.0;
    double estimatedEpsAvg = 0.0;
    double estimatedEpsHigh = 0.0;
    double estimatedEpsLow = 0.0;
    int numberAnalystEstimatedRevenue = 0;
    int numberAnalystsEstimatedEps = 0;
};

// Security Interface
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

    // Historical time series
    std::vector<HistoricalBar> history;
    // Analyst estimates (projections)
    std::vector<AnalystEstimates> analystEstimates;

    void print();

    // Constructor that takes JSON for quote, history, and analyst estimates
    Security(std::string stock_quote, std::string stock_history, std::string analyst_estimates_json = "") {
        // Parse the string into json object
        json j = json::parse(stock_quote);

        if (!j.is_array() || j.empty() || !j[0].is_object()) {
            throw std::runtime_error("Unexpected Quote JSON shape");
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

        json* arr_ptr = nullptr;

        json h = json::parse(stock_history);
        if (!h.is_object()) {
            throw std::runtime_error("Unexpected history JSON shape");
        }

        if (h.contains("historical") && h["historical"].is_array()) {
            arr_ptr = &h["historical"];
        }

        json& arr = *arr_ptr;

        history.clear();
        history.reserve(arr.size());

        for (const auto& item : arr) {
            HistoricalBar b;
            b.date             = item.value("date", std::string{});
            b.open             = item.value("open", 0.0);
            b.high             = item.value("high", 0.0);
            b.low              = item.value("low", 0.0);
            b.close            = item.value("close", 0.0);
            b.adjClose         = item.value("adjClose", 0.0);
            b.volume           = item.value("volume", static_cast<std::uint64_t>(0));
            b.unadjustedVolume = item.value("unadjustedVolume", static_cast<std::uint64_t>(0));
            b.change           = item.value("change", 0.0);
            b.changePercent    = item.value("changePercent", 0.0);
            b.vwap             = item.value("vwap", 0.0);
            b.label            = item.value("label", std::string{});
            b.changeOverTime   = item.value("changeOverTime", 0.0);
            history.push_back(b);
        }

        // Parse analyst estimates if provided
        if (!analyst_estimates_json.empty()) {
            json ef = json::parse(analyst_estimates_json);
            if (ef.is_array()) {
                for (const auto& item : ef) {
                    AnalystEstimates est;
                    est.symbol = item.value("symbol", "");
                    est.date = item.value("date", "");
                    est.estimatedRevenueLow = item.value("estimatedRevenueLow", 0.0);
                    est.estimatedRevenueHigh = item.value("estimatedRevenueHigh", 0.0);
                    est.estimatedRevenueAvg = item.value("estimatedRevenueAvg", 0.0);
                    est.estimatedEbitdaLow = item.value("estimatedEbitdaLow", 0.0);
                    est.estimatedEbitdaHigh = item.value("estimatedEbitdaHigh", 0.0);
                    est.estimatedEbitdaAvg = item.value("estimatedEbitdaAvg", 0.0);
                    est.estimatedEbitLow = item.value("estimatedEbitLow", 0.0);
                    est.estimatedEbitHigh = item.value("estimatedEbitHigh", 0.0);
                    est.estimatedEbitAvg = item.value("estimatedEbitAvg", 0.0);
                    est.estimatedNetIncomeLow = item.value("estimatedNetIncomeLow", 0.0);
                    est.estimatedNetIncomeHigh = item.value("estimatedNetIncomeHigh", 0.0);
                    est.estimatedNetIncomeAvg = item.value("estimatedNetIncomeAvg", 0.0);
                    est.estimatedSgaExpenseLow = item.value("estimatedSgaExpenseLow", 0.0);
                    est.estimatedSgaExpenseHigh = item.value("estimatedSgaExpenseHigh", 0.0);
                    est.estimatedSgaExpenseAvg = item.value("estimatedSgaExpenseAvg", 0.0);
                    est.estimatedEpsAvg = item.value("estimatedEpsAvg", 0.0);
                    est.estimatedEpsHigh = item.value("estimatedEpsHigh", 0.0);
                    est.estimatedEpsLow = item.value("estimatedEpsLow", 0.0);
                    est.numberAnalystEstimatedRevenue = item.value("numberAnalystEstimatedRevenue", 0);
                    est.numberAnalystsEstimatedEps = item.value("numberAnalystsEstimatedEps", 0);
                    analystEstimates.push_back(est);
                }
            }
        }
    }
};

void Security::print() {
    std::cout << this->symbol << " :" << this->name << std::endl;
    std::cout << "history points: " << history.size() << "\n";
    if (!history.empty()) {
        const auto& last = history.back(); // last bar
        std::cout << "latest history:\n"
                  << "  date: " << last.date << "\n"
                  << "  open: " << last.open
                  << "  high: " << last.high
                  << "  low: "  << last.low
                  << "  close: " << last.close
                  << "  volume: " << last.volume << "\n";
    }
    if (!analystEstimates.empty()) {
        std::cout << "Analyst Estimates:\n";
        for (const auto& est : analystEstimates) {
            std::cout << "  Date: " << est.date
                      << "  EPS Avg: " << est.estimatedEpsAvg
                      << "  Revenue Avg: " << est.estimatedRevenueAvg
                      << "  Analysts (EPS): " << est.numberAnalystsEstimatedEps << "\n";
        }
    }
}

#endif //Security.h