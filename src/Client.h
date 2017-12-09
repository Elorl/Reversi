
#ifndef REVERSI_CLIENT_H
#define REVERSI_CLIENT_H

#include <iostream>
#include <utility>

using namespace std;

/**
 *  Client.
 *
 *  @param serverIP      ip address.
 *  @param serverPort    port number.
 */
class Client {
public:
    Client(const char *serverIP, int serverPort);
    int connectToServer();
    void sendPoint(int arg1, char op, int arg2);
    pair<int, int> readPoint();
private:
    const char *serverIP;
    int serverPort;
    int clientSocket;
};


#endif //REVERSI_CLIENT_H
