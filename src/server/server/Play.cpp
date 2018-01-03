//Avner Merhavi 203090436

// 28/12/17.
//

#include <map>
#include <cstdlib>
#include <unistd.h>
#include "Play.h"
#include "Room.h"
/**
 *
 *  @param args 0: string vector [ socket, room name, x, y]
 *             1: rooms map
 * @return
 */
int Play::execute(vector<void *> args) {
    vector<string> stringArgs = *(vector<string>*)args[0];
    map<string, Room&>* rooms = (map<string, Room&>*)args[1];

    int destSocket = atoi(stringArgs[0].c_str());
    string name = stringArgs[1];

    int x = atoi(stringArgs[2].c_str());
    int y = atoi(stringArgs[3].c_str());

    //found room - if not found , it will contain the end of the map
    Room& foundRoom = rooms->find(name)->second;
    //if a game with such does not exist, or room is not running yet
    if(rooms->find(name) == rooms->end() || !foundRoom.isRunning()){
        return -1;
    }

    //write move to socket

    int status = write(destSocket, &x, sizeof(x));
    if(status == -1) {
        cout<<"error writing to client socket" <<endl;
        return -1;
    }
    if(status ==0) {
        cout<< "client is disconnected"<< endl;
        return 0;
    }

    char comma = ',';

    status = write(destSocket, &comma, sizeof(comma));
    if(status == -1) {
        cout<<"error writing to client socket" <<endl;
        return -1;
    }
    if(status ==0) {
        cout<< "client is disconnected"<< endl;
        return 0;
    }

    status = write(destSocket, &y, sizeof(y));
    if(status == -1) {
        cout<<"error writing to client socket" <<endl;
        return -1;
    }
    if(status ==0) {
        cout<< "client is disconnected"<< endl;
        return 0;
    }

    return 1;

}