cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

set(SDL2_PATH $ENV{SDL2_PATH})

project(SDL2Test)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} src)

# add_executable(SnakeGame src/main.cpp src/game.cpp src/controller.cpp src/renderer.cpp src/snake.cpp)
add_executable(SnakeGame WIN32 src/main.cpp src/game.cpp src/controller.cpp src/renderer.cpp src/snake.cpp)
# string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
# target_link_libraries(SnakeGame ${SDL2_LIBRARIES})
string(STRIP ${SDL2_LIBRARY} SDL2_LIBRARY)
target_link_libraries(SnakeGame ${SDL2_LIBRARY})