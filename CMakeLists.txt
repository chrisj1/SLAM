cmake_minimum_required(VERSION 3.6)
project(Slam)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/Lidar.cpp
        src/main.cpp
        src/Roomba.cpp
        src/PaintArea.cpp
        src/Calculations.cpp)

include_directories(include)

set(SOUCRE_FILES
        include/Calculations.h
        include/Lidar.h
        include/PaintArea.h
        include/Roomba.h)

find_package(Qt5Widgets REQUIRED)

add_executable(Slam ${SOURCE_FILES})


target_link_libraries(Slam Qt5::Widgets)
