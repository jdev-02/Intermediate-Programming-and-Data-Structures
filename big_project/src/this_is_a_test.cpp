#include "Stock_info.h"

int main() {
     Stock_info s;
     std::string aapl = s.getStockInfo("AAPL");
     std::cout << "AAPL: " << aapl << "\n";
     s.printCache();
     return 0;
}