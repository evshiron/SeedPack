cmake_minimum_required(VERSION 3.3)
project(SeedPack)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp SeedPack.cpp SeedPack.h SeedBox.cpp SeedBox.h SeedProduct.cpp SeedProduct.h)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

add_executable(SeedCup ${SOURCE_FILES})