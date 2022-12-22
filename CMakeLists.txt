cmake_minimum_required(VERSION 3.22)
project(Fahm VERSION 1.0)

# Place the binary in the root of the project

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

add_library(Fahm
    src/AudioHandler.cpp
    src/BaseWindow.cpp
    src/Entity.cpp
    src/EventQueue.cpp
    src/Fahm.cpp
    src/GameplayMenu.cpp
    src/InputHandler.cpp
    src/Menu.cpp
    src/MenuTools.cpp
    src/OJAsciiEngine.cpp
    src/PauseMenu.cpp
    src/TextHandler.cpp
    src/TextureHandler.cpp
    src/TileDisplayMenu.cpp
    src/Tilemap.cpp
    src/TilemapWindow.cpp
)

target_include_directories(Fahm

    PUBLIC
        $<INSTALL_INTERFACE:include>    
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>

    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)


# Find required libraries

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)

target_link_libraries(Fahm
    PUBLIC
        SDL2::SDL2
        SDL2_image
        SDL2_mixer
)

# Set compile options

set(CMAKE_CXX_FLAGS "-O3")

add_executable(Main main.cpp)

target_link_libraries(Main Fahm)
