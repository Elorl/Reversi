//Avner Merhavi 203090436

// 28/12/17.
//

#include <map>
#include "Play.h"
#include "Room.h"

int Play::execute(vector<void *> args) {

    int destSocket = *(int*)args[0];
    string name = *(string*)args[1];

    int x = *(int*)args[2];
    int y = *(int*)args[3];
    map<string, Room&>* rooms = (map*)args[4];

    //found room - if not found , it will contain the end of the map
    Room& foundRoom = rooms->find(name)->second;
    //if a game with such does not exist, or room is not running yet
    if(rooms->find(name) == rooms->end() || !foundRoom.isRunning()){
        return -1;
    }

    //write move to socket
    foundRoom.writeNumToSocket(x, destSocket);
    foundRoom.writeNumToSocket((int)",", destSocket);
    foundRoom.writeNumToSocket(y, destSocket);
}