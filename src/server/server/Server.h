

#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H
#define MAX_CONNECTED_CLIENTS 10
#define CLIENTS_NUM 2
#define MAX_INDICES 10

#include <vector>
#include <pthread.h>
#include "CommandsManager.h"
#include <map>
#include "Room.h"
#include "ThreadPool.h"

using namespace std;
/**
 *  Server.
 *
 * @param port     the port number.
 */
class Server {
public:
    Server(int port, CommandsManager commandsManager);
    void start();
    static void *stop(void* connectStruckt);
    static void *handleAccepts(void* connectStruckt);
    static void *handleConnectClient(void* connectStruckt);
    map <string, Room&> rooms;
private:
    int port;
    int *serverSocket; // the socket's file descriptor
    int clientSockets[2];
    vector <int> sockets;
    //vector <pthread_t> *threads;
    pthread_t *thread;
    ThreadPool threadPool;
    CommandsManager commandsManager;
};


#endif //SERVER_SERVER_H
