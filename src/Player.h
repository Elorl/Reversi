/******************************************
* Student name: Elor Lichtziger
* Student: 308541739
* Exercise name: ex1
******************************************/

#ifndef EX1_PLAYER_H
#define EX1_PLAYER_H


#include <iostream>
#include "color.h"
#include "Counter.h"

#include "GameLogic.h"

using namespace std;



class Player {
public:
    Player();
    Player(Color color);
    virtual ~Player();
    Color type;
    virtual int getCount();
    virtual Color getType() = 0;
    virtual char getSymbol();
    virtual void increase(int k = 1);
    virtual void decrease(int k = 1);
    virtual void setCount(int count);
    virtual void chooseOption(int *x, int *y) = 0;
    void setLogic(GameLogic *logic);
    Counter *getCounter();
    void setRivalCounter(Counter *rivalCounter);
protected:
    char symbol;
    Counter* counter;
    GameLogic* logic;
    Color rivalColor;
    Counter* rivalCounter;
};


#endif //EX1_PLAYER_H
