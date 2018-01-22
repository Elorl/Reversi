//Avner Merhavi 203090436

// 27/12/17.
//

#ifndef REVERSI_CLOSE_H
#define REVERSI_CLOSE_H


#include <vector>
#include "Command.h"
#include <iostream>
using namespace std;

class Close : public Command{
public:
    int execute(vector<void*> args);
};


#endif //REVERSI_CLOSE_H

