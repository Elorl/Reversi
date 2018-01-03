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
    string name;
public:
    Room(int firstSocket, string nameRoom);
    bool isFull();
    bool isRunning();
    void addSocket(int secondSocket);
    int writeCharToSocket(char c, int socket);
    int sendNumbersToClients();
    int writeNumToSocket(int num, int socket);
    vector<int> getSockets();
    int getFirstSocket();
    int getSecondSocket();
    void setThread(pthread_t& thread);
    void markRunning();
    void closeRoom();
    string getName();

};


#endif //REVERSI_ROOM_H
