#include "Stock_info.h"
#include "Security.h"


int main() {
     Stock_info s;
     Security aapl = s.getStockInfo("AAPL");
     aapl.print();
     s.printCache();
     return 0;
}