//
// Created by Avner Merhavi
//

#include "CommandsManager.h"
#include "Start.h"
#include "Join.h"
#include "Play.h"
#include "Close.h"
#include "ListGame.h"

pthread_mutex_t lock;

CommandsManager::CommandsManager() {
    Command& start = *new Start();
    Command& join = *new Join();
    Command& play = *new Play();
    Command& close = *new Close();
    Command& listGame = *new ListGame();
    commandsMap.insert(pair<string, Command&>("start", start));
    commandsMap.insert(pair<string, Command&>("join", join));
    commandsMap.insert(pair<string, Command&>("play", play));
    commandsMap.insert(pair<string, Command&>("close", close));
    commandsMap.insert(pair<string, Command&>("list_games", listGame));

}
CommandsManager::~CommandsManager() {
/*
    for(map<string,Command&>::iterator it = commandsMap.begin(); it != commandsMap.end(); ++it) {
        Command* command = &it->second;
        delete command;
        commandsMap.erase(it);
    }*/

}
int CommandsManager::executeCommand(string command, vector<string> args) {
    Command& foundCommand = commandsMap.find(command)->second;

    //if command does not exist
    if(commandsMap.find(command) == commandsMap.end()) {
        return -1;
    }
    //put string args and map as pointers in void* vector, and send to command
    vector<void*> commandArgs;
    commandArgs.push_back((void*)&args);
    commandArgs.push_back((void*)rooms);
    int retVal = foundCommand.execute(commandArgs);
    return retVal;

}

void CommandsManager::setRooms(map<string, Room &> *roomsMap) {
    rooms = roomsMap;
}
