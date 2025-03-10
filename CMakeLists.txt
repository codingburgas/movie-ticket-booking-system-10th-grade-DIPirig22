cmake_minimum_required(VERSION 2.2)  # CMake version check
project(movie-ticket-booking-system-10th-grade-DIPirig22)               # Create project "simple_example"
set(CMAKE_CXX_STANDARD 14)            # Enable c++14 standard

# Add main.cpp file of the project root directory as a source file
set(SOURCE_FILES main.cpp
        func/menu.h
        scr/main.cpp
        scr/utility.cpp
        loginPage/menu.cpp
        func/menu.h
        func/menu.h)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(movie-ticket-booking-system-10th-grade-DIPirig22 ${SOURCE_FILES}
        scr/main.cpp
        scr/utility.cpp
        func/menu.h
        loginPage/menu.cpp)