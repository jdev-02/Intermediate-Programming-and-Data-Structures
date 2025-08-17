#include <iostream>
#include <string>
#include <curl/curl.h>
#include <unordered_map>

// ------------------------------------------------------
// File: Stock_info.h
//
// Author: John Rolfe
//
// Description: Class Stock_info.h returns an instance of
// class Security that contains relevant ingformation.
// 
// ------------------------------------------------------

//Queue Interface
class Stock_info
{

    public:
        //default constructor
        Stock_info(){};

        public:
            // Returns an instance of class Security
            //** TODO After creating class Security change from returning string
            std::string getStockInfo(std::string symbol);


            // Method for printing the current cache
            void printCache() const;

        private:
            // A hashmap to act as a cache to limit API calls 
            // keys are strings and values are integers
            std::unordered_map<std::string, std::string> cache;




};


// Callback to capture the API response 
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
    size_t newLength = size * nmemb;
    try {
        s->append((char*)contents, newLength);
    } catch (std::bad_alloc& e) {
        return 0;
    }
    return newLength;
}

std::string Stock_info::getStockInfo(std::string symbol){

    //chck if present in cache
    if (auto it = cache.find(symbol); it != cache.end()) {
        return it->second;
    }

    //Fetch with libcurl
    CURL* curl;
    CURLcode res;
    std::string readBuffer;
    std::string apiKey = "PYARh7MERk6CSX3WcbbwqzkbVYAu6XBD"; // API key is good for 250 calls per day

    std::string url = "https://financialmodelingprep.com/api/v3/quote/" + symbol + "?apikey=" + apiKey;

    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();
    if (!curl) {
        std::cerr << "curl_easy_init() failed\n";
        curl_global_cleanup();
        return std::string(); // empty on failure
    }

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "stock-info/1.0");

    res = curl_easy_perform(curl);

    long http_status = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_status);

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
    cache.emplace(symbol, readBuffer);
    return readBuffer;
}

void Stock_info::printCache() const {
    for (const auto& [sym, json] : cache) {
        std::cout << sym << " => " << json << "\n";
    }
}
