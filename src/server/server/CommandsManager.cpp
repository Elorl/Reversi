//
// Created by Avner Merhavi
//

#include "CommandsManager.h"
#include "Play.h"
#include "Join.h"
#include "Start.h"
#include "ListGame.h"

CommandsManager::CommandsManager() {
    Play commandPlay;
    Join commandJoin;
    ListGame commandList;
    Start commandStart;


}

int CommandsManager::executeCommand(string command, vector<string> args) {
    Command foundCommand = commandsMap.find(command)->second;

    //if command does not exist
    if(commandsMap.find(command) == commandsMap.end()) {
        return -1;
    }
    //put string args and map as pointers in void* vector, and send to command
    vector<void*> commandArgs;
    commandArgs.push_back((void*)&args);
    commandArgs.push_back((void*)rooms);
    foundCommand.execute(commandArgs);

}

void CommandsManager::setRooms(map<string, Room &> *roomsMap) {
    rooms = roomsMap;
}