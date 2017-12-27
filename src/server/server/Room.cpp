//Avner Merhavi 203090436

// 26/12/17.
//

#include <string>
#include <unistd.h>
#include <iostream>
#include "Room.h"

/**
 * constructor.
 * @param firstSocket
 */
Room::Room(int firstSocket): running(false), thread(NULL){
    sockets.push_back(firstSocket);
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
 * writing to socket
 * @param socket
 */
int Room::writeToSocket(char* buffer, int socket) {
    int status = write(socket, &buffer, sizeof(num));
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

void Room::setThread(pthread_t& thread) {
    Room::thread = &thread;
}

void Room::closeRoom() {
    if(running) {
        close(*thread);
    }
    for(int i = 0; i < sockets.size(); i++){
        close(sockets[i]);
    }
}