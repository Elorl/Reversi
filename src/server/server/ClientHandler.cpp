//
// Created by elor on 28/12/17.
//

#include <cstdlib>
#include "ClientHandler.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <sstream>
#include <cstdio>

struct RoomPlayer {
    Room *room;
    CommandsManager *commandsManager;
};

/*****************************************************************************************************
* function name: ClientHandler          			            		        	                 *
* the input: cm = the command manager object, map of the rooms.                                      *
* the output: -                                                                                      *
* the function operation: constructor                                                                *
*****************************************************************************************************/
ClientHandler::ClientHandler(CommandsManager *cm, map <string, Room&> *map) {
    rooms = map;
    cManager = cm;
}
/*****************************************************************************************************
* function name: handle          			                       		        	                 *
* the input: -                                                                                       *
* the output: -                                                                                      *
* the function operation: check if there is a new room to run.                                       *
*****************************************************************************************************/
void ClientHandler::handle() {
    map<string, Room&>::const_iterator iter;
    RoomPlayer *roomPlayer = new RoomPlayer;
    roomPlayer->commandsManager = cManager;
    //runs all over the room map.
    for(iter = rooms->begin(); iter != rooms->end(); iter++) {
        Room *r = &iter->second;
        bool running = r->isRunning();
        bool full = r->isFull();
        //check if there is an open thread to the room and if the room has 2 sockets.
        if((!running) && (full)) {
            pthread_t thread;
            roomPlayer->room = r;
            //create the thread to start the game, actually.
            int i = pthread_create(&thread, NULL, run, roomPlayer);
            if (i) {
                cout << "Error: unable to create thread, " << i << endl;
                r->closeRoom();
            } else {
                //update the game was start.
                r->markRunning();
                r->setThread(thread);
            }
        }
    }
}
/*****************************************************************************************************
* function name: run          			                       		        	                     *
* the input: struct with the room and the command manager.                                           *
* the output: -                                                                                      *
* the function operation: start the run of the game, switch between the players.                     *
*****************************************************************************************************/
void* ClientHandler::run(void *r) {
    struct RoomPlayer *roomPlayer = (struct RoomPlayer *) r;
    Room *room = roomPlayer->room;
    room->sendNumbersToClients();
    int clientSockets[2];
    clientSockets[0] = room->getFirstSocket();
    clientSockets[1] = room->getSecondSocket();
    int status, i = 0;
    //loop that run the game.
    while(true) {
        status = handleClients(clientSockets[i%2], clientSockets[(i + 1)% 2], room, roomPlayer->commandsManager);
        //check if the game was ended(-2), or there was error(0 or -1)
        if(status == 0 || status == -1 || status == -2) {
            // Close communication with the client
            room->closeRoom();
            pthread_exit(&status);
        } else {
            i++;
        }
    }
}
/*****************************************************************************************************
* function name: handleClients          			          		        	                     *
* the input: the recive and send socket, the room and the command manager.                           *
* the output: -                                                                                      *
* the function operation: get from the sender user is play command and send it to the receiver.      *
*****************************************************************************************************/
int ClientHandler::handleClients(int senderSocket, int receiverSocket, Room *r, CommandsManager *cm) {
    vector<string> args;
    CommandsManager *commandsManager = cm;
    char input[50], *token, temp = ',';
    const char *comma = &temp;
    char c = ' ', n ='\n';
    const char *space = &c;
    const char *newLine = &n;
    //read the command from the user
    int status = read(senderSocket, input, sizeof(input));
    //check if the read was failed.
    if (status == -1) {
        cout << "Error reading current player move" << endl;
        return -1;
    }
    //check if the read was failed.
    if(status == 0) {
        cout << "Current Player is disconnected" << endl;
        return 0;
    }
    //convert the socket number to string.
    stringstream s;
    s << receiverSocket;
    string receiver = s.str();
    args.push_back(receiver);
    args.push_back(r->getName());
    //split the string with the space char.
    token = strtok(input, space);
    string command(token);
    //split the point to two ints.
    token = strtok(NULL, comma);
    string x(token);
    token = strtok(NULL, newLine);
    string y(token);
    int xNum, yNum;
    sscanf(x.c_str(), "%d", &xNum);
    sscanf(y.c_str(), "%d", &yNum);
    //check if the game was ended.
    if(xNum == -2 || yNum == -2 ) {
        return -2;
    }
    //check if there is no possible move for a player.
    if(xNum == -3 || yNum == -3) {
        return -3;
    }
    args.push_back(x);
    args.push_back(y);
    //execute the command.
    commandsManager->executeCommand(command, args);
}




