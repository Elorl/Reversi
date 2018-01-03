
#include "Client.h"
#include "UserInterface.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <sstream>
#include <cstdlib>

#define ILLEGAL_CHOICE -5

using namespace std;

/*****************************************************************************************************
* function name: Client - constructor			            		        	                     *
* the input: serverIP = ip address, serverPort = port number.       			                     *
* the output: -                                                                                      *
* the function operation: -                                                                          *
*****************************************************************************************************/
Client::Client(const char *serverIP, int serverPort, UserInterface& ui):
        serverIP(serverIP), serverPort(serverPort), clientSocket(0), ui(ui) {

}

/*****************************************************************************************************
* function name: connectToServer
* the input: -
* the output: 1 = this computer is the first player, 2 = this computer is the second player.
* the function operation: the function will connect to the server.
*****************************************************************************************************/
int Client::connectToServer() {
    // Create a socket point
    int playerNumber;
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        throw "Error opening socket";
    }
    // Convert the ip string to a network address
    struct in_addr address;
    if (!inet_aton(serverIP, &address)) {
        throw "Can't parse IP address";
    }
    // Get a hostent structure for the given host address
    struct hostent *server;
    server = gethostbyaddr((const void *)&address, sizeof
            address, AF_INET);
    if (server == NULL) {
        throw "Host is unreachable";
    }
    // Create a structure for the server address
    struct sockaddr_in serverAddress;
    bzero((char *)&address, sizeof(address));

    serverAddress.sin_family = AF_INET;
    memcpy((char *)&serverAddress.sin_addr.s_addr, (char *) server-> h_addr, server->h_length);
    // htons converts values between host and network byte orders

    serverAddress.sin_port = htons(serverPort);
    // Establish a connection with the TCP server
    if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
        throw "Error connecting to server";
    }
}

/*****************************************************************************************************
* function name: sendString
* the input: string
* the output: -
* the function operation: write string to socket
*****************************************************************************************************/
void Client::sendString(string str) {
    char buffer[50];
    strcpy(buffer, str.c_str());
    int n = write(clientSocket, buffer, sizeof(buffer));
    if (n == -1) {
        throw "Error writing to socket";
    }
}

/*****************************************************************************************************
* function name: readNumber
* the input: -
* the output: -
* the function operation: reads an int from socket
*****************************************************************************************************/
int Client::readNumber() {
    int number;
    int n = read(clientSocket, &number, sizeof(number));
    if(n == -1) {
        throw "Error reading number from socket";
    }
    if (n == 0) {
        throw "server closed!";
    }
    return number;
}
/*****************************************************************************************************
* function name: sendPoint          			            		        	                     *
* the input: arg1 = the x cord of the cell, arg2= the y cord of the cell.                            *
* the output: -                                                                                      *
* the function operation: the function will send the arguments to the server by the client object.   *
*****************************************************************************************************/
void Client::sendPoint(int arg1, char comma, int arg2) {

//chain all args to string: "play x,y" , then convert to char array
    string command = "play ";
    stringstream s1, s2;
    s1 << arg1;
    string x = s1.str();
    command += x;
    command += comma;
    s2 << arg2;
    string y = s2.str();
    command += y;
    sendString(command);
}

/*****************************************************************************************************
* function name: readPoint          			            		        	                     *
* the input: -                                                                                       *
* the output: -                                                                                      *
* the function operation: the function will read the arguments from the server by the client object. *
*****************************************************************************************************/
pair<int, int> Client::readPoint() {
    int x, y;
    char comma;
    pair<int, int> dot;
    int n = read(clientSocket, &x, sizeof(x));
    if (n == -1 || n == 0) {
        throw "Error reading x from socket";
        exit(0);
    }
    n = read(clientSocket, &comma, sizeof(comma));
    if (n == -1 || n == 0) {
        throw "Error reading comma from socket";
    }
    n = read(clientSocket, &y, sizeof(y));
    if (n == -1 || n == 0) {
        throw "Error reading y from socket";
    }
    dot.first = x;
    dot.second = y;
    return dot;
}

/*****************************************************************************************************
* function name: getGamesList
* the input: -
* the output: vector of game names
* the function operation: gets list of game names from server, which available for joining
*****************************************************************************************************/

