cmake_minimum_required(VERSION 3.22)
project(test)

set(CMAKE_CXX_STANDARD 23)

add_executable(test main.cpp db.cpp DiskStorage.cpp LevelNonZero.cpp LevelZero.cpp SSTable.cpp SSTableId.cpp operation.cpp)
