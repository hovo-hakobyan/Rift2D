cmake_minimum_required(VERSION 3.26)
project(Rift2D)

include(FetchContent)

# add imgui
# declares the content that needs to be downloaded
FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui.git
  GIT_TAG v1.90.4
)

# do the actual dowloading, if necessary
FetchContent_MakeAvailable(imgui)

# add implot
FetchContent_Declare(
  implot
  GIT_REPOSITORY https://github.com/epezent/implot.git
  GIT_TAG v0.16
)

FetchContent_MakeAvailable(implot)

set(IMGUI_SOURCES
  ${imgui_SOURCE_DIR}/imgui.cpp
  ${imgui_SOURCE_DIR}/imgui_draw.cpp
  ${imgui_SOURCE_DIR}/imgui_widgets.cpp
  ${imgui_SOURCE_DIR}/imgui_tables.cpp
  ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl2.cpp
  ${imgui_SOURCE_DIR}/backends/imgui_impl_sdlrenderer2.cpp
  ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp

  ${implot_SOURCE_DIR}/implot.cpp
  ${implot_SOURCE_DIR}/implot_items.cpp
)

# add box2d
FetchContent_Declare(
  box2d
  GIT_REPOSITORY https://github.com/erincatto/box2d.git
  GIT_TAG v2.4.0
)


FetchContent_GetProperties(box2d)
if(NOT box2d_POPULATED)
  FetchContent_Populate(box2d)
endif()

# Include all Box2D .cpp files
file(GLOB_RECURSE BOX2D_SOURCES "${box2d_SOURCE_DIR}/src/*.cpp")

# Add Box2D's include and src directories for header file resolution
include_directories(
  ${box2d_SOURCE_DIR}/include
  ${box2d_SOURCE_DIR}/src
)


# ignore the compiler warinings for external libs
if (WIN32)
set_source_files_properties("${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp"
                          PROPERTIES COMPILE_FLAGS "/wd4701")
# Disabling warning C4189 for specific Box2D files
set_source_files_properties("${box2d_SOURCE_DIR}/src/dynamics/b2_distance_joint.cpp"
                          PROPERTIES COMPILE_FLAGS "/wd4189")
set_source_files_properties("${box2d_SOURCE_DIR}/src/dynamics/b2_mouse_joint.cpp"
                          PROPERTIES COMPILE_FLAGS "/wd4189")
set_source_files_properties("${box2d_SOURCE_DIR}/src/dynamics/b2_revolute_joint.cpp"
                           PROPERTIES COMPILE_FLAGS "/wd4189")
set_source_files_properties("${box2d_SOURCE_DIR}/src/dynamics/b2_rope_joint.cpp"
                           PROPERTIES COMPILE_FLAGS "/wd4189")

endif()

# Define engine files
file(GLOB ENGINE_AUDIO_SOURCES "Rift2D/Audio/*.cpp" "Rift2D/Audio/*.h")
file(GLOB ENGINE_CORE_SOURCES "Rift2D/Core/*.cpp" "Rift2D/Core/*.h")
file(GLOB ENGINE_COMMON_SOURCES "Rift2D/Common/*.cpp" "Rift2D/Common/*.h")
file(GLOB ENGINE_COMPPONENT_SOURCES "Rift2D/Components/*.cpp" "Rift2D/Components/*.h" )
file(GLOB ENGINE_GRAPHICS_SOURCES "Rift2D/Graphics/*.cpp" "Rift2D/Graphics/*.h" )
file(GLOB ENGINE_INPUT_SOURCES "Rift2D/Input/*.cpp" "Rift2D/Input/*.h" )
file(GLOB ENGINE_PHYSICS_SOURCES "Rift2D/Physics/*.cpp" "Rift2D/Physics/*.h")
file(GLOB ENGINE_WORLD_SOURCES "Rift2D/World/*.cpp" "Rift2D/World/*.h" )


