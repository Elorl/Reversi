
// 28/12/17.
//

//
// Created by elor on 27/12/17.
//

#ifndef SERVER_COMMANDSMANAGER_H
#define SERVER_COMMANDSMANAGER_H

#include <map>
#include <string>
#include <vector>
#include "Command.h"
#include "Room.h"


using namespace std;

class CommandsManager {
public:
    CommandsManager();
    ~CommandsManager();
    int executeCommand(string command, vector<string> args);
    void setRooms(map<string, Room&>* rooms);



private:
    map<string, Command&> commandsMap;
    map<string, Room&>* rooms;
};


#endif //SERVER_COMMANDSMANAGER_H
