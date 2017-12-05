/******************************************
* Student name: Elor Lichtziger
* Student: 308541739
* Exercise name: ex1
******************************************/

#ifndef EX1_BOARD_H
#define EX1_BOARD_H


#include "Cell.h"

/**
 *  Board.
 *
 *  @param rows     number of rows.
 *  @param columns  number of columns.
 */
class Board {
public:
    Board(int rows, int columns);
    ~Board();
    Cell** boardArr;

    void setBoardArr(Cell **updatedArr);
    int getRowsNum();
    int getColumnsNum();
private:
    int rowsNum;
    int colsNum;
};


#endif //EX1_BOARD_H