# Create filters
source_group("Audio" FILES ${ENGINE_AUDIO_SOURCES})
source_group("Core" FILES ${ENGINE_CORE_SOURCES})
source_group("Components" FILES ${ENGINE_COMPPONENT_SOURCES})
source_group("Common" FILES ${ENGINE_COMMON_SOURCES})
source_group("Graphics" FILES ${ENGINE_GRAPHICS_SOURCES})
source_group("Input" FILES ${ENGINE_INPUT_SOURCES})
source_group("Physics" FILES ${ENGINE_PHYSICS_SOURCES})
source_group("World" FILES ${ENGINE_WORLD_SOURCES})
source_group("Third-Party\\Imgui" FILES ${IMGUI_SOURCES} )
source_group("Third-Party\\Box2D" FILES ${BOX2D_SOURCES} )

# Add all sources to Engine library
add_library(Engine STATIC 
${ENGINE_AUDIO_SOURCES}
${ENGINE_CORE_SOURCES}
${ENGINE_COMPPONENT_SOURCES}
${ENGINE_COMMON_SOURCES}
${ENGINE_GRAPHICS_SOURCES}
${ENGINE_INPUT_SOURCES}
${ENGINE_PHYSICS_SOURCES}
${ENGINE_WORLD_SOURCES}
${IMGUI_SOURCES}
${BOX2D_SOURCES})

# Link box2d
#target_link_libraries(Engine PRIVATE box2d)

# enable c++20 features
target_compile_features(Engine PUBLIC cxx_std_20)

# compile at max warning level + treat warnings as errors
target_compile_options(Engine PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)

# add glm
FetchContent_Declare(
  glm
  URL https://github.com/g-truc/glm/releases/download/0.9.9.8/glm-0.9.9.8.zip
  DOWNLOAD_NO_PROGRESS ON
  DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/downloads
)

FetchContent_GetProperties(glm)
if(NOT glm_POPULATED)
  FetchContent_Populate(glm)
endif()


#PRIVATE: used only by this target, other targets that link against the engine won't have access
#INTERFACE: only for targets that link against this target, engine has no use
target_include_directories(Engine PUBLIC
${imgui_SOURCE_DIR}
${imgui_SOURCE_DIR}/backends
${implot_SOURCE_DIR}
${box2d_SOURCE_DIR}/include
${glm_SOURCE_DIR}
${CMAKE_SOURCE_DIR}/Rift2D/Audio
${CMAKE_SOURCE_DIR}/Rift2D/Core
${CMAKE_SOURCE_DIR}/Rift2D/Components
${CMAKE_SOURCE_DIR}/Rift2D/Common
${CMAKE_SOURCE_DIR}/Rift2D/Graphics
${CMAKE_SOURCE_DIR}/Rift2D/Input
${CMAKE_SOURCE_DIR}/Rift2D/Physics
${CMAKE_SOURCE_DIR}/Rift2D/World
)

# add SDL2
if(WIN32)
  FetchContent_Declare(
    SDL2
    URL https://www.libsdl.org/release/SDL2-devel-2.28.5-VC.zip 
    DOWNLOAD_NO_PROGRESS ON
    DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/downloads 

  )
  FetchContent_GetProperties(SDL2)
  if(NOT SDL2_POPULATED)
    FetchContent_Populate(SDL2)
    set(SDL2_INCLUDE_DIR ${sdl2_SOURCE_DIR}/include)
  if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
    set(SDL2_LIBRARIES "${sdl2_SOURCE_DIR}/lib/x64/SDL2.lib;${sdl2_SOURCE_DIR}/lib/x64/SDL2main.lib")
    set(SDL2_LIBRARY_DLL "${sdl2_SOURCE_DIR}/lib/x64/SDL2.dll")
  else()
    set(SDL2_LIBRARIES "${sdl2_SOURCE_DIR}/lib/x86/SDL2.lib;${sdl2_SOURCE_DIR}/lib/x86/SDL2main.lib")
    set(SDL2_LIBRARY_DLL "${sdl2_SOURCE_DIR}/lib/x86/SDL2.dll")
  endif()
  endif()
