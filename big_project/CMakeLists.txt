cmake_minimum_required(VERSION 3.10)
project(BigProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- Dependencies ----
add_subdirectory(external/glfw)
find_package(OpenGL REQUIRED)
find_package(CURL REQUIRED)
find_package(GTest REQUIRED)

# ---- ImGui / ImPlot  ----
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/external/imgui)
add_library(imgui
  ${IMGUI_DIR}/imgui.cpp
  ${IMGUI_DIR}/imgui_draw.cpp
  ${IMGUI_DIR}/imgui_tables.cpp
  ${IMGUI_DIR}/imgui_widgets.cpp
  ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
  ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
  ${IMGUI_DIR}/misc/cpp/imgui_stdlib.cpp
)
target_include_directories(imgui PUBLIC
  ${IMGUI_DIR}
  ${IMGUI_DIR}/backends
  ${CMAKE_SOURCE_DIR}/external/glfw/include
)

set(IMPLOT_DIR ${CMAKE_SOURCE_DIR}/external/implot)
add_library(implot
  ${IMPLOT_DIR}/implot.cpp
  ${IMPLOT_DIR}/implot_items.cpp
  ${IMPLOT_DIR}/implot_demo.cpp
)
target_include_directories(implot PUBLIC ${IMPLOT_DIR} ${IMGUI_DIR})

# --- App ---
add_executable(test_app src/this_is_a_test.cpp)
target_include_directories(test_app PRIVATE
  ${CMAKE_SOURCE_DIR}/include
  ${IMGUI_DIR} ${IMGUI_DIR}/backends
  ${IMPLOT_DIR}
  ${CMAKE_SOURCE_DIR}/external/glfw/include
)
target_link_libraries(test_app PRIVATE
  CURL::libcurl      # needed because headers call curl
  imgui implot glfw OpenGL::GL
)
target_compile_options(test_app PRIVATE -Wall -Wextra -Wpedantic -g)

# --- Tests ---
enable_testing()
include(GoogleTest)

add_executable(runSecurityTests tests/security_tests.cpp)
target_include_directories(runSecurityTests PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(runSecurityTests PRIVATE
  CURL::libcurl          # needed here too (header-only curl calls)
  GTest::gtest
  GTest::gtest_main
  pthread
)
gtest_discover_tests(runSecurityTests)