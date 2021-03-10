cmake_minimum_required(VERSION 3.17)
project(Offline_9__Branch___Bound_)

set(CMAKE_CXX_STANDARD 14)

add_executable(Offline_9__Branch___Bound_ main.cpp)
add_executable(brute brute.cpp)
add_executable(branchAndBound branchAndBound.cpp)
add_executable(bruteRecursive bruteRecursive.cpp)
add_executable(branchAndBoundCoordinate branchAndBoundCoordinate.cpp)
add_executable(branchAndBoundNew branchAndBoundNew.cpp)