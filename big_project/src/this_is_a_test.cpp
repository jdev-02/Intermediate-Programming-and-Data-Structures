#include "../big_project/include/Stock_info.h"
#include "../big_project/include/Security.h"


int main() {
     Stock_info s;
     Security aapl = s.getStockInfo("AAPL");
     aapl.print();
     return 0;
}