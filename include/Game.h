/******************************************
* Student name: Elor Lichtziger
* Student: 308541739
* Exercise name: ex1
******************************************/

#ifndef EX1_GAME_H
#define EX1_GAME_H


#include "Board.h"
#include "Player.h"
#include "UserInterface.h"

/**
 *  Game.
 *
 *  @param board    the game's board.
 *  @param player1  the first player.
 *  @param player2  the second color.
 *  @param logic    the logic of the game.
 */
class Game {
public:
    Game(Board *board, Player *player1, Player *player2, GameLogic *logic, UserInterface& ui);
    void run();
private:
    Board *board;
    Player *player1;
    Player *player2;
    GameLogic *logic;
    UserInterface& ui;
};


#endif //EX1_GAME_H
