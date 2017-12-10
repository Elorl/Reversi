cmake_minimum_required(VERSION 3.8)
project(server)

set(CMAKE_CXX_STANDARD 98)

set(SERVER_SOURCE_FILES server/main.cpp server/Server.cpp server/Server.h )
add_executable(server ${SERVER_SOURCE_FILES})