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

ClientHandler::ClientHandler(CommandsManager *cm, map <string, Room&> *map) {
    rooms = map;
    cManager = cm;
}

void ClientHandler::handle() {
    map<string, Room&>::const_iterator iter;
    RoomPlayer roomPlayer;
    roomPlayer.commandsManager = cManager;
    for(iter = rooms->begin(); iter != rooms->end(); iter++) {
        Room r = iter->second;
        bool running = r.isRunning();
        if(!running) {
            r.markRunning();
            pthread_t thread;
            roomPlayer.room = &r;
            int i = pthread_create(&thread, NULL, run, &roomPlayer);
            if (i) {
                cout << "Error: unable to create thread, " << i << endl;
                r.closeRoom();
            } else {
                r.markRunning();
                r.setThread(thread);
            }
        }
    }
}

void* ClientHandler::run(void *r) {
    struct RoomPlayer *roomPlayer = (struct RoomPlayer *) r;
    Room *room = roomPlayer->room;
    int clientSockets[2];
    clientSockets[0] = room->getSockets()[0];
    clientSockets[1] = room->getSockets()[1];
    int status, i = 0;
    while(true) {
        status = handleClients(clientSockets[i%2], clientSockets[(i + 1)% 2], room, roomPlayer->commandsManager);
        if(status == 0 || status == -1 || status == -2) {
            // Close communication with the client
            room->closeRoom();
            pthread_exit(&status);
        } else {
            i++;
        }
    }
}

int ClientHandler::handleClients(int senderSocket, int receiverSocket, Room *r, CommandsManager *cm) {
    vector<string> args;
    CommandsManager *commandsManager = cm;
    char *input, *token, temp = ',';
    const char *comma = &temp;
    char c = ' ', n ='\n';
    const char *space = &c;
    const char *newLine = &n;
    //יכול להיות שצריך לקרוא מהסוקט עד שמקבלים \n..צריך לבדוק את זה
    int status = read(senderSocket, input, sizeof(input));
    if (status == -1) {
        cout << "Error reading current player move" << endl;
        return -1;
    }
    if(status == 0) {
        cout << "Current Player is disconnected" << endl;
        return 0;
    }
    stringstream s;
    s << receiverSocket;
    string receiver = s.str();
    args.push_back(receiver);
    args.push_back(r->getName());
    //split the string with the space char.
    token = strtok(input, space);
    string command(token);
    //לוודא שזה NULL ולא ההמשך של cmnd
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
    commandsManager->executeCommand(command, args);
}




