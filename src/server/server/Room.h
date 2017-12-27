//Avner Merhavi 203090436

// 26/12/17.
//

#ifndef REVERSI_ROOM_H
#define REVERSI_ROOM_H

#include "vector"
using namespace std;
class Room {
private:
    vector<int> sockets;
public:
    Room(int firstSocket);
    bool isAvailable();
    void addSocket(int secondSocket);
    int writeToSocket(int num, int socket);
    vector<int> getSockets();
};


#endif //REVERSI_ROOM_H
