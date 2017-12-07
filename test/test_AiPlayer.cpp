#include "gtest/gtest.h"
#include "../src/Board.h"
#include "../src/AIPlayer.h"
#include "../src/FlipMoveLogic.h"
#include "../src/ManualPlayer.h"
#include "../src/ConsoleUI.h"

TEST(test_AiPlayer, options) {
    int *inputX , *inputY;
    inputX = new int;
    inputY = new int;
    Board board(5,5);
    ConsoleUI consoleUI;
    ManualPlayer b(Black, consoleUI);
    AIPlayer w(White, &board);
    FlipMoveLogic l(&board, &b, &w);
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            board.boardArr[i][j].setColor(Empty);
        }
    }
    b.setCount(7);
    w.setCount(1);
    w.setLogic(&l);
    w.setRivalCounter(b.getCounter());
    board.boardArr[0][0].setColor(Black);
    board.boardArr[1][1].setColor(Black);
    board.boardArr[1][2].setColor(Black);
    board.boardArr[1][3].setColor(Black);
    board.boardArr[0][4].setColor(Black);
    board.boardArr[2][0].setColor(Black);
    board.boardArr[2][4].setColor(Black);
    board.boardArr[1][4].setColor(White);
    //consoleUI.printBoard(board);
    w.chooseOption(inputX, inputY);
    EXPECT_EQ(*inputX, 1);
    EXPECT_EQ(*inputY, 0);
    //consoleUI.printBoard(board);
}