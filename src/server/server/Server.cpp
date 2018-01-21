
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
pthread_mutex_t lock;
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
* the function operation: constructor.                                                               *
*****************************************************************************************************/
Server::Server(int port, CommandsManager cM): port(port), threads(new vector <pthread_t>) {
    serverSocket = new int;
    commandsManager = cM;
    commandsManager.setRooms(&rooms);
    cout << "Server" << endl;
}

/*****************************************************************************************************
* function name: start     											                                 *
* the input: -					                                                                     *
* the output:                                                                                        *
* the function operation: start the server.                                                          *
*****************************************************************************************************/
void Server::start() {

    Connect *args = new Connect;
    args->serverSock = serverSocket;
    args->socketList = &sockets;
    args->threadsList = threads;
    args->cManager = &commandsManager;
    args->roomList = &rooms;
    thread = new pthread_t;
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
    //create a thread that run the accept loop.
    int i = pthread_create(thread, NULL, handleConnectClient, args);
    if (i) {
        cout << "Error: unable to create thread, " << i << endl;
        exit(-1);
    }
    //add this thread to the threads list.
    args->threadsList->push_back(*thread);
    pthread_t exitThread;
    //create a threat that listening to the server's command line, to catch 'exit' command.
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
    //check if the server got an 'exit' command.
    if(strcmp(command, "exit") == 0) {
        vector <pthread_t> threads = *arg->threadsList;
        //close all the threads.
        for(int i=0; i < threads.size(); i++) {
            pthread_t thread = threads[i];
            pthread_cancel(thread);
        }
        //close all the rooms.
        for(iter = arg->roomList->begin(); iter != arg->roomList->end(); iter++) {
            Room r = iter->second;
            r.closeRoom();
        }
        //close all the sockets.
        vector <int> sockets = *arg->socketList;
        for(int j = 0; j < sockets.size(); j++) {
            int socket = sockets[j];
            close(socket);
        }
    }
}
/*****************************************************************************************************
* function name: handleConnectClient											        	         *
* the input: a connect struct.					                                                     *
* the output:                                                                                        *
* the function operation: the function will loop and accept connections to the server.               *
*****************************************************************************************************/
void* Server::handleConnectClient(void* connectStruct) {
    struct Connect *arg = (struct Connect *) connectStruct;
    int *clientSocket = new int;
    pthread_t pthread;
    // Define the client socket's structures
    struct sockaddr_in *clientAddress;
    socklen_t *clientAddressLen;
    while(true) {
        cout << "Waiting for client connections..." << endl;
        // Accept a client connection
        *clientSocket = accept(*arg->serverSock, (struct sockaddr *)clientAddress, clientAddressLen);
        //check if the connection have been failed.
        if (*clientSocket == -1)
            throw "Error on accept";
        cout << "Client connected" << endl;
        //add the new socket to the sockets list.
        arg->socketList->push_back(*clientSocket);
        arg->clientSock = clientSocket;
        //create a thread that handle with this connection.
        int i = pthread_create(&pthread, NULL, handleAccepts, arg);
        if (i) {
            cout << "Error: unable to create thread, " << i << endl;
            exit(-1);
        }
        //add the new socket to the threads list.
        int x = arg->threadsList->size();
        arg->threadsList->push_back(pthread);
        int x1 = arg->threadsList->size();
        int y = arg->threadsList->size();
    }
}
/*****************************************************************************************************
* function name: handleAccepts      											        	         *
* the input: a connect struct.					                                                     *
* the output:                                                                                        *
* the function operation: the function will handle each accept.                                      *
*****************************************************************************************************/
void* Server::handleAccepts(void* connectStruct) {
    struct Connect *arg = (struct Connect *) connectStruct;
    vector<string> args;
    int check;
    int socket = *arg->clientSock;
    //convert the socket number to string.
    stringstream s;
    s << socket;
    string sckt = s.str();
    args.push_back(sckt);
    char buffer[50];
    //read the command from the socket
    int status = read(socket, buffer, sizeof(buffer));
    //check if the read action have been failed.
    if (status == -1) {
        cout << "Error reading current player move" << endl;
        pthread_exit(&status);
    }
    //check if the read action have been failed.
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
    //split the string with the '\n' char.
    token = strtok(NULL, newLine);
    if(token != NULL) {
        string temp(token);
        args.push_back(temp);
    }
    //execute the command from the socket
    try {
        check = arg->cManager->executeCommand(command, args);
    } catch (char const *s) {
        cout << s << endl;
        close(socket);
        pthread_exit(&status);
    }
    //check if the command is not valid
    if(check < 0) {
        status = write(socket, &check, sizeof(check));
        if (status == -1) {
            cout << "Error reading current player command" << endl;
            close(socket);
            pthread_exit(&status);
        }
        //check if the read action have been failed.
        if (status == 0) {
            cout << "Current Player is disconnected" << endl;
            close(socket);
            pthread_exit(&status);
        }
    } else {
        ClientHandler clientHandler(arg->cManager, arg->roomList);
        clientHandler.handle();
    }
}