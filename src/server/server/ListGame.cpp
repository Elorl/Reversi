//Avner Merhavi 203090436

// 26/12/17.
//

#include "ListGame.h"
#include "map"
#include "Room.h"

using namespace std;
/**
 * writing list of games to client socket
 * @param args rooms map, empty game names list
 * @return 0
 */
int ListGame::execute(vector<void*> args) {
    //copy pointer of the list given by caller
    vector<string>* gamesList = (vector<string>*)objects[1];

    map<string, Room*> rooms = *((map*)objects[0]);

    //insert games to the given list
    for(map<string,Room*>::iterator it = rooms.begin(); it != rooms.end(); ++it) {

        //if game is available for joining, add to list
        if(it->second->isAvailable()) {
            gamesList->push_back(it->first);
        }
    }
}