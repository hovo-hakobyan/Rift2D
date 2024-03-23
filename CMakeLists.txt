cmake_minimum_required(VERSION 3.26)
project(Rift2D)

option(STEAMWORKS "Use steamworks SDK" TRUE)

if(EMSCRIPTEN)
  message("Using Emscripten!")
endif()

if(EMSCRIPTEN)
  set(TARGET_NAME Rift2D_web)
  set(TARGET_PARAM )
else()
  set(TARGET_NAME Rift2D)
  set(TARGET_PARAM WIN32)
endif()



# list source files here
add_executable(${TARGET_NAME} ${TARGET_PARAM}
  Rift2D/BaseComponent.h
  Rift2D/Font.cpp
  Rift2D/Font.h
  Rift2D/FPSComponent.cpp
  Rift2D/FPSComponent.h
  Rift2D/GameObject.cpp
  Rift2D/GameObject.h
  Rift2D/InputManager.cpp
  Rift2D/InputManager.h
  Rift2D/Main.cpp
  Rift2D/Rift2DEngine.cpp
  Rift2D/Rift2DEngine.h
  Rift2D/Renderer.cpp
  Rift2D/Renderer.h
  Rift2D/ResourceManager.cpp
  Rift2D/ResourceManager.h
  Rift2D/Rotator.cpp
  Rift2D/Rotator.h
  Rift2D/Scene.cpp
  Rift2D/Scene.h
  Rift2D/SceneManager.cpp
  Rift2D/SceneManager.h
  Rift2D/TextComponent.cpp
  Rift2D/TextComponent.h
  Rift2D/Texture2D.cpp
  Rift2D/Texture2D.h
  Rift2D/Transform.cpp
  Rift2D/Transform.h
  Rift2D/TimeManager.h
  Rift2D/Interfaces.h
  Rift2D/SpriteComponent.cpp
  Rift2D/SpriteComponent.h
  Rift2D/LineGraph.cpp
  Rift2D/LineGraph.h
  Rift2D/TrashTheCache.cpp
  Rift2D/TrashTheCache.h
  Rift2D/Gamepad.cpp
  Rift2D/Gamepad.h
  Rift2D/ShootCommand.cpp
  Rift2D/ShootCommand.h
  Rift2D/Axis2DCommand.h
  Rift2D/MoveCommand.cpp
  Rift2D/MoveCommand.h
  Rift2D/Subject.h
  Rift2D/MenuScene.cpp
  Rift2D/MenuScene.h
  Rift2D/Prefab.cpp
  Rift2D/Prefab.h
  Rift2D/DiggerPrefab.cpp
  Rift2D/DiggerPrefab.h
  Rift2D/HealthComponent.cpp
  Rift2D/HealthComponent.h
  Rift2D/HealthDisplayComponent.cpp
  Rift2D/HealthDisplayComponent.h
  Rift2D/EnemyPrefab.cpp
  Rift2D/EnemyPrefab.h
  Rift2D/ScoreComponent.cpp
  Rift2D/ScoreComponent.h
  Rift2D/ScoreDisplayComponent.cpp
  Rift2D/ScoreDisplayComponent.h
  Rift2D/ScoreCommand.cpp
  Rift2D/ScoreCommand.h
)


#imgui + implot
add_library(imgui OBJECT
3rdParty/imgui/imgui.cpp
3rdParty/imgui/imgui_draw.cpp
3rdParty/imgui/imgui_widgets.cpp
3rdParty/imgui/imgui_tables.cpp
3rdParty/imgui/backends/imgui_impl_opengl3.cpp
3rdParty/imgui/backends/imgui_impl_sdl2.cpp
3rdParty/imgui/backends/imgui_impl_sdlrenderer2.cpp

3rdParty/implot/implot.cpp
3rdParty/implot/implot_items.cpp
)

target_include_directories(imgui PRIVATE 3rdParty/imgui 3rdParty/implot)
target_link_libraries(${TARGET_NAME} PRIVATE imgui)

# Steamworks
if(STEAMWORKS)
  if(NOT EXISTS "${CMAKE_SOURCE_DIR}/3rdParty/steamworks")
    message(FATAL_ERROR "Steamworks directory not found")
  else()
    file(GLOB STEAMWORKS_FILES "${CMAKE_SOURCE_DIR}/3rdParty/steamworks/*")
      if(NOT STEAMWORKS_FILES)
        message(FATAL_ERROR "Steamworks dir is empty")
      endif()
  endif()

  set(STEAMWORKS_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/3rdParty/steamworks/public/steam)
  set(STEAMWORKS_LIB_DIR ${CMAKE_SOURCE_DIR}/3rdParty/steamworks/redistributable_bin)

  if(WIN32)
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
      set(STEAMWORKS_LIB ${STEAMWORKS_LIB_DIR}/win64/steam_api64.lib)
      add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
          COMMAND ${CMAKE_COMMAND} -E copy
                 ${STEAMWORKS_LIB_DIR}/win64/steam_api64.dll
                 $<TARGET_FILE_DIR:${TARGET_NAME}> )
   else()
      set(STEAMWORKS_LIB ${STEAMWORKS_LIB_DIR}/steam_api.lib)
     add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${STEAMWORKS_LIB_DIR}/steam_api.dll
                $<TARGET_FILE_DIR:${TARGET_NAME}>)
   endif()

   target_include_directories(${TARGET_NAME} PRIVATE ${STEAMWORKS_INCLUDE_DIR})
   target_link_libraries(${TARGET_NAME} PRIVATE ${STEAMWORKS_LIB})


    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
     COMMAND ${CMAKE_COMMAND} -E echo 480 > "$<TARGET_FILE_DIR:${TARGET_NAME}>/steam_appid.txt"
     COMMENT "Creating steam_appid.txt"
  )


 
  endif()
