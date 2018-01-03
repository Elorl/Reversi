//Avner Merhavi 203090436

// 28/12/17.
//

#ifndef REVERSI_PLAY_H
#define REVERSI_PLAY_H


#include <vector>
#include "Command.h"

class Play : public Command {
public:
    int execute(vector<void*> args);
};


#endif //REVERSI_PLAY_H

