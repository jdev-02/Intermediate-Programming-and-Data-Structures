#pragma once
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

Sources: 
1. https://www.glfw.org/docs/3.3/group__window.html
2. https://www.glfw.org/docs/3.3/context_guide.html
3. https://github.com/ocornut/imgui?tab=readme-ov-file#usage
*/

#ifndef GUI_H
#define GUI_H

#include "User_info.h"
// ImGui/ImPlot/GLFW includes for GUI rendering
#include "../external/imgui/imgui.h"                               //ImGui API
#include "../external/imgui/imgui_impl_glfw.h"                     //ImGui GLFW backend
#include "../external/imgui/imgui_impl_opengl3.h"                  //ImGui OpenGL3 backend
#include "../external/implot/implot.h"                              //plotting library
#include "../external/glfw/glfw3.h"                               //glfw api

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class GUI {
private:
    string username;
    User_info userInfo;
    GLFWwindow* window; //pointer to the main app window
    int strategyType; //1 for peter lynch, 2 for ben graham, 3 for dividend discount (maybe we can use something else for multiple selections)

    bool portfolioLoaded;        //Tracks whether user has loaded portfolio data successfully
    //input buffers for user data
    char usernameBuffer[128] = {}; //char array to store username input from user, will be fed into user_info class
    char csvInputBuffer[4096] = {};   //character array to store manual CSV input from user
    char csvFilePath[512] = {};       //character array to store file path for CSV file input
    string popupMessage;    //string to store messages displayed in popups (error or success)

    //growth scenarios for 5x/2.5x/1.5x requirement from documentation
    int selectedScenario;        //index for growth scenario: 0=nothing, 1=1.25x, 2=2.5x, 3=5x growth
    int projectionYears;         //number of years for growth projections (1-60), 0 means not set

public:
    friend class User_info;
    GUI();
    ~GUI();

    bool init(); //initialize the gui and create window using window var, returns false if fails from api call issue
    void run(); //main loop to run the gui app (until user exits)
    void cleanup(); //cleanup and free resources on exit (maybe in destructor)

private:
    //ui methods
    void requestUserInput(); //request username csv, strategy type, growth scenario multiplier, and projection years to draw graph. this will validate input
    void displayProjection(); //display numeric projections right below the graph
    void displayVisualGraphs(); //using implot to draw graph based on calcs from user info methods
    void displayError(string& err); //displays error based on string passed in
    void displaySuccess(string& msg); //displays success msg based on string passed in

private:
    //UI widgets/helpers
    void showMainWindow();
    void handleCSVInputSection();
    void showStrategyControls();
    void displayProjectionsWindow();
    void displayGrowthPlotWindow();

    //Analysis helper methods
    void performPeterLynchAnalysis();
    void performBenjaminGrahamAnalysis();
    void performDividendDiscountAnalysis();

    //popup helper methods
    void openPopup(const string& msg, bool isError = true);
    void renderPopupIfNeeded();  
};

//implementation

GUI::GUI() : window(nullptr), userInfo(), strategyType(0), portfolioLoaded(false),
             selectedScenario(0), projectionYears(0) {}

GUI::~GUI() {
    cleanup(); //explicit cleanup call for freeing resources
}

bool GUI::init() {
    //initalize GLFW
    if (!glfwInit()) {
        openPopup("Failed to initialize GLFW", true);
        return false;
    }
    //set opengl 3.3 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    //create window and opengl context, data member is pointer to GLFW window
    window = glfwCreateWindow(1200, 800, "Investment Portfolio Projection Tool", NULL, NULL);
    if (window == NULL) {
        glfwTerminate();
        openPopup("Failed to create GLFW window", true);
        return false;
    }
    //make the gl context current per documentation
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    //create implot context and set style for popups
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImPlot::CreateContext();
    ImGui::StyleColorsDark();

    // Initialize ImGui backends for GLFW + OpenGL3
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    return true; //successful init
}


#endif