vector<string> Client::getGamesList() {
    string listGames = "list_games";
    const char* listGamesCommand = listGames.c_str();

    //write command to socket
    int n = write(clientSocket, listGamesCommand, strlen(listGamesCommand));
    if(n == -1) {
        throw "Error writing list_games command to socket";
    }

    //read list games from socket and save as vector
    vector<string> gamesList;

    //read number of names to read
    int numberOfNames;
    n = read(clientSocket, &numberOfNames, sizeof(numberOfNames));
    if(n == -1) {
        throw "Error reading size of games list";
    }

    //read game names
    char buffer[50];
    int confirm = 1;
    for(int i = 0; i < numberOfNames; i++){
        read(clientSocket, buffer, sizeof(buffer));
        write(clientSocket, &confirm, sizeof(confirm));
        string gameName(buffer);
        gamesList.push_back(gameName);
    }
    return gamesList;

}

/*****************************************************************************************************
* function name: start
* the input: -
* the output: player number
* the function operation: starts a game
*****************************************************************************************************/
int Client::start() {
    int playerNumber;
    string command = "start ";
    ui.printString("please choose a game name");
    string name = ui.getString();
    command += name;

    sendString(command);

    ui.printString("waiting for other player to Join");
    //wait to get a player number
    playerNumber = readNumber();
    if (playerNumber == 0) {
        throw "server closed!";
    }
    if (playerNumber == -1) {
        throw "there was an error with the server!";
    }
    if(playerNumber == ILLEGAL_CHOICE) {
        ui.printString("a game with an identical name already exists");
    }
    return  playerNumber;
}

/*****************************************************************************************************
* function name: start
* the input: -
* the output: player number
* the function operation: starts a game
*****************************************************************************************************/

bool Client::printGamesList() {
    vector<string> gamesList = getGamesList();
    if(gamesList.empty()) {
        ui.printString("there are no available games to show");
        return false;
    }
    ui.printString("current available games:");
    for(int i = 0; i < gamesList.size(); i++) {
        ui.printGameName(gamesList[i]);
    }
    ui.printString("");
    ui.printString("\n");
    return true;
}


/*****************************************************************************************************
* function name: start
* the input: -
* the output: player number
* the function operation: starts a game
*****************************************************************************************************/
int Client::join() {
    int playerNumber;

    ui.printString("\nplease choose a game to join:");
    //after print request, reconnect
    connectToServer();

    //get a game choice
    string name = ui.getString();
    string command = "join ";
    command += name;
    sendString(command);

    //wait to get a player number
    playerNumber = readNumber();
    if (playerNumber == 0) {
        throw "server closed!";
    }
    if (playerNumber == -1) {
        throw "there was an error with the server!";
    }
    if(playerNumber == ILLEGAL_CHOICE) {
        ui.printString("there is no available game with the given name");
    }

    return playerNumber;
}
/*****************************************************************************************************
* function name: chooseRemoteGameOption
* the input: -
* the output: player number
* the function operation: using ui to print remote game options and fulfils user choice
*****************************************************************************************************/
int Client::chooseRemoteGameOption() {
    int choice;
    int playerNumber;
    int choiceLegality;
    bool reConnect = false;
    do {
        if(reConnect){
            connectToServer();
            choiceLegality = 1;
        }

        choice = ui.chooseRemoteGameOptions();

        switch(choice) {
            case 1: {
                playerNumber = start();
                if(playerNumber == ILLEGAL_CHOICE){
                    choiceLegality = ILLEGAL_CHOICE;
                    reConnect = true;
                    continue;
                }
                return  playerNumber;
            }
            case 2: {
                int gamesExist = printGamesList();
                if(!gamesExist) {
                    choiceLegality = ILLEGAL_CHOICE;
                    reConnect = true;
                    continue;
                }

                playerNumber = join();

                if(playerNumber == ILLEGAL_CHOICE) {
                    choiceLegality = ILLEGAL_CHOICE;
                    reConnect = true;
                    continue;
                }
                return playerNumber;
            }
            case 3: {
                printGamesList();
                reConnect = true;
            }
            break;
            default:{
                ui.printString("illegal choice.");
                choiceLegality = ILLEGAL_CHOICE;
                reConnect = true;
            }

        }
    } while(choice == 3 || choiceLegality == ILLEGAL_CHOICE);

}