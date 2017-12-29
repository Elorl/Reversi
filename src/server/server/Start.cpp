//Avner Merhavi 203090436

// 26/12/17.
//

#include <map>
#include <cstdlib>
#include "Start.h"
#include "Room.h"

/**
 * opens a room with given name. adds first client socket to room.Zz
 * adds socket to an existing room.
 * @param args 0: string vector [ socket, game name]
 *             1: rooms map
 * @return success flag
 */
int start::execute(vector<void*> args) {
    vector<string> stringArgs = *(vector<string>*)args[0];
    int socket = atoi(stringArgs[0].c_str());
    string name = stringArgs[1];
    map<string, Room&>* rooms = ((map*)args[1]);

    //if a game with such a name already exists
    if(rooms->find(name) != rooms->end()){
        return -1;
    }

    //create a room and insert to the given map
    Room* room = new Room(socket);
    rooms->insert(pair<string, Room&>(name, *room));
}