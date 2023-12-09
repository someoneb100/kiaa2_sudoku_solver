# Make solver library
add_library(
    solver
    src/solver.cpp inc/solver.hpp
    src/board.cpp inc/board.hpp
)
target_include_directories(solver PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/inc")
target_link_libraries(solver PUBLIC dlx)

# Make solver test
add_executable(test_solver test.cpp)
target_link_libraries(test_solver PRIVATE solver)
add_test(
    NAME solver
    COMMAND test_solver
)



# Add benchmark executable and use parallel processing if enabled
# requires to be ran with command:
# cmake -D BENCHMARK=ON ..
if(${BENCHMARK})
    set(BENCHMARK_FLAG ON)
else()
    set(BENCHMARK_FLAG OFF)
endif()
message(STATUS "Benchmark: ${BENCHMARK_FLAG}")
if(${BENCHMARK_FLAG})
    list(
        APPEND CMAKE_MODULE_PATH
        ${PROJECT_SOURCE_DIR}/cmake
    )

    # Collect dataset
    set(DATASET_URL http://magictour.free.fr/topn234)
    if(NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/dataset.txt")
        message(STATUS "Downloading dataset from ${DATASET_URL}")
        file(DOWNLOAD ${DATASET_URL} "${CMAKE_CURRENT_BINARY_DIR}/dataset.txt")
    endif()

    # Building benchmark executable
    add_executable(benchmark benchmark.cpp)
    target_link_libraries(benchmark PRIVATE solver)
    find_package(OpenMP)
    if(${OpenMP_FOUND})
        target_link_libraries(benchmark PRIVATE OpenMP::OpenMP_CXX)
    else()
        target_compile_options(benchmark PRIVATE "-Wno-unknown-pragmas")
    endif()
endif()
