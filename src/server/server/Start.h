//Avner Merhavi 203090436

// 26/12/17.
//

#ifndef REVERSI_START_H
#define REVERSI_START_H


#include <vector>
#include "Command.h"

class Start : public Command {
public:
    int execute(vector<void*> args);
};


#endif //REVERSI_START_H

