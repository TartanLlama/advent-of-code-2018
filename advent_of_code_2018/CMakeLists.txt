﻿# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("advent_of_code_2018")

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /permissive-")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(range-v3 CONFIG REQUIRED)
link_libraries(meta range-v3)
include_directories(include)

add_subdirectory ("1_chronal_calibration")
add_subdirectory ("2_inventory_management_system")
add_subdirectory ("3_no_matter_how_you_slice_it")
