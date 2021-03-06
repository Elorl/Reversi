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
    map <string, Room&> *mapRooms;
};

/*****************************************************************************************************
* function name: ClientHandler          			            		        	                 *
* the input: cm = the command manager object, map of the rooms.                                      *
* the output: -                                                                                      *
* the function operation: constructor                                                                *
*****************************************************************************************************/
ClientHandler::ClientHandler(CommandsManager *cm, map <string, Room&> *map, ThreadPool *tp) {
    rooms = map;
    cManager = cm;
    threadPool = tp;
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
    roomPlayer->mapRooms = rooms;

    pthread_mutex_lock(&lock);

    //runs all over the room map.
    for(iter = rooms->begin(); iter != rooms->end(); iter++) {
        Room *r = &iter->second;
        bool running = r->isRunning();
        bool full = r->isFull();
        //check if there is an open thread to the room and if the room has 2 sockets.
        if((!running) && (full)) {
            roomPlayer->room = r;

            threadPool->addTask(new Task(run, roomPlayer));

            //update the game was start.
            r->markRunning();
        }
    }

    pthread_mutex_unlock(&lock);
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
            roomPlayer->mapRooms->erase(room->getName());
            room->closeRoom();
            break;
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
    char input[50], *token1, *token2, *token3, temp = ',';
    const char *comma = &temp;
    char c = ' ', n ='\n', z = '\0';
    const char *space = &c;
    const char *endS = &z;
    //read the command from the user
    int status = read(senderSocket, input, sizeof(input));
    //check if the read was failed.
    if (status == -1) {
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
    token1 = strtok(input, space);
    string command(token1);
    //split the point to two ints.
    token2 = strtok(NULL, comma);
    int xNum = 0, yNum = 0;
    if(token2 != NULL) {
        string x(token2);
        sscanf(x.c_str(), "%d", &xNum);
        args.push_back(x);
    }
    token3 = strtok(NULL, endS);
    if(token3 != NULL) {
        string y(token3);
        sscanf(y.c_str(), "%d", &yNum);
        args.push_back(y);
    }
    //check if there is no possible move for a player.
    if(xNum == -3 || yNum == -3) {
        return -3;
    }
    //execute the command.
    try {
        commandsManager->executeCommand(command, args);
    } catch (char const *x) {
        cout<<"error writing to client socket" <<endl;
    }
}
