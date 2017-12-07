
#ifndef EX1_GAMELOGIC_H
#define EX1_GAMELOGIC_H

#include "color.h"
#include "Board.h"


/**
 *  GameLogic.
 *
 */
class GameLogic {
public:
    GameLogic(Board *board);
    ~GameLogic();
    virtual int checkOpt(Color color) = 0;
    virtual void scanAround(int row, int column, Color originColor, Color negColor) = 0;
    virtual bool isOptEmpty(int *x, int *y);
    virtual void clearOptions();
    virtual void setOptions(Cell** optionMatrix);
    virtual Cell **getOptionsMatrix();
protected:
    Cell** optionsMatrix;
    Board *board;
};


#endif //EX1_GAMELOGIC_H
