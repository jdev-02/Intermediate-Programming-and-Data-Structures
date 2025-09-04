/*
GUI Module:
•	Requests input from user (tickers and shares owned and cost basis in CSV format for us to parse and process in preparation for simulation)
•	Presents user with a request for which projections it would like to be performed and which investor strategy should evaluate and rank their portfolio on
•	Display visual graphs and projections based on user selection

•	Each of the investor filters will provide you with an analysis of the current portfolio ranked by the primary formulas used to evaluate securities and returns a grade. Separately, we will be implementing the graph to show conditional market performance if each equity you hold grows by 5x/2.5x/1.5x over the time period you hold it for.
•	Peter Lynch's PEG Ratio:
o	Fair Value = (EPS Growth Rate / P/E Ratio) × Current Price If PEG < 1.0 = undervalued, > 1.0 = overvalued X% of users stocks are undervalued/overvalued based on this metric.
•	Ex from API docs: "eps": 1.26, "epsEstimated": 1.19,
•	Benjamin Graham's Intrinsic Value:
o	Intrinsic Value = EPS × (8.5 + 2 × Expected Growth Rate) Key Metrics API "grahamNumber": 20.801963754945305,
•	Dividend Discount Model:
o	Stock Value = Annual Dividend / (Required Rate of Return - Dividend Growth Rate)

*/

#ifndef GUI_H
#define GUI_H

#include "User_info.h"
#include <string>
#include <vector>

class GUI {
private:
    User_info userInfo;
    int strategyType; //1 for peter lynch, 2 for ben graham, 3 for dividend discount (maybe we can use something else for multiple selections)

    //Helper methods for display
    void displayWelcomeScreen();
    void displayMenu();
    void displayAnalysisResults(const PortfolioAnalysis& analysis);

    //Input handling
    //string getCSVInput();
    // getProjectionSelections();
    //int getStrategySelection();

public:
    GUI();
    ~GUI() = default;

    //interface methods
    void run(); //does main loop for gui service (press q to quit or similar)
    void requestUserInput(); 
    displayProjections(); //displays projections based on user selection as a popup with 
    displayVisualGraphs(); //displays graphs based on user selection as a popup
    displayPopup(displayProjections, displayVisualGraphs); //
    //Specific display methods
    void showPerformanceChart();
    void showRiskAssessment();
    void showStrategyComparison();
    void showGrowthProjection();

    // Utility methods
    void clearScreen(); //do this after the user inputs their data and before the results are displayed
    void waitForUserInput(); //pauses until user presses a key to continue to display results
    void displayError(const std::string& error); //displays error messages in a popup if soemthing in ingest or processing goes wrong
    void displaySuccess(const std::string& message); //displays success messages before showing results
};

#endif