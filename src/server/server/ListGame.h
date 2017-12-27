//Avner Merhavi 203090436

// 26/12/17.
//

#ifndef REVERSI_LISTGAME_H
#define REVERSI_LISTGAME_H


#include <vector>
#include "Command.h"

class ListGame: public Command{
public:
    int execute(vector<void*> args);
};


#endif //REVERSI_LISTGAME_H
