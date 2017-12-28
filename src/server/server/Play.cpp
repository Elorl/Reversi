//Avner Merhavi 203090436

// 28/12/17.
//

#include <map>
#include "Play.h"
#include "Room.h"

int Play::execute(vector<void *> args) {

    string name = *(string*)args[0];
    map<string, Room>* rooms = (map*)args[1];
}