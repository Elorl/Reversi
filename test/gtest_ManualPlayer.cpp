#include "gtest/gtest.h"
#include "../src/Board.h"
#include "../src/AIPlayer.h"
#include "../src/ManualPlayer.h"
#include "../src/ConsoleUI.h"

TEST(test_ManualPlayer, color){
    ConsoleUI consoleUI;
    Board board(8,8);
    ManualPlayer player(Black, consoleUI, &board);
    EXPECT_EQ('X', player.getSymbol());
}