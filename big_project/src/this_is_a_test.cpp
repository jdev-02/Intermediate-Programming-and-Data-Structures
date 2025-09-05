#include "../include/Stock_info.h"
#include "../include/Security.h"
#include "../include/Math.h"
#include "../include/user_info.h"

int main() {
     Stock_info s;
     Security aapl = Security("AAPL");
     aapl.print();

     User_info my_info = User_info("my_user"); 
     return 0;
}