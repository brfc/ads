cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(ads VERSION 1.0)

# configure googletest
include(FetchContent)
FetchContent_Declare(
	googletest
	URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(avl_test ${CMAKE_CURRENT_SOURCE_DIR}/tests/avl_tests.cc)
target_include_directories(avl_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(avl_test GTest::gtest_main)

add_executable(ring-buffer_test ${CMAKE_CURRENT_SOURCE_DIR}/tests/ring-buffer_tests.cc)
target_include_directories(ring-buffer_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(ring-buffer_test GTest::gtest_main)

# ctest configuration
include(GoogleTest)
gtest_discover_tests(avl_test)
gtest_discover_tests(ring-buffer_test)