
#ifndef REVERSI_PLAYER_H
#define REVERSI_PLAYER_H


#include <iostream>
#include "color.h"
#include "Counter.h"

#include "GameLogic.h"

using namespace std;



class Player {
public:
    Player();
    Player(Color color);
    ~Player();
    Color type;
    virtual int getCount();
    virtual Color getType() = 0;
    virtual char getSymbol();
    virtual void increase(int k = 1);
    virtual void decrease(int k = 1);
    virtual void setCount(int count);
    virtual void chooseOption(int *x, int *y) = 0;
    virtual void send(int *x, int *y) = 0;
    void setLogic(GameLogic *logic);
    Counter *getCounter();
    void setRivalCounter(Counter *rivalCounter);
    bool sendToServer();
protected:
    char symbol;
    Counter* counter;
    GameLogic* logic;
    Color rivalColor;
    Counter* rivalCounter;
    bool sendToSrvr;
};


#endif //REVERSI_PLAYER_H
