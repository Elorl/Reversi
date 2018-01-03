//Avner Merhavi 203090436

// 26/12/17.
//

#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include "ListGame.h"
#include "map"
#include "Room.h"

using namespace std;
/**
 * writing list of games to client socket
 * @param args 0: vector with one string represent socket number
 *             1: rooms map
 * @return 0
 */
int ListGame::execute(vector<void*> args) {

    vector<string> stringArgs = *(vector<string>*)args[0];
    int socket = atoi(stringArgs[0].c_str());
    map<string, Room&>* rooms = ((map<string, Room&>*)args[1]);

    vector<string> availableGames;
    //insert available games to a vector

    for(map<string,Room&>::iterator it = rooms->begin(); it != rooms->end(); ++it) {
        Room& room = it->second;
        //if game is not full, write it's name to client socket
        if(!room.isFull()) {
            availableGames.push_back(it->first);
        }
    }


    //write number of names to socket (for the reading loop in client)
    int numberOfAvailableGames = availableGames.size();
    int stat = write(socket,&numberOfAvailableGames, sizeof(numberOfAvailableGames));
    if(stat == -1) {
        cout<< "Error writing game list size to socket"<<endl;
        return stat;
    }
    if(stat == 0){
        cout << "Client is disconnected"<<endl;
        return stat;
    }

    //write game names
    for(int i = 0; i < numberOfAvailableGames; i++) {
        const char* gameName = availableGames[i].c_str();
        int confirm;
        stat = write(socket, gameName, strlen(gameName) + 1);
        if(stat == -1) {
            cout<< "Error writing game list size to socket"<<endl;
            return stat;
        }
        if(stat == 0){
            cout << "Client is disconnected"<<endl;
            return stat;
        }

        stat = read(socket, &confirm, sizeof(confirm));

        if(stat == -1) {
            cout<< "Error writing game socket"<<endl;
            return stat;
        }
        if(stat == 0){
            cout << "Client is disconnected"<<endl;
            return stat;
        }
    }

    return 1;
}
