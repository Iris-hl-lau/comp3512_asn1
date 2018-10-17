cmake_minimum_required(VERSION 3.12)
project(comp3512_asn1)

set(CMAKE_CXX_STANDARD 14)

add_executable(comp3512_asn1 main.cpp)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")