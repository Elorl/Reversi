
#ifndef EX1_ManualPlayer_H
#define EX1_ManualPlayer_H

#include "color.h"
#include "Player.h"
#include "UserInterface.h"


/**
 *  Player.
 *
 *  @param color    the player's color(Black / White).
 */

class ManualPlayer: public Player{
private:
    UserInterface& ui;
public:
    ManualPlayer(Color color, UserInterface& ui);
    Color getType();
    virtual void chooseOption(int *x, int *y);
};


#endif //EX1_ManualPlayer_H
