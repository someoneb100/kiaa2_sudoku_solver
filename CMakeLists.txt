cmake_minimum_required(VERSION 3.16)
project(SudokuSolverDLX VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-g -O0 -Wall -Wextra -Werror")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-O3")


enable_testing()

add_subdirectory(dlx)
add_subdirectory(solver)
add_subdirectory(app)