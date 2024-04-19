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

# cmake -DENABLE_COVERAGE=true
if(ENABLE_COVERAGE)
  set(CMAKE_CXX_FLAGS "-O0 -coverage")

  find_program(LCOV lcov REQUIRED)
  find_program(GENHTML genhtml REQUIRED)

  add_custom_target(coverage
    COMMAND ${LCOV} --ignore-errors inconsistent --directory . --capture --output-file coverage.info 
    COMMAND ${GENHTML} --ignore-errors inconsistent --demangle-cpp -o coverage coverage.info
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
endif()

add_executable(avl_test ${CMAKE_CURRENT_SOURCE_DIR}/tests/avl_tests.cc)
target_include_directories(avl_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(avl_test GTest::gtest_main)

add_executable(ring-buffer_test ${CMAKE_CURRENT_SOURCE_DIR}/tests/ring-buffer_tests.cc)
target_include_directories(ring-buffer_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(ring-buffer_test GTest::gtest_main)

add_executable(trie_test ${CMAKE_CURRENT_SOURCE_DIR}/tests/trie_tests.cc)
target_include_directories(trie_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(trie_test GTest::gtest_main)

add_executable(segment-tree_test ${CMAKE_CURRENT_SOURCE_DIR}/tests/segment-tree_tests.cc)
target_include_directories(segment-tree_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(segment-tree_test GTest::gtest_main)

# ctest configuration
include(GoogleTest)
gtest_discover_tests(avl_test)
gtest_discover_tests(ring-buffer_test)
gtest_discover_tests(trie_test)
gtest_discover_tests(segment-tree_test)
