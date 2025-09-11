#pragma once

#ifndef GUI_H
#define GUI_H

/*
GUI Module:
�	Requests input from user (tickers and shares owned and cost basis in CSV format for us to parse and process in preparation for simulation)
�	Presents user with a request for which projections it would like to be performed and which investor strategy should evaluate and rank their portfolio on
�	Display visual graphs and projections based on user selection
 - OpenGL handles what to draw, while GLFW handles where to draw it (the window) and how to interact with the user and the operating system environment.

�	Each of the investor filters will provide you with an analysis of the current portfolio ranked by the primary formulas used to evaluate securities and returns a grade. Separately, we will be implementing the graph to show conditional market performance if each equity you hold grows by 5x/2.5x/1.5x over the time period you hold it for.
�	Peter Lynch's PEG Ratio:
o	Fair Value = (EPS Growth Rate / P/E Ratio) � Current Price If PEG < 1.0 = undervalued, > 1.0 = overvalued X% of users stocks are undervalued/overvalued based on this metric.
�	Ex from API docs: "eps": 1.26, "epsEstimated": 1.19,
�	Benjamin Graham's Intrinsic Value:
o	Intrinsic Value = EPS � (8.5 + 2 � Expected Growth Rate) Key Metrics API "grahamNumber": 20.801963754945305,
�	Dividend Discount Model:
o	Stock Value = Annual Dividend / (Required Rate of Return - Dividend Growth Rate)

Sources: 
1. https://www.glfw.org/docs/3.3/group__window.html
2. https://www.glfw.org/docs/3.3/context_guide.html
3. https://github.com/ocornut/imgui?tab=readme-ov-file#usage
4. https://registry.khronos.org/OpenGL-Refpages/gl4/html/glClearColor.xhtml#:~:text=Name,detail%20on%20the%20removedTypes%20page.
*/

#include "user_info.h"
// ImGui/ImPlot/GLFW includes for GUI rendering
//#include "../external/imgui/imgui.h"                               //ImGui API
//#include "../external/imgui/imgui_impl_glfw.h"                     //ImGui GLFW backend
//#include "../external/imgui/imgui_impl_opengl3.h"                  //ImGui OpenGL3 backend
//#include "../external/implot/implot.h"                              //plotting library
//#include "../external/glfw/glfw3.h"                               //glfw api

//ImGui/ImPlot/GLFW includes for GUI rendering
#include "../external/imgui/imgui.h"                                 //imgui api
#include "../external/imgui/backends/imgui_impl_glfw.h"              //imgui glfw backend
#include "../external/imgui/backends/imgui_impl_opengl3.h"           //imgui opengl3 backend
//Include the loader helper BEFORE using any GL headers
#include "../external/imgui/backends/imgui_impl_opengl3_loader.h"    
#include "../external/implot/implot.h"                               //plotting library
#include <GLFW/glfw3.h>                                              //glfw api

#include <iostream>
#include <string>
#include <vector>
#include <conio.h> //For getch() on Windows
#include <algorithm>

#define SUCCESS 0
#define GLFW_INIT_FAIL 1
#define WINDOW_CREATE_FAILED 2
#define IMGUI_INIT_FAIL 3
#define CSV_PARSE_FAILED 4
#define FILE_NOT_FOUND 5
#define INVALID_INPUT 6
#define UNAME_BUF 128
#define CSV_BUF 4096
#define FPATH_BUF 512

using namespace std;

class GUI {
private:
    User_info userInfo;
    GLFWwindow* window; //pointer to the main app window

    bool portfolioLoaded;        //Tracks whether user has loaded portfolio data successfully
    //input buffers for user data
    char usernameBuffer[UNAME_BUF] = {}; //char array to store username input from user, will be fed into user_info class
    char csvInputBuffer[CSV_BUF] = {};   //character array to store manual CSV input from user
    char csvFilePath[FPATH_BUF] = {};       //character array to store file path for CSV file input

    string popupMessage;    //string to store messages displayed in popups (error or success)
    bool showPopup; //false unless theres a showpopup
    bool popupIsError; //true if error false if success, we will make red or green based on this

    //growth scenarios for 5x/2.5x/1.5x requirement from documentation
    int strategyType; //1 for peter lynch, 2 for ben graham, 3 for dividend discount (maybe we can use something else for multiple selections)
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
             selectedScenario(0), projectionYears(0) {

}

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
    window = glfwCreateWindow(1400, 900, "Investment Portfolio Projection Tool", NULL, NULL);
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

void GUI::run() {
    if (!window) {
        return 2; //window not initliazed
    }
    cout << "Starting Investment Portfolio Projection Tool GUI..." << endl;
    //main loop until user closes window 
    while (!glfwWindowShouldClose(window)) { //while the window is open
        glfwPollEvents(); //poll for events which takes in ipnut from user like kbd and mouse
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS {
            glfwSetWindowShouldClose(window,true); //close window if user presses escape key
            }
        //now we make the imgui frame
        ImGui_ImplOpenGl3_newFrame(); //prepare opengl backend
        ImGui_ImplGlfw_NewFrame(); //prepare glfw backend
        ImGui::NewFrame(); //new imgui frame
        requestUserInput();
        if (portfolioLoaded) {
                displayProjection();
                displayVisualGraphs();
        }
        renderPopupIfNeeded(); //render popup if required
        //frame rendering process for imgui and glfw
        Imgui::Render(); //finalize imgui frame
        int displaywidth, displayheight;
        glfwGetFramebufferSize(window, &displaywidth, &displayheight); //get pixel dimentions of framebuffer from glfw
        glViewport(0, 0, displaywidth, displayheight); //set opengl viewport to cover entire window
        glClearColor(0.1f, 0.1f, 0.12f, 1.0f); //set clear color to dark blue
        glClear(GL_COLOR_BUFFER_BIT); //clear framebuffer for next frame
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); //render imgui draw data via opengl3 backend - displays the gui
    
        glfwSwapBuffers(window);
    }
}