endif()

  # add SDL2_image
  FetchContent_Declare(
    SDL2_image
    URL https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.8.2-VC.zip 
    DOWNLOAD_NO_PROGRESS ON
    DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/downloads
  )
  FetchContent_GetProperties(SDL2_image)
  if(NOT SDL2_image_POPULATED)
    FetchContent_Populate(SDL2_image)
    set(SDL2_IMAGE_INCLUDE_DIR ${sdl2_image_SOURCE_DIR}/include)
  if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
    set(SDL2_IMAGE_LIBRARIES "${sdl2_image_SOURCE_DIR}/lib/x64/SDL2_image.lib")
    set(SDL2_IMAGE_LIBRARY_DLL "${sdl2_image_SOURCE_DIR}/lib/x64/SDL2_image.dll")
  else()
    set(SDL2_IMAGE_LIBRARIES "${sdl2_image_SOURCE_DIR}/lib/x86/SDL2_image.lib")
    set(SDL2_IMAGE_LIBRARY_DLL "${sdl2_image_SOURCE_DIR}/lib/x86/SDL2_image.dll")
  endif()
  endif()

  
  # add SDL2_ttf
  FetchContent_Declare(
    SDL2_ttf
    URL https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-devel-2.20.2-VC.zip
    DOWNLOAD_NO_PROGRESS ON
    DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/downloads
  )
  FetchContent_GetProperties(SDL2_ttf)
  if(NOT sdl2_ttf_POPULATED)
    FetchContent_Populate(SDL2_ttf)
    set(SDL2_TTF_INCLUDE_DIR ${sdl2_ttf_SOURCE_DIR}/include)
  if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
    set(SDL2_TTF_LIBRARIES ${sdl2_ttf_SOURCE_DIR}/lib/x64/SDL2_ttf.lib)
    set(SDL2_TTF_LIBRARY_DLL "${sdl2_ttf_SOURCE_DIR}/lib/x64/SDL2_ttf.dll")
  else()
    set(SDL2_TTF_LIBRARIES ${sdl2_ttf_SOURCE_DIR}/lib/x86/SDL2_ttf.lib)
    set(SDL2_TTF_LIBRARY_DLL "${sdl2_ttf_SOURCE_DIR}/lib/x86/SDL2_ttf.dll")
  endif()
  endif()

  # add SDL_mixer
  FetchContent_Declare(
    SDL2_mixer
    URL "https://github.com/libsdl-org/SDL_mixer/releases/download/release-2.8.0/SDL2_mixer-devel-2.8.0-VC.zip"
    DOWNLOAD_NO_PROGRESS ON
    DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/downloads
  )

  # Check if population has already been performed
  FetchContent_GetProperties(SDL2_mixer)
  if(NOT sdl2_mixer_POPULATED)
    FetchContent_Populate(SDL2_mixer)
    set(SDL2_MIXER_INCLUDE_DIR ${sdl2_mixer_SOURCE_DIR}/include)
    if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
    set(SDL2_MIXER_LIBRARY_DLL "${sdl2_mixer_SOURCE_DIR}/lib/x64/SDL2_mixer.dll")
    set(SDL2_MIXER_LIBRARIES "${sdl2_mixer_SOURCE_DIR}/lib/x64/SDL2_mixer.lib")
  else()
    set(SDL2_MIXER_LIBRARY_DLL "${sdl2_mixer_SOURCE_DIR}/lib/x86/SDL2_mixer.dll")
    set(SDL2_MIXER_LIBRARIES "${sdl2_mixer_SOURCE_DIR}/lib/x86/SDL2_mixer.lib")
  endif()


  set(VLD_DIR "$ENV{ProgramFiles\(x86\)}/Visual Leak Detector")
  IF(EXISTS ${VLD_DIR})
    set(VLD_INCLUDE_DIR "${VLD_DIR}/include")
    if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
        set(VLD_LIBRARY "${VLD_DIR}/lib/Win64/vld.lib")
    else()
        set(VLD_LIBRARY "${VLD_DIR}/lib/Win32/vld.lib")
    endif()
  endif()

  # set all include directories for the engine
  target_include_directories(Engine PUBLIC
    ${VLD_INCLUDE_DIR}
    ${SDL2_INCLUDE_DIR} 
    ${SDL2_IMAGE_INCLUDE_DIR} 
    ${SDL2_TTF_INCLUDE_DIR}
    ${SDL2_MIXER_INCLUDE_DIR}
)

  # set libraries to link with
  target_link_libraries(Engine PUBLIC
    ${SDL2_LIBRARIES} 
    ${SDL2_IMAGE_LIBRARIES} 
    ${SDL2_TTF_LIBRARIES} 
    ${VLD_LIBRARY}
    ${SDL2_MIXER_LIBRARIES}
    xinput
  )
