
#ifndef REVERSI_MANUALLOGIC_H
#define REVERSI_MANUALLOGIC_H


#include "GameLogic.h"
#include "Player.h"
#include "Board.h"

/**
 *  ManualLogic.
 *
 *  @param board    the game's board.
 *  @param player1  the first player.
 *  @param player2  the second color.
 */
class FlipMoveLogic : public GameLogic {
public:
    FlipMoveLogic(Board *board, Player *player1, Player *player2);
    virtual int checkOpt(Color color);
    virtual void scanAround(int row, int column, Color originColor, Color negColor);
    void scanAround(int row, int column, Color playerColor, Color negColor, Action act);
    

private:
    void simulateInPath(int i, int j, int changeRow, int changeColumn, Color playerColor, Color negColor);
    void flip(int x, int y, Color color);
    void moveInPath(int i, int j, int changeRow, int changeColumn, Color originColor, Color negColor);

protected:
    int counter;
    Player *player1;
    Player *player2;
};


#endif //REVERSI_MANUALLOGIC_H
