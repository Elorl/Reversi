
#include "Board.h"
#include <cmath>
using namespace std;

/*****************************************************************************************************
* function name: Board - constructor							        	                         *
* the input:        			                                                                     *
* the output: -                                                                                      *
* the function operation: -                                                                          *
*****************************************************************************************************/
Board::Board(int rows, int columns) : rowsNum(rows), colsNum(columns) {
    //allocating boardArr
    boardArr = new Cell *[rowsNum];
    for (int i = 0; i < rowsNum; i++) {
        boardArr[i] = new Cell[colsNum];
    }

    //fill the matrix with space char.
    for(int row = 0; row < rowsNum; row++) {
        for (int column = 0; column < colsNum; column++) {
            this->boardArr[row][column].setX(row);
            this->boardArr[row][column].setY(column);
        }
    }
    // getting middle
    int midRow = ceil((double) rowsNum/ 2);
    int midCol = ceil((double) colsNum / 2);

    //starting position
    this->boardArr[midRow - 1][midCol - 1].setColor(White);
    this->boardArr[midRow][midCol].setColor(White);
    this->boardArr[midRow - 1][midCol].setColor(Black);
    this->boardArr[midRow][midCol - 1].setColor(Black);

    }

/*****************************************************************************************************
* function name: Board - destructor							        	                             *
* the input:        			                                                                     *
* the output: -                                                                                      *
* the function operation: -                                                                          *
*****************************************************************************************************/
Board::~Board() {
    for (int i = 0; i < rowsNum; i++) {
        delete[] boardArr[i];
    }
    delete[] boardArr;
}

/*****************************************************************************************************
* function name: getRowsNum.        							        	                         *
* the input:        			                                                                     *
* the output: the function return the amount of rows in the board                                    *
* the function operation: -                                                                          *
*****************************************************************************************************/
int Board::getRowsNum() {
    return rowsNum;
}

/*****************************************************************************************************
* function name: getColumnsNum.        							        	                         *
* the input:        			                                                                     *
* the output: the function return the amount of columns in the board.                                *
* the function operation: -                                                                          *
*****************************************************************************************************/
int Board::getColumnsNum() {
    return colsNum;
}

/*****************************************************************************************************
* function name: setBoardArr.        							        	                         *
* the input: a cell object       			                                                         *
* the output: -                                                                                      *
* the function operation: update the boardArr.                                                       *
*****************************************************************************************************/
void Board::setBoardArr(Cell **updatedArr) {
    for(int i = 0; i < rowsNum; i ++) {
        for(int j = 0 ; j < colsNum; j++) {
            boardArr[i][j] = updatedArr[i][j];
        }
    }
}