endif()

if(WIN32)

  # add post build commands
  add_custom_command(TARGET Engine POST_BUILD
      COMMAND "${CMAKE_COMMAND}" -E copy "${SDL2_LIBRARY_DLL}" "$<TARGET_FILE_DIR:Engine>"
  )
  add_custom_command(TARGET Engine POST_BUILD
      COMMAND "${CMAKE_COMMAND}" -E copy "${SDL2_IMAGE_LIBRARY_DLL}" "$<TARGET_FILE_DIR:Engine>"
  )
  add_custom_command(TARGET Engine POST_BUILD
      COMMAND "${CMAKE_COMMAND}" -E copy "${SDL2_TTF_LIBRARY_DLL}" "$<TARGET_FILE_DIR:Engine>"
  )

  add_custom_command(TARGET Engine POST_BUILD
  COMMAND "${CMAKE_COMMAND}" -E copy "${SDL2_MIXER_LIBRARY_DLL}" "$<TARGET_FILE_DIR:Engine>"
)


  add_custom_command(TARGET Engine POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy_directory "${CMAKE_SOURCE_DIR}/Data" "$<TARGET_FILE_DIR:Engine>/Data"
  )



  set_target_properties(Engine PROPERTIES
        LINK_FLAGS "/SUBSYSTEM:CONSOLE"
    )
  
endif()

# Game

# Define game files
file(GLOB GAME_COMMANDS_SOURCES "Digger/Commands/*.cpp" "Digger/Commands/*.h")
file(GLOB GAME_COMPONENTS_SOURCES "Digger/Components/*.cpp" "Digger/Components/*.h")
file(GLOB GAME_DIGGER_SOURCES "Digger/Digger/*.cpp" "Digger/Digger/*.h")
file(GLOB GAME_MISC_SOURCES "Digger/Misc/*.cpp" "Digger/Misc/*.h")
file(GLOB GAME_PREFABS_SOURCES "Digger/Prefabs/*.cpp" "Digger/Prefabs/*.h")
file(GLOB GAME_SCENES_SOURCES "Digger/Scenes/*.cpp" "Digger/Scenes/*.h")
file(GLOB GAME_STATES_SOURCES "Digger/States/*.cpp" "Digger/States/*.h")

# Create filtesr
source_group("Commands" FILES ${GAME_COMMANDS_SOURCES})
source_group("Components" FILES ${GAME_COMPONENTS_SOURCES})
source_group("Digger" FILES ${GAME_DIGGER_SOURCES})
source_group("Misc" FILES ${GAME_MISC_SOURCES})
source_group("Prefabs" FILES ${GAME_PREFABS_SOURCES})
source_group("Scenes" FILES ${GAME_SCENES_SOURCES})
source_group("States" FILES ${GAME_STATES_SOURCES})

# Create executable
add_executable(Digger
 ${GAME_COMMANDS_SOURCES}
 ${GAME_COMPONENTS_SOURCES}
 ${GAME_DIGGER_SOURCES}
 ${GAME_MISC_SOURCES}
 ${GAME_PREFABS_SOURCES}
 ${GAME_SCENES_SOURCES}
 ${GAME_STATES_SOURCES}
 )

# Link against Engine. Tells the linker where to find the libraries
target_link_libraries(Digger PRIVATE Engine)
# to find include files
target_include_directories(Digger PRIVATE 
${CMAKE_SOURCE_DIR}/Rift2D/
${CMAKE_SOURCE_DIR}/Digger/
${imgui_SOURCE_DIR}
${imgui_SOURCE_DIR}/backends
${glm_SOURCE_DIR}
)

# enable c++20 features
target_compile_features(Digger PUBLIC cxx_std_20)

# compile at max warning level + treat warnings as errors
target_compile_options(Digger PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)

#Set the startup project for Visual Studio
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Digger)
#Add post build commands for the Testing executable

add_custom_command(TARGET Digger POST_BUILD
  COMMAND "${CMAKE_COMMAND}" -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/Data" "$<TARGET_FILE_DIR:Digger>/Data"
)

# Enable console
set_target_properties(Digger PROPERTIES
LINK_FLAGS "/SUBSYSTEM:CONSOLE"
)
