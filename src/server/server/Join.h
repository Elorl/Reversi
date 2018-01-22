//Avner Merhavi 203090436

// 27/12/17.
//

#ifndef REVERSI_JOIN_H
#define REVERSI_JOIN_H

#include <vector>
#include "Command.h"

using namespace std;

class Join: public Command{
public:
    int execute(vector<void*> args);
};


#endif //REVERSI_JOIN_H

