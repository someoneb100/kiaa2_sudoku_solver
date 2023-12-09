# kiaa2_sudoku_solver

[![Language](https://img.shields.io/badge/language-C%2B%2B-blue.svg)](https://en.cppreference.com/)
[![Qt](https://img.shields.io/badge/Qt-6-blue.svg)](https://www.qt.io/)
[![CMake](https://img.shields.io/badge/CMake-3.16-green.svg)](https://cmake.org/)

---

A Sudoku solver implemented in C++ with a focus on efficiency using the Dancing Links algorithm. The project includes a general-purpose Dancing Links (DLX) library for solving any exact cover problem and a specialized solver library tailored for solving Sudoku puzzles. The Qt framework (version 6) is utilized for the graphical user interface, providing an interactive environment for input and visualization.

---

The project supports benchmarking with parallelization using OpenMP. Before building the project, make sure to initialize and update the submodules by running the command `git submodule update --recursive`. To enable benchmarking during the build, use the flag `-DBENCHMARK=ON` with CMake. Benchmarking utilizes datasets from [Magic Tour](http://magictour.free.fr/topn234), including challenging Sudoku puzzles.
