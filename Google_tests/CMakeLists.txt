project(GoogleTest)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


add_executable(Google_Tests_run sunTracer_test1.cpp)

target_link_libraries(Google_Tests_run SunTracer_lib)


target_link_libraries(Google_Tests_run gtest gtest_main)