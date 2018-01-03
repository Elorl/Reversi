
#ifndef REVERSI_CLIENT_H
#define REVERSI_CLIENT_H

#include <iostream>
#include <utility>
#include <vector>
#include "UserInterface.h"
#include "ConsoleUI.h"

using namespace std;

/**
 *  Client.
 *
 *  @param serverIP      ip address.
 *  @param serverPort    port number.
 */
class Client {
public:
    Client(const char *serverIP, int serverPort, UserInterface& ui);
    int connectToServer();
    void sendString(string str);
    int readNumber();
    void sendPoint(int arg1, char op, int arg2);
    pair<int, int> readPoint();
    vector<string> getGamesList();
    int chooseRemoteGameOption();
    int start();
    bool printGamesList();
    int join();
private:
    const char *serverIP;
    int serverPort;
    int clientSocket;
    UserInterface& ui;
};


#endif //REVERSI_CLIENT_H
