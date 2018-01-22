#include "Server.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>

using namespace std;

int readFIle();

int main() {
    int port = readFIle();
    CommandsManager commandsManager;
    Server server(port, commandsManager);
    try {
        server.start();
    } catch (const char *msg) {
        cout << "Cannot start server. Reason: " << msg << endl;
        exit(-1);
    }
}

int readFIle() {
    ifstream settings;
    string port;
    //open the settings file.
    settings.open("server_settings.txt");
    //check if the open action was succeed.
    if(settings == NULL) {
        throw "Error on open settings file";
    } else {
        getline(settings,port);
    }
    //convert the port from string to int.
    int prt = atoi(port.c_str());
    return prt;
}

