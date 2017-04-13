cmake_minimum_required(VERSION 3.6)
project(Slam)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
    Lidar.cpp
    main.cpp
    Roomba.cpp
    StepperMotor.cpp)

add_executable(Slam ${SOURCE_FILES})