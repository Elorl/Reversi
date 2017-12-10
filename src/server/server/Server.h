//Avner Merhavi 203090436

// 05/12/17.
//

#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H
#define MAX_CONNECTED_CLIENTS 10
#define CLIENTS_NUM 2
#define MAX_INDICES 10

/**
 *  Server.
 *
 * @param port     the port number.
 */
class Server {
public:
    Server(int port);
    void start();
    void stop();
private:
    int port;
    int serverSocket; // the socket's file descriptor
    int clientSockets[2];
    int handleClients(int senderSocket, int receiverSocket);
};


#endif //SERVER_SERVER_H
