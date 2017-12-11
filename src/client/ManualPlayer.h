
#ifndef REVERSI_ManualPlayer_H
#define REVERSI_ManualPlayer_H

#include "color.h"
#include "Player.h"
#include "UserInterface.h"
#include "Client.h"


/**
 *  Player.
 *
 *  @param color    the player's color(Black / White).
 */

class ManualPlayer: public Player{
public:
    ManualPlayer(Color color, UserInterface& ui, Board* b);
    ManualPlayer(Color color, UserInterface& ui, Board* b, Client* clnt);
    Color getType();
    void chooseOption(int *x, int *y);
    virtual void send(int *x, int *y);
    virtual void noMove();
private:
    Board* board;
    UserInterface& ui;
    Client* client;
};


#endif //REVERSI_ManualPlayer_H
