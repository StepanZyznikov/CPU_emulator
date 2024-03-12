cmake_minimum_required(VERSION 3.27)
project(CPU_emulator)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

add_executable(main main.cpp)

add_library(cpu STATIC CPU.h)
set_target_properties(cpu PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(main PRIVATE cpu)

# Google tests
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

#For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(tests tests.cpp)
target_link_libraries(tests PRIVATE stack GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)