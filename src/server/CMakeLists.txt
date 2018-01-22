cmake_minimum_required(VERSION 3.8)
project(server)

set(CMAKE_CXX_STANDARD 98)

set(CMAKE_CXX_FLAGS -pthread)
set(SERVER_SOURCE_FILES server/main.cpp server/Server.cpp server/Server.h server/CommandsManager.cpp server/CommandsManager.h server/ClientHandler.cpp server/ClientHandler.h server/Close.cpp server/Close.h server/Command.h server/Join.cpp server/Join.h server/ListGame.cpp server/ListGame.h server/Play.cpp server/Play.h server/Room.cpp server/Room.h server/Start.cpp server/Start.h server/ThreadPool.cpp server/ThreadPool.h  server/Task.h)

add_executable(server ${SERVER_SOURCE_FILES})