void GUI::cleanup() {
    if (window) {
        //shutdown imgui in reverse order of init process
        ImGui_ImplGlfw_Shutdown(); //free opengl resources
        ImGui_ImplGlfw_Shutdown(); //frees glfw integration resources
        ImPlot::DestroyContext(); //destroys implot contex of any generated chart resources
        ImGui::DestroyContext(); //destroys imgui context of gui rendering resources
    }
    //destroy the window now
    glfwDestroyWindow(window);
    window = nullptr; //dangling pointer protection
    glfwTerminate(); //shutdown glfw lib resources
}

void GUI::requestUserInput() {
    showMainWindow();
    handleCSVInputSection(); //handle portfolio data section
    showStrategyControls(); //shows strategy options and descriptions
}

void GUI::showMainWindow() {
    ImGui::Begin("Portfolio Input and Configuration"); // main input windwo for user
    ImGui::Text("Investment Portfolio Projection Tool");
    ImGui::Separator(); //adds a visual separator from imgui lib
    ImGui::Text("Username:");
    ImGui::InputText("##username", usernameBuffer, UNAME_BUF);

    if (ImGui::Button("Set Username")) {
        //if the button is clicked so val is true
        string username(usernameBuffer);
        if (!username.empty()) {
            //username validation
            userInfo.setUName(username);
            displaySuccess(useername); //provide positive feedback for successful addition of username
        }
        else { //it is empty which is an error
            string error = "Username cannot be empty.";
            displayError(error);
        }
    }
    ImGui::End(); //closes the main window rendering
}

void GUI::handleCSVInputSection() {
    ImGui::Begin("-----CSV Portfolio Data Input-----"); //create csv input window
    //file path input
    ImGui::Text("CSV File Path:");
    ImGui::InputText("##filepath", csvFilePath, FPATH_BUF);
    ImGui::SameLine(); //we want the upload button next to the input field for text for design

    if (ImGui::Button("Choose File")) {
        //if successful button then we will set the file path as the user inputted csvfilepath
        string filePath(csvFilePath); //creates a fs::path object from the string
        if (!filePath.empty()) {
            //if valid input
            ifstream file(filePath);
            if (file) { //if filestream established properly
                string fileContents((ifstreambuf_iterator<char>(file)), istreambuf_iterator<char>());
                //now validate for at least one valid line
                bool validstate = false;
                istringstream iss(fileContents) ; //create stringstream with the filecontents as we will pass contents to userinfo
                string line;
                while (getline(iss, line)) {
                    //while theres lines in the file contents
                    stringstream ss(line);
                    string cell;
                    int count = 0;
                    while (getline(ss, cell, ',')) {
                        ++count;
                    }
                    if (count == 3) {
                        validstate = true;
                        break;
                    }
                    if (valid) { //we have filecontents loaded with the proper format
                        strncpy(csvInputBuffer, fileContents.c_str(), CSV_BUF - 1); //minus one on buff for null char
                        csvInputBuffer[CSV_BUF - 1] = '\0'; //mannually null terminate to prevent buffer overflow
                        strncpy(userInfo.csvInputBuffer, csvInputBuffer, CSV_BUF - 1); //this will copy from this input buffer to input buffer in userinfo
                        userInfo.csvInputBuffer[CSV_BUF-1] = '\0';
                        userInfo.parseCSV(*this); //pass the object information from this module to the method in userinfo
                        portfolioLoaded = true;
                        displaySuccess("CSV file loaded and processed successfully.");
                    }
                    else {
                        //input validation error
                        displayError("CSV file format invalid. Expected: Ticker,Shares,Cost Basis on each line.");
                    }
                    else {
                        //file input error
                        displayError("File not found or insufficient permissions to open file.");
                    }
            else {
                //blank file path input field
                displayError("Please enter a file path to continue.");
            }
            //manual input option as well
            ImGui::Text("You can also paste CSV data (Format: Ticker, Shares, CostBasis):");
            ImGUI::InputTextMultiline("##csvdata", csvInputBuffer, CSV_BUF, ImVec2(-1, 120)); //imvec gives the 2d vector size for inputting the data
            if (ImGUI:Button("Process CSV")) {
                string csvData(csvInputBuffer);
                if (!csvData.empty()) {
                    strncpy(userInfo.csvInputBuffer, csvInputBuffer, CSV_BUF - 1);
                    userInfo.csvInputBuffer[CSV_BUF] = '\0';
                    userinfo.parseCSV(*this); //pass object info from this object to the userinfo method to parse the data since validated
                    poartfolioLoaded = true;
                    displaySuccess("CSV data processed successfully via manual method.");
                }
                else {
                    displayError("Please enter valid CSV data in the field.");
                }
            }
            ImGui::End();
                }

#endif