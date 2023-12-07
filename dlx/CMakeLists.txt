# Make dlx library
add_library(
    dlx
    src/dlx.cpp inc/dlx.hpp
    src/node.cpp inc/node.hpp
)
target_include_directories(dlx PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/inc")

# Make dlx test
add_executable(test_dlx test.cpp)
target_link_libraries(test_dlx PRIVATE dlx)
add_test(
    NAME dlx
    COMMAND test_dlx
)