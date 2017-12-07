cmake_minimum_required(VERSION 3.8)
project(Reversi)

set(CMAKE_CXX_STANDARD 98)
add_subdirectory(lib/googletest-release-1.8.0)
include_directories(lib/googletest-release-1.8.0/googletest/include)

set(SOURCE_FILES src/main.cpp src/Board.cpp src/Board.h src/ManualPlayer.cpp src/ManualPlayer.h src/Game.cpp src/Game.h src/Counter.cpp src/Counter.h src/Cell.cpp src/Cell.h src/Player.cpp src/Player.h src/color.h src/GameLogic.cpp src/GameLogic.h src/FlipMoveLogic.cpp src/FlipMoveLogic.h src/AIPlayer.cpp src/AIPlayer.h src/UserInterface.h src/ConsoleUI.cpp src/ConsoleUI.h)
set(TEST_FILES
        # Board Test
        test/test_board.cpp
        test/test_logic.cpp test/test_AiPlayer.cpp test/test_logic.cpp test/test_board.cpp test/test_AiPlayer.cpp test/gtest_main.cpp)

add_executable(Reversi ${SOURCE_FILES})
add_executable(tests test/gtest_main.cpp ${TEST_FILES} ${SOURCE_FILES} test/test_logic.cpp test/test_AiPlayer.cpp test/test_logic.cpp test/test_board.cpp test/test_AiPlayer.cpp test/gtest_main.cpp)
target_link_libraries(tests gtest gtest_main)
add_test(tests tests)