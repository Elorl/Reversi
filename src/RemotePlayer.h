
#ifndef REVERSI_REMOTEPLAYER_H
#define REVERSI_REMOTEPLAYER_H


#include "Player.h"
#include "Client.h"
#include "UserInterface.h"

class RemotePlayer: public Player{
public:
    RemotePlayer(Color color, UserInterface& ui, Client* clnt);
    Color getType();
    void chooseOption(int *x, int *y);
    virtual void send(int *x, int *y);
private:
    UserInterface& ui;
    Client* client = NULL;
};


#endif //REVERSI_REMOTEPLAYER_H
