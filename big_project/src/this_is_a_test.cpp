#include "../include/Stock_info.h"
#include "../include/Security.h"
#include "../include/Math.h"

int main() {
    Stock_info s;

    Security aapl = Security("AAPL");   // Apple
    Security msft = Security("MSFT");   // Microsoft
    Security nvda = Security("NVDA");   // NVIDIA
    Security googl = Security("GOOGL"); // Alphabet (Class A)
    Security goog = Security("GOOG");   // Alphabet (Class C)
    Security amzn = Security("AMZN");   // Amazon
    Security meta = Security("META");   // Meta Platforms
    Security llnl = Security("LLY");    // Eli Lilly
    Security tsla = Security("TSLA");   // Tesla


    // Print each security
    aapl.print();
    msft.print();
    nvda.print();
    googl.print();
    goog.print();
    amzn.print();
    meta.print();
    llnl.print();
    tsla.print();


    // Print the cache at the end
    s.printCache();

    return 0;
}