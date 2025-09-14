#Portfolio Projection System

A C++ application for analyzing investment portfolios using famous investor methodologies and generating future value projections.

#Overview

The Portfolio Projection System allows users to upload stock portfolios and analyze potential future performance using proven investment strategies from Peter Lynch, Benjamin Graham, and dividend discount models. The application provides conservative, moderate, and optimistic projections with visual graphs and detailed stock rankings.

#Features

-Portfolio Analysis: Upload CSV files or manually enter stock positions
-Multiple Projection Models: Peter Lynch PEG, Benjamin Graham Intrinsic Value, Dividend Discount Model
-Scenario Planning: Conservative, moderate, and optimistic market projections
-Real-time Data: Integration with Alpha Vantage API (with local caching)
-GUI Interface: User-friendly desktop application using ImGui, ImPlot, and GLFW

#Installation

#System Requirements
-C++ compiler with C++17 support (g++ 7.0+ or clang++ 5.0+)
-CMake 3.15 or higher
-ImGui, ImPlot, GLFW, nlohmann-json libraries
-Internet connection for API access

#macOS Installation
```bash
#Install dependencies using Homebrew
brew install cmake glfw

```

#Create build directory
mkdir build && cd build

#Configure and build
cmake ..
make

#Run the application
./test_app
```

#Usage

#Portfolio Input Format
Create a CSV file with the following format:
```csv
ticker,shares,cost_basis
AAPL,100,150.50
MSFT,50,280.25
GOOGL,25,2500.75
```

An example is included in /tests/input_test.csv

#Running Analysis

0. from the build folder run commands `cmake ..` and  `make`
1. Launch the application: from the build folder `./test_app`
2. Enter your username
3. Choose analysis method from radio button
4. Select time horizon
5. Pick market scenario (Conservative/Moderate/Optimistic)
6. Enter your portfolio via file path CSV or manual input
7. View results

#Documentation

#Technical Implementation
#Required Course Techniques Implementation

| Technique | Location | Description |
|-----------|----------|-------------|
| **Hash Table/Dictionary** | `user_info.h` | Portfolio storage with ticker as key (`map`) |
| **Object-Oriented Design** | `Security.h`, `user_info.h` | FinancialInstrument base class, Security derived |
| **Inheritance** | `Security.h` | Security inherits FinancialInstrument |
| **Exception Handling** | `Security.h` | Throws on API/JSON errors |
| **Functional Programming** | `user_info.h` | Lambdas/functions for portfolio aggregation |
| **GUI Implementation** | `GUI.h` | ImGui/GLFW/ImPlot interface |
| **Unit Testing** | `tests/` | For calculation validation |
| **External Libraries** | `Stock_info.h` | nlohmann::json, ImGui, ImPlot, GLFW |

#Bonus Features

| Feature | Location | Description |
|---------|----------|-------------|
| **Data Persistence** | `Stock_info.h` | JSON cache for API results |
| **Advanced Functional Programming** | `user_info.h` | Aggregation via function |

### Project Structure
```
portfolio-projection-system/
├── CMakeLists.txt              -->Created the make file
├── external                    -->Includes external libraries used
├── include                     -->Repo for project files
│   ├── GUI.h
│   ├── json.hpp
│   ├── Math.h
│   ├── Security.h
│   ├── Stock_info.h
│   └── user_info.h
├── reactions                   -->Project reactions from participants
│   └── reactions.txt
├── README.md                   -->This file **YOU ARE HERE**
├── src                         -->.cpp that is compiled to launch the GUI
│   └── this_is_a_test.cpp
└── tests                       -->Test repository
    ├── input_test.csv
    └── security_tests.cpp


```
