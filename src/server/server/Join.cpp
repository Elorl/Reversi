//Avner Merhavi 203090436

// 27/12/17.
//

#include "Join.h"
#include <map>
#include "Room.h"

/**
 * adds socket to an existing room.
 * @param args 0: socket, 1: game name, 2: rooms map
 * @return
 */
int Join::execute(vector<void *> args) {
    int socket  = *(int*)args[0];
    string name = *(string*)args[1];
    map<string, Room*>* rooms = ((map*)args[2]);

    //found room - if not found , it will contain the end of the map
    Room* foundRoom = rooms->find(name)->second;
    //if a game with such does not exist, or game is already full
    if(rooms->find(name) == rooms->end() || foundRoom->isFull()){
        return -1;
    }

    // add socket to room - join
    foundRoom->addSocket(socket);
    //write id numbers 1, 2 to clients
    int firstPlayerNum = 1;
    int secondPlayerNum = 2;
    int stat1 = foundRoom->writeNumToSocket(firstPlayerNum, foundRoom->getSockets()[0]);
    if(stat1 == -1 || stat1 == 0) {
        return stat1;
    }
    int stat2 = foundRoom->writeNumToSocket(secondPlayerNum, socket);

    if(stat2 == -1 || stat2 == 0) {
        return stat2;
    }
    //if all correct
    return 1;
}