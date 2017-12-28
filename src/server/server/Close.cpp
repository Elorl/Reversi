//Avner Merhavi 203090436

// 27/12/17.
//

#include <map>
#include "Close.h"
#include "Room.h"

/**
 * close the thread, remove room from map
 * @param args - 0: room name, 1 - rooms map
 * @return
 */
int Close::execute(vector<void *> args) {
    string name = *(string*)args[0];
    map<string, Room*>* rooms = ((map*)args[1]);

    //found room - if not found , it will contain the end of the map
    Room* foundRoom = rooms->find(name)->second;

    //if a game with such does not exist
    if(rooms->find(name) == rooms->end()){
        return -1;
    }

    //close room, remove from map
    foundRoom->closeRoom();
    rooms->erase(name);
}