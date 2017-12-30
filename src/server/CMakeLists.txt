cmake_minimum_required(VERSION 3.8)
project(server)

set(CMAKE_CXX_STANDARD 98)

<<<<<<< HEAD
set(SERVER_SOURCE_FILES  server/main.cpp server/Server.cpp server/Server.h server/CommandsManager.cpp server/CommandsManager.h server/ClientHandler.cpp server/ClientHandler.h server/Close.cpp server/Close.h server/Command.h server/Join.cpp server/Join.h server/ListGame.cpp server/ListGame.h server/Play.cpp server/Play.h server/Room.cpp server/Room.h server/Start.cpp server/Start.h)
=======
set(CMAKE_CXX_FLAGS -pthread)
set(SERVER_SOURCE_FILES server/main.cpp server/Server.cpp server/Server.h server/CommandsManager.cpp server/CommandsManager.h server/ClientHandler.cpp server/ClientHandler.h server/Close.cpp server/Close.h server/Command.h server/Join.cpp server/Join.h server/ListGame.cpp server/ListGame.h server/Play.cpp server/Play.h server/Room.cpp server/Room.h server/Start.cpp server/Start.h)

>>>>>>> 8a1d32d8c767f36555dbf75f65edfbe054d0d7fe
add_executable(server ${SERVER_SOURCE_FILES})