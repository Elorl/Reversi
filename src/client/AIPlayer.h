
#ifndef REVERSI_AIPLAYER_H
#define REVERSI_AIPLAYER_H


#include "Player.h"
#include "GameLogic.h"
#include "Board.h"
#include "UserInterface.h"

/**
 *  AIPlayer.
 */
class AIPlayer : public Player {
public:
    AIPlayer(Color color, UserInterface& ui, Board* board);
    ~AIPlayer();
    Color getType();
    void chooseOption(int *x, int *y);
    void freeMatrix(Cell **matrix);
    virtual void send(int *x, int *y);
    virtual void noMove();
private:
    Board* board;
    UserInterface& ui;
    Cell** playerOptions;
    Cell** initialBoardBackup;
    Cell** subBoardbackup;
    Cell** rivalOptions;
    int getMaxRivalMove();
    Cell chooseMinMax();
};


#endif //REVERSI_AIPLAYER_H
