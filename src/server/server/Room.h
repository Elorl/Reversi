//Avner Merhavi 203090436

// 26/12/17.
//

#ifndef REVERSI_ROOM_H
#define REVERSI_ROOM_H

#include "vector"
#include "pthread.h"

using namespace std;
class Room {
private:
    vector<int> sockets;
    bool running;
    pthread_t* thread;

public:
    Room(int firstSocket);
    bool isFull();
    bool isRunning();
    void addSocket(int secondSocket);
    int writeToSocket(int num, int socket);
    vector<int> getSockets();
    void setThread(pthread_t& thread);
    void markRunning();
    void closeRoom();
};


#endif //REVERSI_ROOM_H
