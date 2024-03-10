cmake_minimum_required(VERSION 3.10)

# Define ImGui as a static library
project(ImGuiLibrary)

add_library(ImGui STATIC
  imgui.cpp
  imgui_demo.cpp
  imgui_draw.cpp
  imgui_widgets.cpp
  imgui_tables.cpp
  backends/imgui_impl_sdl2.cpp
  backends/imgui_impl_sdlrenderer2.cpp
  backends/imgui_impl_opengl3.cpp
)

set(ImGuiIncludeDir "${CMAKE_CURRENT_SOURCE_DIR}" PARENT_SCOPE)

# Specify include directories for users of ImGui
target_include_directories(ImGui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${SDL2_INCLUDE_DIR})
