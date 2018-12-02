# CMakeList.txt : CMake project for advent_of_code_2018, include source and define
# project specific logic here.
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (part1 "part1.cpp")
add_executable (part2 "part2.cpp")

find_package(range-v3 CONFIG REQUIRED)
target_link_libraries(part1 PRIVATE meta range-v3)
target_link_libraries(part2 PRIVATE meta range-v3)

# TODO: Add tests and install targets if needed.
