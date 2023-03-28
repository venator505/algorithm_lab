cmake_minimum_required(VERSION 3.5)

project(algorithm_lab)

add_subdirectory(googletest)

include_directories(${PROJECT_SOURCE_DIR}/src)

enable_testing()

FILE(GLOB_RECURSE TESTFILES tests/*.cpp)

foreach(file ${TESTFILES})
    get_filename_component(execute_name ${file} NAME_WE)
    add_executable(${execute_name} ${file})
	target_link_libraries(${execute_name} GTest::gtest_main)
endforeach()