#ifndef STOCK_INFO_H   // If STOCK_INFO_H is not defined
#define STOCK_INFO_H   // Define STOCK_INFO_H

#include <iostream>
#include <string>
#include <curl/curl.h>
#include <unordered_map>
#include <ctime>
#include "Security.h"


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
        //is there a reason we have two public sections? and do we want a blank constructor?
        public:
            // Returns an instance of class Security
            Security getStockInfo(std::string symbol);

            // Method for printing the current cache
            void printCache() const;

        private:
            // A hashmap to act as a cache to limit API calls to 250 per day
            // keys are strings and values are json results from API
            std::unordered_map<std::string, std::string> cache_quotes;
            std::unordered_map<std::string, std::string> cache_history;
            std::unordered_map<std::string, std::string> cache_eps_forecast;

            //Methods for calling the API
            std::string get_quote(std::string symbol, std::string apiKey);
            std::string get_history(std::string symbol, std::string apiKey);
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
    

    std::string url = "https://financialmodelingprep.com/api/v3/quote/" + symbol + "?apikey=" + apiKey;

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

    //Cache and return
    cache_quotes.emplace(symbol, readBuffer);
    return readBuffer;
}

std::string Stock_info::get_history(std::string symbol, std::string apiKey){
    //Fetch with libcurl
    CURL* curl;
    CURLcode res;
    std::string readBuffer;
    int numDays = 365*10;

    std::string url = "https://financialmodelingprep.com/api/v3/historical-price-full/" + symbol +
    "?timeseries=" + std::to_string(numDays) + "&apikey=" + apiKey;

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

    //Cache and return
    cache_history.emplace(symbol, readBuffer);
    return readBuffer;
    
}

std::string Stock_info::get_eps_forecast(std::string symbol, std::string apiKey){
    //Fetch with libcurl
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    std::string url = "https://financialmodelingprep.com/api/v3/forecast/" + symbol + "?apikey=" + apiKey;

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

    //Cache and return
    cache_eps_forecast.emplace(symbol, readBuffer);
    return readBuffer;
}

Security Stock_info::getStockInfo(std::string symbol) {
    if (auto it = cache_quotes.find(symbol); it != cache_quotes.end()) {
        return Security(cache_quotes[symbol], cache_history[symbol], cache_eps_forecast[symbol]);
    }

    std::string apiKey = "PYARh7MERk6CSX3WcbbwqzkbVYAu6XBD";
    std::string stock_quote = get_quote(symbol, apiKey);
    std::string stock_history = get_history(symbol, apiKey);
    std::string eps_forecast = get_eps_forecast(symbol, apiKey);

    return Security(stock_quote, stock_history, eps_forecast);
}


void Stock_info::printCache() const {
    //prints the current cache which is full of json strings of symbol and their associated data)
    for (const auto& [sym, json] : cache_quotes) {
        std::cout << sym << " => " << json << "\n";
    }
}

#endif // STOCK_INFO_H
