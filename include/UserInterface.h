//Avner Merhavi 203090436

// 29/11/17.
//

#ifndef EX1_USERINTERFACE_H
#define EX1_USERINTERFACE_H


#include "Board.h"
#include "Player.h"

class UserInterface {
public:
    virtual void printBoard(Board& b) = 0;
    virtual void printPoints(int bPoints, int wPoints) = 0;
    virtual void printOptions(Cell** optionsMatrix, int rows, int cols) = 0;
    virtual void requestIndices(bool isFirstTime = true) = 0;
    virtual void announceTurnPlayer(Player &player) = 0;
    virtual void noPossibleMove() = 0;
    virtual void gameOver() = 0;
    virtual char choosePlayerType() = 0;
};


#endif //EX1_USERINTERFACE_H
