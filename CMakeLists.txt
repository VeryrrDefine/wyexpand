cmake_minimum_required(VERSION 3.27.0)
project(wyexpand VERSION 0.1.1 LANGUAGES CXX)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# set output executable file directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


add_library(wyexpand SHARED src/wyexpand.cpp)

add_executable(wyexpand_executable src/exec.cpp)
target_link_libraries(wyexpand_executable PRIVATE wyexpand)
target_include_directories(wyexpand
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# include(FetchContent)
# FetchContent_Declare(
#   googletest
#   URL https://github.com/google/googletest/archive/refs/heads/main.zip
# )
# FetchContent_MakeAvailable(googletest)

# target_link_libraries(wyexpand_tests PRIVATE wyexpand gtest_main)
# enable_testing()
# add_test(NAME wyexpand_tests COMMAND wyexpand_tests)
