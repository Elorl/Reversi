
#ifndef EX1_AIPLAYER_H
#define EX1_AIPLAYER_H


#include "Player.h"
#include "GameLogic.h"
#include "Board.h"

class AIPlayer : public Player {
public:
    AIPlayer(Color color, Board* board);
    ~AIPlayer();
    Color getType();
    virtual void chooseOption(int *x, int *y);
    void freeMatrix(Cell **matrix);

private:
    Board* board;
    Cell** playerOptions;
    Cell** initialBoardBackup;
    Cell** subBoardbackup;
    Cell** rivalOptions;
    int getMaxRivalMove();
    Cell chooseMinMax();
};


#endif //EX1_AIPLAYER_H
