//Avner Merhavi 203090436

// 26/12/17.
//

#ifndef REVERSI_COMMAND_H
#define REVERSI_COMMAND_H
#include <iostream>

using namespace std;
class Command {
    public:
    virtual int execute(vector<void*> args) = 0;
};


#endif //REVERSI_COMMAND_H
