
#ifndef REVERSI_BOARD_H
#define REVERSI_BOARD_H


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


#endif //REVERSI_BOARD_H
