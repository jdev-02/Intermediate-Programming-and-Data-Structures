#include <gtest/gtest.h>
#include <string>
#include "Security.h"



// ----------------------- Tests -----------------------

TEST(Security, ParsesData_TEST) {

    // Uses the constructor that accepts raw JSON strings
    Security fakeSec("AAPL");

    EXPECT_EQ(fakeSec.symbol, "AAPL");
    EXPECT_EQ(fakeSec.name, "Apple Inc");

}




int main(int argc, char* argv[]){

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();


}

