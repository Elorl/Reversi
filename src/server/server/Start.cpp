//Avner Merhavi 203090436

// 26/12/17.
//

#include <map>
#include "Start.h"
#include "Room.h"

/**
 *
 * @param args - 0: socket, 1: game name, 2: rooms map
 * @return
 */
int start::execute(vector<void*> args) {
    int socket  = *(int*)args[0];
    map<string, Room*>* rooms = ((map*)args[2]);
    string name = *(string*)args[1];

    //if a game with such a name already exists
    if(rooms->find(name) != rooms->end()){
        return -1;
    }

    //create a room and insert to the given map
    Room* room = new Room(socket);
    rooms->insert(pair<string, Room*>(name, room));
}