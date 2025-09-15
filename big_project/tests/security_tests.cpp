#include <gtest/gtest.h>
#include <string>
#include <fstream>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <list>
#include "Security.h"
#include "Stock_info.h"
#include "json.hpp"
#include "user_info.h"

using json = nlohmann::json;

TEST(StockInfoTest, AAPL_FetchesQuoteAndEstimates) {
    // If AAPL is in the persistent cache, Stock_info will use it; otherwise it may hit the API.
    Stock_info si;
    std::list<std::string> blobs = si.getStockInfo("AAPL");
    ASSERT_EQ(blobs.size(), 2);

    const std::string quote = blobs.front();
    const std::string ests  = blobs.back();

    // Basic structural checks 
    json jq = json::parse(quote);
    ASSERT_TRUE(jq.is_object());
    EXPECT_EQ(jq.value("Symbol", std::string()), "AAPL");
    ASSERT_TRUE(jq.contains("Name"));
    ASSERT_TRUE(jq["Name"].is_string());
    EXPECT_FALSE(jq["Name"].get<std::string>().empty());

}



TEST(SecurityTest, AAPL_ParsesMinimalFields) {
    Security sec("AAPL");
    EXPECT_EQ(sec.symbol, "AAPL");
    EXPECT_FALSE(sec.name.empty());
}

TEST(SecurityTest, BADSTRING) {
    EXPECT_THROW(Security("BADSTRING"),std::invalid_argument);
}

// ----------------------- User_info tests -----------------------

TEST(UserInfoTest, AddStockAndCalcValue) {
    User_info u("tester");
    Security aapl("AAPL");
    u.add_stock("AAPL", aapl, 1, 100.0);
    double value = u.calc_portfolio_current_value();
    EXPECT_GE(value, 0.0);
}

TEST(UserInfoTest, CSVParsingEnablesCalcs) {
    User_info u("tester");
    std::string csv = "AAPL, 1, 100.00\n";
    u.parseCSV(csv);

    std::string peg = u.calc_peterLynchPEG();
    EXPECT_FALSE(peg.empty());

    std::string graham = u.calc_benjaminGrahamInstrinsicValue();
    EXPECT_FALSE(graham.empty());
    EXPECT_NE(graham.find("Benjamin Graham"), std::string::npos);

    std::string ddm = u.calc_dividendDiscountModel();
    EXPECT_FALSE(ddm.empty());
    bool has_name = ddm.find("Dividend Discount Model") != std::string::npos;
    bool has_ddm_values = ddm.find("DDM value:") != std::string::npos;
    EXPECT_TRUE(has_name || has_ddm_values);
}

int main(int argc, char* argv[]){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
