//Avner Merhavi 203090436

// 26/12/17.
//

#include <string>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include "Room.h"

/**
 * constructor.
 * @param firstSocket
 */
Room::Room(int firstSocket, string nameRoom): running(false), thread(NULL){
    sockets.push_back(firstSocket);
    name = nameRoom;
}
/**
 * returns if the room is available. when only one socket was supplied
 * @return
 */
bool Room::isFull() {
    return sockets.size() == 2;
}

/**
 * check if a current activity is happening in room
 * @return bool
 */
bool Room::isRunning() {
    return running;
}
/**
 * adds second socket.
 * @param secondSocket
 */
void Room::addSocket(int secondSocket) {
    sockets.push_back(secondSocket);
}

/**
 * write string to socket
 * @param buffer
 * @param socket
 * @return success status flag
 */
int Room::writeStringToSocket(char *buffer, int socket) {
    int status = write(socket, &buffer, strlen(buffer));
    if(status == -1) {
        cout<<"error writing to client socket" <<endl;
        return -1;
    }
    if(status ==0) {
        cout<< "client is disconnected"<< endl;
        return 0;
    }
}
/**
 * writing a decimal to socket
 * @param num
 * @param socket
 * @return success status flag
 */
int Room::writeNumToSocket(int num, int socket) {
    int status = write(socket, &num, sizeof(num));
    if(status == -1) {
        cout<<"error writing to client socket" <<endl;
        return -1;
    }
    if(status ==0) {
        cout<< "client is disconnected"<< endl;
        return 0;
    }
}
/**
 * getter for sockets vector
 * @return
 */
vector<int> Room::getSockets() {
    return sockets;
}

/**
 * set bollean of running as true
 * @param running
 */
void Room::markRunning() {
    running = true;
}
/**
 * set thread related to room.
 * @param thread
 */
void Room::setThread(pthread_t& thread) {
    Room::thread = &thread;
}

void Room::closeRoom() {
    if(running) {
        pthread_cancel(*thread);
    }
    for(int i = 0; i < sockets.size(); i++){
        close(sockets[i]);
    }
}

string Room::getName() {
    return name;
}

int Room::sendNumbersToClients() {
    if(isFull()) {
        //write id numbers 1, 2 to clients
        int firstPlayerNum = 1;
        int secondPlayerNum = 2;
        int stat1 = writeNumToSocket(firstPlayerNum, sockets[0]);
        if(stat1 == -1 || stat1 == 0) {
            return stat1;
        }
        int stat2 = writeNumToSocket(secondPlayerNum, sockets[1]);

        if(stat2 == -1 || stat2 == 0) {
            return stat2;
        }
    }

}
int Room::getFirstSocket() {
    return sockets[0];
}
int Room::getSecondSocket() {
    return sockets[1];
}