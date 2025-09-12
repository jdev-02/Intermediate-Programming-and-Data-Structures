#ifndef STOCK_INFO_H   // If STOCK_INFO_H is not defined
#define STOCK_INFO_H   // Define STOCK_INFO_H

#include <iostream>
#include <string>
#include <curl/curl.h>
#include <unordered_map>
#include <ctime>
#include <list>
#include <fstream>
#include <filesystem>
#include "json.hpp"

//#define API_KEY "PYARh7MERk6CSX3WcbbwqzkbVYAu6XBD"
//#define API_KEY "g9C8KiSXIyPVKRu6rTM39qL3BxQDUKHR"
#define API_KEY "TWTLPDSLI1D8354E"
#define CACHE_TIME_OUT 10 * 24 * 60 * 60 // 10 days


// ------------------------------------------------------
// File: Stock_info.h
//
// Author: Jonathan Goohs, John Rolfe
//
// Description: Class Stock_info.h returns an instance of
// class Security that contains relevant ingformation.
// Method: Calling the API on given stock symbol, limited to 250 calls per day.
// Method: data is validated and parsed 
// ------------------------------------------------------

//Stock_Info Interface
class Stock_info
{

    public:
        //default constructor
        Stock_info(){};

        // Returns an instance of class Security
        std::list<std::string> getStockInfo(std::string symbol);

        // Method for printing the current cache
        void printCache() const;

    private:
        // A hashmap to act as a cache to limit API calls to 250 per day
        // keys are strings and values are json results from API
        std::unordered_map<std::string, std::string> cache_quotes;
        std::unordered_map<std::string, std::string> cache_eps_forecast;

        // Persistent cache (shared across instances)
        struct CacheEntry {
            std::string quote;
            std::string eps_forecast;
            std::time_t timestamp{}; // seconds since epoch
        };

        inline static std::unordered_map<std::string, CacheEntry> s_pcache; // symbol -> entry
        inline static bool s_cache_loaded = false;
        inline static const char* s_cache_file = "stock_cache.json";
        inline static const std::time_t s_max_age_seconds = CACHE_TIME_OUT;

        // Helper: load persistent cache from disk once
        static void load_persistent_cache() {
            if (s_cache_loaded) return;
            s_cache_loaded = true;
            std::ifstream in(s_cache_file);
            if (!in.good()) return; // nothing to load
            try {
                nlohmann::json j;
                in >> j;
                if (!j.is_object()) return;
                for (auto it = j.begin(); it != j.end(); ++it) {
                    if (!it.value().is_object()) continue;
                    CacheEntry e{};
                    const auto& o = it.value();
                    if (o.contains("quote") && o["quote"].is_string()) e.quote = o["quote"].get<std::string>();
                    if (o.contains("eps_forecast") && o["eps_forecast"].is_string()) e.eps_forecast = o["eps_forecast"].get<std::string>();
                    if (o.contains("timestamp") && (o["timestamp"].is_number_integer() || o["timestamp"].is_number_unsigned()))
                        e.timestamp = static_cast<std::time_t>(o["timestamp"].get<long long>());
                    if (!it.key().empty()) {
                        s_pcache[it.key()] = std::move(e);
                    }
                }
            } catch (...) {
                
            }
        }

        // Helper: save persistent cache to disk
        static void save_persistent_cache() {
            nlohmann::json j = nlohmann::json::object();
            for (const auto& [sym, e] : s_pcache) {
                j[sym] = {
                    {"quote", e.quote},
                    {"eps_forecast", e.eps_forecast},
                    {"timestamp", static_cast<long long>(e.timestamp)}
                };
            }
            std::ofstream out(s_cache_file);
            if (out.good()) {
                out << j.dump(2);
            }
        }

        static bool is_fresh(const CacheEntry& e) {
            const std::time_t now = std::time(nullptr);
            if (e.timestamp == 0) return false;
            return (now - e.timestamp) <= s_max_age_seconds;
        }

        //Methods for calling the API
        std::string get_quote(std::string symbol, std::string apiKey);
        std::string get_eps_forecast(std::string symbol, std::string apiKey);
};


// Callback to capture the API response, returns size of data written
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
    size_t newLength = size * nmemb;
    try {
        s->append((char*)contents, newLength);
    } catch (std::bad_alloc& e) {
        return 0;
    }
    return newLength;
}