endif()


# enable c++20 features
target_compile_features(${TARGET_NAME} PUBLIC cxx_std_20)
# set Rift2D as the default startup project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${TARGET_NAME})


include(FetchContent)
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

# add SDL2
if (WIN32)
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

  set(VLD_DIR "$ENV{ProgramFiles\(x86\)}/Visual Leak Detector")
  IF(EXISTS ${VLD_DIR})
    set(VLD_INCLUDE_DIR "${VLD_DIR}/include")
    if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
        set(VLD_LIBRARY "${VLD_DIR}/lib/Win64/vld.lib")
    else()
        set(VLD_LIBRARY "${VLD_DIR}/lib/Win32/vld.lib")
    endif()
  endif()

  # set all include directories
  target_include_directories(${TARGET_NAME} PRIVATE
    ${VLD_INCLUDE_DIR}
    ${SDL2_INCLUDE_DIR} 
    ${SDL2_IMAGE_INCLUDE_DIR} 
    ${SDL2_TTF_INCLUDE_DIR}
)

  target_include_directories(imgui PRIVATE
    ${SDL2_INCLUDE_DIR} 
    ${SDL2_IMAGE_INCLUDE_DIR} 
    ${SDL2_TTF_INCLUDE_DIR}
)

  # set libraries to link with
  target_link_libraries(${TARGET_NAME} PUBLIC
    ${SDL2_LIBRARIES} 
    ${SDL2_IMAGE_LIBRARIES} 
    ${SDL2_TTF_LIBRARIES} 
    ${VLD_LIBRARY}
    xinput
  )

elseif(NOT EMSCRIPTEN)

  FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-2.28.5
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
  )
  FetchContent_MakeAvailable(SDL2)
  
  FetchContent_Declare(
    SDL2_image
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
    GIT_TAG release-2.8.2
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
  )
  set(SDL2IMAGE_INSTALL OFF)
  FetchContent_MakeAvailable(SDL2_image)

  FetchContent_Declare(
    SDL2_ttf
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
    GIT_TAG release-2.20.2
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
  )
  set(SDL2TTF_INSTALL OFF)
  FetchContent_MakeAvailable(SDL2_ttf)

  target_include_directories("${TARGET_NAME}" PUBLIC 
    ${sdl2_SOURCE_DIR}/include
    ${sdl2_image_SOURCE_DIR}/include
    ${sdl2_ttf_SOURCE_DIR}
  )
  target_link_libraries("${TARGET_NAME}" PUBLIC 
  SDL2::SDL2main SDL2::SDL2 SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf 
  )
endif()

target_include_directories(${TARGET_NAME} PRIVATE
  ${CMAKE_SOURCE_DIR}/Rift2D/
  ${glm_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/Data/
  3rdParty/imgui
  3rdParty/implot
)

# compile at max warning level + treat warnings as errors
target_compile_options(${TARGET_NAME} PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)

if(EMSCRIPTEN)
  set(EMSCRIPTEN_COMPILE_FLAGS "${EMSCRIPTEN_LINK_FLAGS} -sUSE_SDL=2 -sUSE_SDL_IMAGE=2 -sUSE_SDL_TTF=2 -g")
  set(EMSCRIPTEN_LINK_FLAGS "${EMSCRIPTEN_LINK_FLAGS} -sUSE_SDL=2 -sUSE_SDL_IMAGE=2 -sUSE_SDL_TTF=2 -g -sALLOW_MEMORY_GROWTH --preload-file \"${CMAKE_SOURCE_DIR}/Data@/\" -sSDL2_IMAGE_FORMATS=['tga','png']")

  # work around https://github.com/emscripten-core/emscripten/issues/11513
  set(EMSCRIPTEN_LINK_FLAGS "${EMSCRIPTEN_LINK_FLAGS} -fno-stack-protector")

  # Use the Emscripten toolchain
  set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/EmscriptenToolchain.cmake)

  # Additional settings for Emscripten build
  set_target_properties(${TARGET_NAME} PROPERTIES
      COMPILE_FLAGS "${EMSCRIPTEN_COMPILE_FLAGS}"
      LINK_FLAGS "${EMSCRIPTEN_LINK_FLAGS}"
  )

  # Have emscripten generate a html page too.
  set(CMAKE_EXECUTABLE_SUFFIX ".html")
  
elseif(WIN32)

  # add post build commands
  add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
      COMMAND "${CMAKE_COMMAND}" -E copy "${SDL2_LIBRARY_DLL}" "$<TARGET_FILE_DIR:${TARGET_NAME}>"
  )
  add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
      COMMAND "${CMAKE_COMMAND}" -E copy "${SDL2_IMAGE_LIBRARY_DLL}" "$<TARGET_FILE_DIR:${TARGET_NAME}>"
  )
  add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
      COMMAND "${CMAKE_COMMAND}" -E copy "${SDL2_TTF_LIBRARY_DLL}" "$<TARGET_FILE_DIR:${TARGET_NAME}>"
  )
  add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/Data" "$<TARGET_FILE_DIR:${TARGET_NAME}>/Data"

    
  )

  set_target_properties(${TARGET_NAME} PROPERTIES
        LINK_FLAGS "/SUBSYSTEM:CONSOLE"
    )
  
endif()
