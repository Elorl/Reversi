//
// Created by elor on 28/12/17.
//

#ifndef SERVER_CLIENTHANDLER_H
#define SERVER_CLIENTHANDLER_H


#include "CommandsManager.h"
#include "Room.h"
#include "ThreadPool.h"

class ClientHandler {
public:
    ClientHandler(CommandsManager *cm, map <string, Room&> *mp, ThreadPool *threadPool);
    void handle();
    static int handleClients(int senderSocket, int receiverSocket, Room *r, CommandsManager *cm);
private:
    map <string, Room&> *rooms;
    CommandsManager *cManager;
    static void* run(void *r);
    Room *room;
    ThreadPool *threadPool;
};


#endif //SERVER_CLIENTHANDLER_H