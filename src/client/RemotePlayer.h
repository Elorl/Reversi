
#ifndef REVERSI_REMOTEPLAYER_H
#define REVERSI_REMOTEPLAYER_H


#include "Player.h"
#include "Client.h"
#include "UserInterface.h"

/**
 *  RemotePlayer.
 *
 *  @param color    the player's color.
 *  @param ui       the ui object.
 *  @param clnt     the client object.
 */
class RemotePlayer: public Player{
public:
    RemotePlayer(Color color, UserInterface& ui, Client* clnt);
    Color getType();
    void chooseOption(int *x, int *y);
    virtual void send(int *x, int *y);
private:
    UserInterface& ui;
    Client* client;
};


#endif //REVERSI_REMOTEPLAYER_H
