cmake_minimum_required(VERSION 3.2)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Project3)

set(SFML_DIR "/usr/local/Cellar/sfml/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
add_executable(Project3 main.cpp Board.cpp Board.hpp TextureHandler.h TileBehaviors.cpp TileBehaviors.h )
target_link_libraries(Project3 sfml-graphics sfml-audio)