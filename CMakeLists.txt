cmake_minimum_required(VERSION 3.8)
project(ex1)

set(CMAKE_CXX_STANDARD 98)
add_subdirectory(lib/googletest-release-1.8.0)
include_directories(lib/googletest-release-1.8.0/googletest/include)

set(SOURCE_FILES src/main.cpp src/Board.cpp include/Board.h src/ManualPlayer.cpp include/ManualPlayer.h src/Game.cpp include/Game.h src/Counter.cpp include/Counter.h src/Cell.cpp include/Cell.h src/Player.cpp include/Player.h include/color.h src/GameLogic.cpp include/GameLogic.h src/FlipMoveLogic.cpp include/FlipMoveLogic.h src/AIPlayer.cpp include/AIPlayer.h include/UserInterface.h src/ConsoleUI.cpp include/ConsoleUI.h)
set(TEST_FILES
        # Board Test
        test/test_board.cpp
        test/test_logic.cpp test/test_AiPlayer.cpp test/test_logic.cpp test/test_board.cpp test/test_AiPlayer.cpp test/gtest_main.cpp)

add_executable(ex1 ${SOURCE_FILES})
add_executable(tests test/gtest_main.cpp ${TEST_FILES} ${SOURCE_FILES} test/test_logic.cpp test/test_AiPlayer.cpp test/test_logic.cpp test/test_board.cpp test/test_AiPlayer.cpp test/gtest_main.cpp)
target_link_libraries(tests gtest gtest_main)
add_test(tests tests)