cmake_minimum_required(VERSION 3.6)
project(Slam)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Lidar.cpp
        main.cpp
        Roomba.cpp
        StepperMotor.cpp
        PaintArea.cpp
        Calculations.cpp)

find_package(Qt5Widgets REQUIRED)

add_executable(Slam ${SOURCE_FILES})

target_link_libraries(Slam Qt5::Widgets)
