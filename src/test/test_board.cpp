#include "gtest/gtest.h"
#include "../client/Board.h"

TEST(test_board, initialBoard) {
    Board b(8,8);
    EXPECT_EQ(b.boardArr[3][3].getColor(), White);
    EXPECT_EQ(b.boardArr[4][4].getColor(), White);
    EXPECT_EQ(b.boardArr[3][4].getColor(), Black);
    EXPECT_EQ(b.boardArr[4][3].getColor(), Black);
}