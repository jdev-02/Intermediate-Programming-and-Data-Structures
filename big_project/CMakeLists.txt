cmake_minimum_required(VERSION 3.10)
project(BigProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- Sources for your app ----
set(APP_SOURCES
    src/this_is_a_test.cpp
)

# ---- Dependencies ----
# Build GLFW from the vendored source
add_subdirectory(external/glfw)

# Find OpenGL
find_package(OpenGL REQUIRED)

# ImGui (core + backends)
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/external/imgui)
add_library(imgui
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
    # Optional std::string helpers:
    ${IMGUI_DIR}/misc/cpp/imgui_stdlib.cpp
)
target_include_directories(imgui PUBLIC
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
    ${CMAKE_SOURCE_DIR}/external/glfw/include
)

# ImPlot
set(IMPLOT_DIR ${CMAKE_SOURCE_DIR}/external/implot)
add_library(implot
    ${IMPLOT_DIR}/implot.cpp
    ${IMPLOT_DIR}/implot_items.cpp
    ${IMPLOT_DIR}/implot_demo.cpp    # optional; remove if you don't want the demo
)
target_include_directories(implot PUBLIC
    ${IMPLOT_DIR}
    ${IMGUI_DIR}          # ImPlot needs ImGui headers
)

# ---- Your executable ----
add_executable(test_app ${APP_SOURCES})

# Your public headers live here
target_include_directories(test_app PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
    ${IMPLOT_DIR}
    ${CMAKE_SOURCE_DIR}/external/glfw/include
)


find_package(CURL REQUIRED)
target_link_libraries(test_app PRIVATE ${CURL_LIBRARIES})
target_include_directories(test_app PRIVATE ${CURL_INCLUDE_DIRS})

# Link everything needed for the GUI
target_link_libraries(test_app PRIVATE
    imgui
    implot
    glfw           # from add_subdirectory(external/glfw)
    OpenGL::GL
)

# Warnings
target_compile_options(test_app PRIVATE -Wall -Wextra -Wpedantic -g)

enable_testing()
# find_package(GTest REQUIRED)  # add tests later
