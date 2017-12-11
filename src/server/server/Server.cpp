
#include "Server.h"
#include <sys/socket.h>

#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <sys/param.h>

using namespace std;
#define MAX_CONNECTED_CLIENTS 10

/*****************************************************************************************************
* function name: Server     											                             *
* the input: -					                                                                     *
* the output:                                                                                        *
* the function operation: the function will create the server.                                       *
*****************************************************************************************************/
Server::Server(int port): port(port), serverSocket(0) {
    cout << "Server" << endl;
}
void Server::start() {
// Create a socket point
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        throw "Error opening socket";
    }
    // Assign a local address to the socket
    struct sockaddr_in serverAddress;
    bzero((void *)&serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);
    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
        throw "Error on binding";
    }
    // Start listening to incoming connections
    listen(serverSocket, MAX_CONNECTED_CLIENTS);

    // Define the client socket's structures
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLen;
    while (true) {
        cout << "Waiting for client connections..." << endl;
    // Accept first client connection
        int firstClientSocket = accept(serverSocket, (struct
                sockaddr *)&clientAddress, &clientAddressLen);
        cout << "Client connected" << endl;
        if (firstClientSocket == -1)
            throw "Error on accept";

        //add to client sockets array
        clientSockets[0] = firstClientSocket;

        // Accept second client connection
        cout << "Waiting for client connections..." << endl;
        // Accept first client connection
        int secondClientSocket = accept(serverSocket, (struct
                sockaddr *)&clientAddress, &clientAddressLen);
        cout << "Client connected" << endl;
        if (secondClientSocket == -1)
            throw "Error on accept";
        //add to client sockets array
        clientSockets[1] = secondClientSocket;

        //send clients their numbers
        int status;
        int firstPlayerNum = 1;
        int secondPlayerNum = 2;
        status = write(firstClientSocket, &firstPlayerNum, sizeof(firstPlayerNum));
        status = write(secondClientSocket, &secondPlayerNum, sizeof(secondPlayerNum));
        // to add: if status is 0 / -1

        int i = 0;
        while(true) {
            status = handleClients(clientSockets[i%2], clientSockets[(i + 1)% 2]);
            if(status == 0 || status == -1 || status == -2) {
                break;
            } else {
                i++;
            }
        }
    // Close communication with the client
        close(firstClientSocket);
        close(secondClientSocket);
    }
}

/*****************************************************************************************************
* function name: handleClients											                             *
* the input: -					                                                                     *
* the output:                                                                                        *
* the function operation: the function will Handle requests from a specific client                   *
*****************************************************************************************************/
int Server::handleClients(int senderSocket, int receiverSocket) {
    char index[10];
    int x, y;
    char comma;
    int status1 = read(senderSocket, &x, sizeof(x));
    int status2 = read(senderSocket, &comma, sizeof(comma));
    int status3 = read(senderSocket, &y, sizeof(y));
    if (status1 == -1 || status2 == -1 || status3 == -1) {
        cout << "Error reading current player move" << endl;
        return -1;
    }
    if(status1 == 0 || status2 == 0 || status3 == 0) {
        cout << "Current Player is disconnected" << endl;
        return 0;
    }
    //check if the game was ended.
    if(x == -2 || y == -2 ) {
        return -2;
    }
    //check if there is no possible move for a player.
    if(x == -3 || y == -3) {
        return -3;
    }
    //print the input
    cout << "input: " << '(' << x << ',' << y << ')' << endl;
    status1 = write(receiverSocket, &x, sizeof(x));
    status2 = write(receiverSocket, &comma, sizeof(comma));
    status3 = write(receiverSocket, &y, sizeof(y));
    if (status1 == -1 || status2 == -1 || status3 == -1) {
        cout << "Error writing player move to it's rival" << endl;
        return -1;
    }
    if(status1 == 0 || status2 == 0 || status3 == 0) {
        cout << "rival is disconnected" << endl;
        return 0;
    }
    //print the output
    cout << "Output: " << '(' << x << ',' << y << ')' << endl;
    return 1;
}

/*****************************************************************************************************
* function name: stop											        	                         *
* the input: -					                                                                     *
* the output:                                                                                        *
* the function operation: the function will close all the sockets.                                   *
*****************************************************************************************************/
void Server::stop() {
    close(serverSocket);
}