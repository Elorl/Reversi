//
// Created by elor on 27/12/17.
//

#ifndef SERVER_COMMANDSMANAGER_H
#define SERVER_COMMANDSMANAGER_H

#include <map>
#include <string>
#include <vector>
#include "Command.h"

using namespace std;

class CommandsManager {
public:
    CommandsManager();
    ~CommandsManager();
    bool executeCommand(string command, vector<string> args);
private:
    map<string, Command *> commandsMap;
};


#endif //SERVER_COMMANDSMANAGER_H
