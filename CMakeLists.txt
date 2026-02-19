cmake_minimum_required(VERSION 3.15)
project(Ann_Retrievial)

set(CMAKE_CXX_STANDARD 17)
add_library(fvecs_reader STATIC data/fvecs_reader/fvecs_reader.cpp)
target_include_directories(fvecs_reader  PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/data/fvecs_reader)

add_executable(Test_Reader src/test_fvecs_reader.cpp)
target_include_directories(Test_Reader PRIVATE
        data/fvecs_reader)
target_link_libraries(Test_Reader PRIVATE fvecs_reader)

add_executable(Ann_Retrievial src/main.cpp
        src/test_fvecs_reader.cpp)

target_include_directories(Ann_Retrievial PRIVATE
${CMAKE_CURRENT_SOURCE_DIR}/data/fvecs_reader)
target_link_libraries(Ann_Retrievial PRIVATE fvecs_reader)

