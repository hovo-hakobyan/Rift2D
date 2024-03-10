cmake_minimum_required(VERSION 3.10)

project(ImGui)

add_library(${PROJECT_NAME} STATIC
  imgui.cpp
  imgui_draw.cpp
  imgui_widgets.cpp
  imgui_tables.cpp
  backends/imgui_impl_sdl.cpp
  backends/imgui_impl_opengl3.cpp
)

# Specify include directories for users of ImGui
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
