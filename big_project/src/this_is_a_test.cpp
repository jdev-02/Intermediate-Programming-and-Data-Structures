#include "../include/Stock_info.h"
#include "../include/Security.h"
#include "../include/Math.h"

int main() {
     Stock_info s;
     Security aapl = s.getStockInfo("AAPL");
     aapl.print();
     return 0;
}