

#include "Server.h"
#include <sys/socket.h>
#include <pthread.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <sys/param.h>
#include <cstdlib>
#include <sstream>
#include "ClientHandler.h"

struct Connect {
    int *serverSock;
    int *clientSock;
    vector <int> *socketList;
    vector <pthread_t> *threadsList;
    CommandsManager *cManager;
    map <string, Room&> *roomList;
};

using namespace std;
#define MAX_CONNECTED_CLIENTS 10

/*****************************************************************************************************
* function name: Server     											                             *
* the input: -					                                                                     *
* the output:                                                                                        *
* the function operation: the function will create the server.                                       *
*****************************************************************************************************/
Server::Server(int port, CommandsManager cM): port(port) {
    serverSocket = new int;
    commandsManager = cM;
    commandsManager.setRooms(&rooms);
    cout << "Server" << endl;
}
void Server::start() {
    Connect *args = new Connect;
    args->serverSock = serverSocket;
    args->socketList = &sockets;
    args->threadsList = threads;
    args->cManager = &commandsManager;
    args->roomList = &rooms;

    // Create a socket point
    *serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (*serverSocket == -1) {
        throw "Error opening socket";
    }
    // Assign a local address to the socket
    struct sockaddr_in serverAddress;
    bzero((void *)&serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);
    if (bind(*serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
        throw "Error on binding";
    }
    // Start listening to incoming connections
    listen(*serverSocket, MAX_CONNECTED_CLIENTS);
    int i = pthread_create(&thread, NULL, handleConnectClient, args);
    if (i) {
        cout << "Error: unable to create thread, " << i << endl;
        exit(-1);
    }
    args->threadsList->push_back(thread);

    pthread_t exitThread;
    int j = pthread_create(&exitThread, NULL, stop, args);
    if (j) {
        cout << "Error: unable to create thread, " << j << endl;
        exit(-1);
    }
    pthread_exit(NULL);
}

/*****************************************************************************************************
* function name: stop											        	                         *
* the input: -					                                                                     *
* the output:                                                                                        *
* the function operation: the function will close all the sockets.                                   *
*****************************************************************************************************/
void* Server::stop(void *connectStruckt) {
    struct Connect *arg = (struct Connect *) connectStruckt;
    map<string, Room&>::const_iterator iter;
    char command[5];
    cin >> command;
    if(strcmp(command, "exit") == 0) {
        for(iter = arg->roomList->begin(); iter != arg->roomList->end(); iter++) {
            Room r = iter->second;
            r.closeRoom();
        }
        vector <pthread_t> threads = *arg->threadsList;
        for(int i=0; i < threads.size(); i++) {
            pthread_t thread = threads[i];
            pthread_cancel(thread);
        }
        vector <int> sockets = *arg->socketList;
        for(int j = 0; j < sockets.size(); j++) {
            int socket = sockets[j];
            close(socket);
        }
    }
}

void* Server::handleConnectClient(void* connectStruct) {
    struct Connect *arg = (struct Connect *) connectStruct;
    int *clientSocket = new int;
    pthread_t pthread;
    // Define the client socket's structures
    struct sockaddr_in *clientAddress;
    socklen_t *clientAddressLen;
    while(true) {
        cout << "Waiting for client connections..." << endl;
        // Accept first client connection
        *clientSocket = accept(*arg->serverSock, (struct sockaddr *)clientAddress, clientAddressLen);
        cout << "Client connected" << endl;
        if (*clientSocket == -1)
            throw "Error on accept";
        arg->socketList->push_back(*clientSocket);
        arg->clientSock = clientSocket;
        int i = pthread_create(&pthread, NULL, handleAccepts, arg);
        if (i) {
            cout << "Error: unable to create thread, " << i << endl;
            exit(-1);
            /////לסגור את שאר הסוקטים והתרדים או לא?
        }
        arg->threadsList->push_back(pthread);
    }
}

void* Server::handleAccepts(void* connectStruct) {
    struct Connect *arg = (struct Connect *) connectStruct;
    vector<string> args;
    int check;
    int socket = *arg->clientSock;
    stringstream s;
    s << socket;
    string sckt = s.str();
    args.push_back(sckt);
    char buffer[50];
    do {
        //read the command from the socket
        int status = read(socket, buffer, sizeof(buffer));
        if (status == -1) {
            cout << "Error reading current player move" << endl;
            pthread_exit(&status);
        }
        if (status == 0) {
            cout << "Current Player is disconnected" << endl;
            pthread_exit(&status);
        }
        char c = ' ';
        const char *space = &c;
        char *token;
        //split the string with the space char.
        token = strtok(buffer, space);
        string command(token);
        char n = '\n';
        char *newLine = &n;
        //לוודא שזה NULL ולא ההמשך של cmnd
        token = strtok(NULL, newLine);
        string temp(token);
        args.push_back(temp);
        check = arg->cManager->executeCommand(command, args);
    } while (check == -1);
    ClientHandler clientHandler(arg->cManager, arg->roomList);
    clientHandler.handle();
}