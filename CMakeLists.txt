cmake_minimum_required(VERSION 3.6)
project(cs457_p1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    chat.cpp)

add_executable(cs457_p1 ${SOURCE_FILES})