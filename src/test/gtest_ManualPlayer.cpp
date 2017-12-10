#include "gtest/gtest.h"
#include "../client/Board.h"
#include "../client/AIPlayer.h"
#include "../client/ManualPlayer.h"
#include "../client/ConsoleUI.h"

TEST(test_ManualPlayer, color){
    ConsoleUI consoleUI;
    Board board(8,8);
    ManualPlayer player(Black, consoleUI, &board);
    EXPECT_EQ('X', player.getSymbol());
}
