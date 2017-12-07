
#ifndef EX1_CELL_H
#define EX1_CELL_H


#include "color.h"

/**
 *  Board.
 *
 *  @param x      the cell's x cord.
 *  @param y      the cell's y cord.
 *  @param color  the cell's color.
 */
class Cell {
public:
    Cell(int x, int y, Color clr);
    Cell();
    int getX();
    int getY();
    Color getColor();
    void setColor(Color clr);
    void setX(int x);
    void setY(int y);
private:
    int xCord;
    int yCord;
    Color color;
};


#endif //EX1_CELL_H