std::string Stock_info::get_quote(std::string symbol, std::string apiKey){
    //Fetch with libcurl
    CURL* curl;
    CURLcode res;
    std::string readBuffer;
    

    std::string url = "https://www.alphavantage.co/query?function=OVERVIEW&symbol=" + symbol + "&apikey=" + apiKey;

    curl_global_init(CURL_GLOBAL_DEFAULT); //initialize libcurl

    curl = curl_easy_init(); //makes curl handle
    if (!curl) {
        std::cerr << "curl_easy_init() failed\n";
        curl_global_cleanup();
        return std::string(); // empty on failure
    }

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); //set url for curl
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback); //set callback for writing data from http response to the function
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer); //sets the data to write to the buffer which points to the string stored by writecallback
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); //follows any redirects set up by the host server
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "stock-info/1.0"); //sets the user agents coming from us to the server

    res = curl_easy_perform(curl);

    long http_status = 0;
    CURLcode info_res = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_status);
    if (info_res != CURLE_OK) {
        std::cerr << "curl_easy_getinfo() failed: " << curl_easy_strerror(info_res) << "\n";
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        return std::string();
    }

    curl_easy_cleanup(curl);
    curl_global_cleanup();

    if (res != CURLE_OK) {
        std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << "\n";
        return std::string();
    }
    if (http_status < 200 || http_status >= 300) {
        std::cerr << "HTTP error: " << http_status << "\n";
        return std::string();
    }

    // No direct persistent update here; handled by getStockInfo
    return readBuffer;
}

std::string Stock_info::get_eps_forecast(std::string symbol, std::string apiKey){
    //Fetch with libcurl
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    std::string url = "https://www.alphavantage.co/query?function=EARNINGS_ESTIMATES&symbol=" + symbol + "&apikey=" + apiKey;

    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();
    if (!curl) {
        std::cerr << "curl_easy_init() failed\n";
        curl_global_cleanup();
        return std::string(); // empty on failure
    }

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); //set url for curl
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "stock-info/1.0");

    res = curl_easy_perform(curl);

    long http_status = 0;
    CURLcode info_res = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_status);
    if (info_res != CURLE_OK) {
        std::cerr << "curl_easy_getinfo() failed: " << curl_easy_strerror(info_res) << "\n";
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        return std::string();
    }

    curl_easy_cleanup(curl);
    curl_global_cleanup();

    if (res != CURLE_OK) {
        std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << "\n";
        return std::string();
    }
    if (http_status < 200 || http_status >= 300) {
        std::cerr << "HTTP error: " << http_status << "\n";
        return std::string();
    }

    // No direct persistent update here; handled by getStockInfo
    return readBuffer;
}

std::list<std::string> Stock_info::getStockInfo(std::string symbol) {
    std::list<std::string> retList;

    // Ensure persistent cache is loaded
    load_persistent_cache();

    // Check persistent cache first
    if (auto it = s_pcache.find(symbol); it != s_pcache.end()) {
        const CacheEntry& e = it->second;
        if (is_fresh(e) && !e.quote.empty() && !e.eps_forecast.empty()) {
            retList.push_back(e.quote);
            retList.push_back(e.eps_forecast);
            return retList;
        }
    }

    // Otherwise fetch fresh data
    std::string apiKey = API_KEY;
    std::string stock_quote = get_quote(symbol, apiKey);
    std::string eps_forecast = get_eps_forecast(symbol, apiKey);

    // If fetch succeeded, update persistent cache and return
    if (!stock_quote.empty() && !eps_forecast.empty()) {
        CacheEntry e;
        e.quote = stock_quote;
        e.eps_forecast = eps_forecast;
        e.timestamp = std::time(nullptr);
        s_pcache[symbol] = std::move(e);
        save_persistent_cache();

        retList.push_back(stock_quote);
        retList.push_back(eps_forecast);
        return retList;
    }

    // If fetch failed but we have any cached data (even stale), use it as fallback
    if (auto it = s_pcache.find(symbol); it != s_pcache.end()) {
        const CacheEntry& e = it->second;
        if (!e.quote.empty() && !e.eps_forecast.empty()) {
            retList.push_back(e.quote);
            retList.push_back(e.eps_forecast);
            return retList;
        }
    }
    // NO VALID RETURN VALUE FOUND
    retList.push_back(stock_quote);
    retList.push_back(eps_forecast);
    return retList;
}


void Stock_info::printCache() const {
    
    // Print persistent cache summary
    const std::time_t now = std::time(nullptr);
    for (const auto& [sym, e] : s_pcache) {
        std::cout << sym << " => {Age: " << (now - e.timestamp)/(24.0 * 60.0 * 60.0) << " days"
                  << ", quote_len: " << e.quote.size()
                  << ", eps_len: " << e.eps_forecast.size() << "}\n";
    }
}

#endif // STOCK_INFO_H
