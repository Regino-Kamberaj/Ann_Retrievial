cmake_minimum_required(VERSION 3.15)
project(Ann_Retrievial)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ==============================================
# Libraries
# ==============================================
add_library(fvecs_reader STATIC
        libraries/fvecs_reader/fvecs_reader.cpp
)
target_include_directories(fvecs_reader PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/fvecs_reader)

add_library(distances STATIC
        libraries/distances/distances.cpp)
target_include_directories(distances PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/distances)

add_library(dataset STATIC
        libraries/dataset/dataset.cpp
)
target_include_directories(dataset PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/dataset)
target_link_libraries(dataset PRIVATE fvecs_reader)

add_library(knn STATIC
        libraries/kNN/kNN.cpp
)
target_include_directories(knn PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/kNN)
target_link_libraries(knn PRIVATE
        distances dataset)

# ==============================================
# Main
# ==============================================
add_executable(Ann_Retrievial src/main.cpp)
target_link_libraries(Ann_Retrievial PRIVATE
        fvecs_reader distances dataset knn)
target_include_directories(Ann_Retrievial PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/fvecs_reader
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/distances
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/dataset
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/knn)

# ==============================================
# Test_fvecs
# ==============================================
add_executable(Test_Reader src/test_fvecs_reader.cpp)
target_link_libraries(Test_Reader PRIVATE fvecs_reader)
target_include_directories(fvecs_reader PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/fvecs_reader)

# ==============================================
# Test_sequential
# ==============================================
add_executable(Test_Sequential src/test_sequential.cpp)
target_link_libraries(Test_Sequential PRIVATE
        fvecs_reader distances dataset knn
)
target_include_directories(Test_Sequential PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/fvecs_reader
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/distances
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/dataset
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/knn
)

# ==============================================
# Test_accuracy
# ==============================================
add_executable(Test_Accuracy src/test_accuracy.cpp)
target_link_libraries(Test_Accuracy PRIVATE
        fvecs_reader distances dataset knn
)
target_include_directories(Test_Accuracy PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/fvecs_reader
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/distances
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/dataset
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/knn
)