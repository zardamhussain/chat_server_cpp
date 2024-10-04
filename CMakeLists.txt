
cmake_minimum_required(VERSION 3.15)
project(crow_server)

set(INCLUDE_PATHS extra/crow/include extra/boost_1_86_0)

add_executable(crow_server main.cpp)

target_include_directories(crow_server PUBLIC ${INCLUDE_PATHS})