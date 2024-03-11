cmake_minimum_required(VERSION 3.10)

# Define ImGui as a static library
project(ImPlotLibrary)

add_library(ImPlot STATIC
implot.cpp
implot_items.cpp
)

set(ImPlotIncludeDir "${CMAKE_CURRENT_SOURCE_DIR}" PARENT_SCOPE)

target_include_directories(ImPlot PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${ImPlotIncludeDir})
target_link_libraries(ImPlot PUBLIC ImGui)

