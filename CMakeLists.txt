cmake_minimum_required(VERSION 3.0)
project(SunTracerCpp)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE_FILES main.cpp)
add_executable(SunTracer_run ${SOURCE_FILES})

include_directories(SunTracer_lib)
add_subdirectory(SunTracer_lib)
target_link_libraries(SunTracer_run SunTracer_lib)


add_subdirectory(Google_tests)
