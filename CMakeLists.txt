cmake_minimum_required(VERSION 3.16)
project(SudokuSolverDLX VERSION 1.0.0)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake-master)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-g -O0 -Wall -Wextra -Werror")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-O3")


enable_testing()

add_subdirectory(dlx)
add_subdirectory(solver)
add_subdirectory(app)