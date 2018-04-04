cmake_minimum_required(VERSION 3.8)
project(learn_cpp)

set(CMAKE_CXX_STANDARD 17)

add_executable(enable_shared_from_this enable_shared_from_this.cpp)
add_executable(lambda lambda.cpp)
add_executable(mutex mutex.cpp)
add_executable(future future.cpp)