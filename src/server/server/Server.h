//Avner Merhavi 203090436

// 05/12/17.
//

#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H
#define MAX_CONNECTED_CLIENTS 10
#define CLIENTS_NUM 2
#define MAX_INDICES 10

#include <vector>
#include <pthread.h>
#include "CommandsManager.h"

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
    void stop();
    void *handleAccepts(void*);
    void handleConnectClient();
private:
    int port;
    int serverSocket; // the socket's file descriptor
    int clientSockets[2];
    int handleClients(int senderSocket, int receiverSocket);
    vector <int> sockets;
    vector <pthread_t> threads;
    pthread_t thread;
    CommandsManager commandsManager;
};


#endif //SERVER_SERVER_H
