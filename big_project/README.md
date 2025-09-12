#Portfolio Projection System

A C++ application for analyzing investment portfolios using famous investor methodologies and generating future value projections.

#Overview

The Portfolio Projection System allows users to upload stock portfolios and analyze potential future performance using proven investment strategies from Peter Lynch, Benjamin Graham, and dividend discount models. The application provides conservative, moderate, and optimistic projections with visual graphs and detailed stock rankings.

#Features

-Portfolio Analysis: Upload CSV files or manually enter stock positions
-Multiple Projection Models: Peter Lynch PEG, Benjamin Graham Intrinsic Value, Dividend Discount Model
-Scenario Planning: Conservative, moderate, and optimistic market projections
-Stock Rankings: Priority-based ranking system using selected methodology
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
brew install cmake nlohmann-json glfw

#ImGui and ImPlot will be included as submodules or built from source
#See Building from Source section below
```

#Linux Installation (Ubuntu/Debian)
```bash
sudo apt-get update
sudo apt-get install cmake libnlohmann-json3-dev libglfw3-dev libgl1-mesa-dev
```

#Building from Source

```bash
#Clone the repository
git clone https://github.com/yourusername/portfolio-projection-system.git
cd portfolio-projection-system

#Create build directory
mkdir build && cd build

#Configure and build
cmake ..
make

#Run the application
./portfolio_simulator
```

#API Setup

Important: This application requires an Alpha Vantage API key to function.

1. Sign up at [Alpha Vantage](https://www.alphavantage.co/support/#api-key)
2. Obtain your free API key (250 calls/day limit)
3. The API key is set in the code (`Stock_info.h`). Edit the `#define API_KEY` line with your key:

```cpp
#define API_KEY "your_api_key_here"
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

#Running Analysis
1. Launch the application: `./portfolio_simulator`
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
├── src/                    # Source files
│   ├── main.cpp
│   ├── user_info.h
│   ├── Stock_info.h
│   ├── Security.h
│   └── GUI.h
├── tests/                  # Unit tests
├── docs/                   # Additional documentation
├── CMakeLists.txt
└── README.md
```

## Troubleshooting

**Common Issues:**

- **GUI doesn't appear**: Ensure all ImGui/GLFW dependencies are installed
- **API rate limit exceeded**: Application uses local cache to minimize calls
- **Build errors**: Verify all dependencies are installed and CMake version is 3.15+
- **Missing API key**: Edit `Stock_info.h` and add your Alpha Vantage API key to the `#define API_KEY` line

**Network Requirements:**
- Internet connection required for initial stock data fetching
- Offline mode available using cached data after first successful API calls

**Graphics Issues:**
- **OpenGL errors**: Ensure your system has OpenGL support and updated graphics drivers
- **ImGui rendering problems**: Verify GLFW is properly installed and linked