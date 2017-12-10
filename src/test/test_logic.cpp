#include "gtest/gtest.h"
#include "../client/Board.h"
#include "../client/FlipMoveLogic.h"
#include "../client/ManualPlayer.h"
#include "../client/ConsoleUI.h"

TEST(test_logic, NumOptions) {
    Board board(8, 8);
    Board board2(2, 2);
    Board board3(4,4);
    ConsoleUI consoleUI;
    ManualPlayer w(White, consoleUI, &board);
    ManualPlayer b(Black, consoleUI, &board);

    FlipMoveLogic l(&board, &b, &w);
    EXPECT_EQ(l.checkOpt(b.getType()), 4);
    for (int i = 0; i < board.getRowsNum(); i++) {
        for (int j = 0; j < board.getColumnsNum(); j++) {
            board.boardArr[i][j].setColor(White);
        }
    }
    board.boardArr[7][7].setColor(Empty);
    EXPECT_EQ(l.checkOpt(b.getType()), 0);
    for (int i = 0; i < board.getRowsNum(); i++) {
        for (int j = 0; j < board.getColumnsNum(); j++) {
            board.boardArr[i][j].setColor(Empty);
        }
    }
    EXPECT_EQ(l.checkOpt(b.getType()), 0);
    FlipMoveLogic l2(&board2, &b, &w);
    //consoleUI.printBoard(board2);
    EXPECT_EQ(l2.checkOpt(b.getType()), 0);
    FlipMoveLogic l3(&board3, &b, &w);
    //consoleUI.printBoard(board3);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            board3.boardArr[i][j].setColor(Black);
        }
    }
    board3.boardArr[1][0].setColor(Empty);
    board3.boardArr[3][0].setColor(White);
    EXPECT_EQ(l3.checkOpt(w.getType()), 1);
}

TEST(test_logic, Flips) {
    Board board(8, 8);
    ConsoleUI consoleUI;
    ManualPlayer w(White, consoleUI, &board);
    ManualPlayer b(Black, consoleUI, &board);
    FlipMoveLogic l(&board, &b, &w);
    for(int i = 0; i<board.getRowsNum(); i++) {
        for(int j = 0; j<board.getColumnsNum(); j++) {
            board.boardArr[i][j].setColor(Empty);
        }
    }
    for(int i = 1; i < board.getRowsNum() - 1; i++) {
        board.boardArr[i][0].setColor(White);
    }
    board.boardArr[7][0].setColor(Black);
    for(int j = 1; j < board.getColumnsNum() - 1; j++) {
        board.boardArr[0][j].setColor(White);
    }
    board.boardArr[0][7].setColor(Black);
    board.boardArr[0][0].setColor(Empty);
    //consoleUI.printBoard(board);
    b.setCount(2);
    w.setCount(12);
    l.scanAround(0,0, b.getType(), w.getType());
    int s = b.getCount();
    //consoleUI.printBoard(board);
    EXPECT_EQ(s, 15);
}