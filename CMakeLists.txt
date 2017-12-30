cmake_minimum_required(VERSION 3.8)
project(Reversi)

set(CMAKE_CXX_STANDARD 98)
add_subdirectory(lib/googletest-release-1.8.0)
include_directories(lib/googletest-release-1.8.0/googletest/include)

set(SOURCE_FILES src/client/main.cpp src/client/Board.cpp src/client/Board.h src/client/ManualPlayer.cpp src/client/ManualPlayer.h src/client/Game.cpp src/client/Game.h src/client/Counter.cpp src/client/Counter.h src/client/Cell.cpp src/client/Cell.h src/client/Player.cpp src/client/Player.h src/client/color.h src/client/GameLogic.cpp src/client/GameLogic.h src/client/FlipMoveLogic.cpp src/client/FlipMoveLogic.h src/client/AIPlayer.cpp src/client/AIPlayer.h src/client/UserInterface.h src/client/ConsoleUI.cpp src/client/ConsoleUI.h src/client/Client.cpp src/client/Client.h src/client/RemotePlayer.cpp src/client/RemotePlayer.h)
set(TEST_FILES
        # Board Test
        src/test/test_board.cpp
        src/test/test_logic.cpp src/test/test_AiPlayer.cpp src/test/test_logic.cpp src/test/test_board.cpp src/test/test_AiPlayer.cpp src/test/gtest_main.cpp)

add_executable(Reversi ${SOURCE_FILES} src/client/Client.cpp src/client/Client.h src/client/RemotePlayer.cpp src/client/RemotePlayer.h)
add_executable(tests src/test/gtest_main.cpp ${TEST_FILES} ${SOURCE_FILES} src/test/test_logic.cpp src/test/test_AiPlayer.cpp src/test/test_logic.cpp src/test/test_board.cpp src/test/test_AiPlayer.cpp src/test/gtest_main.cpp src/test/gtest_ManualPlayer.cpp)
target_link_libraries(tests gtest gtest_main)
add_test(tests tests)