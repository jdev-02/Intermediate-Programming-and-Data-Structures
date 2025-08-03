#include <iostream>
#include <string>
#include <curl/curl.h>

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

int main() {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;
    std::string apiKey = "PYARh7MERk6CSX3WcbbwqzkbVYAu6XBD"; // API key is good for 250 calls per day

    std::string symbol = "AAPL";
    std::string url = "https://site.financialmodelingprep.com/api/v3/quote/" + symbol + "?apikey=" + apiKey;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK)
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        else {
            // Write JSON response to a file

        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return 0;
}
