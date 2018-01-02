
#include "Client.h"
#include "UserInterface.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
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
    command.push_back(static_cast<char>(arg1));
    command.push_back(comma);
    command.push_back(static_cast<char>(arg2));
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
    if (n == -1) {
        throw "Error reading x from socket";
    }
    n = read(clientSocket, &comma, sizeof(comma));
    if (n == -1) {
        throw "Error reading comma from socket";
    }
    n = read(clientSocket, &y, sizeof(y));
    if (n == -1) {
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
    for(int i = 0; i < numberOfNames; i++){
        read(clientSocket, buffer, sizeof(buffer));
        string gameName(buffer);
        gamesList.push_back(gameName);
    }
    return gamesList;

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
    do {
        //set legality as legal, for re-looping when needed
        choiceLegality = 1;
        choice = ui.chooseRemoteGameOptions();

        //start
        if(choice == 1) {
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
                choiceLegality = ILLEGAL_CHOICE;
                ui.printString("\n");
                //reconnect, reprint menu
                connectToServer();
                continue;
            }
            //if all correct
            return  playerNumber;
        }
        //join
        if(choice == 2){

            // print list of games
            vector<string> gamesList = getGamesList();
            //if no rooms is available, return to main the flag for reprinting menu
            if(gamesList.empty()) {
                ui.printString("no available games to join.");
                choiceLegality = ILLEGAL_CHOICE;
                ui.printString("\n");
                //reconnect, reprint menu
                connectToServer();
                continue;
            }
            ui.printString("please choose a game to join:");
            for(int i = 0; i < gamesList.size(); i++) {
                ui.printString(gamesList[i]);
            }
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
                choiceLegality = ILLEGAL_CHOICE;
                ui.printString("\n");

                //reconnect, reprint menu
                connectToServer();
                continue;
            }
            //if all correct
            return playerNumber;
        }

        //list of games
        if(choice == 3) {
            vector<string> gamesList = getGamesList();
            if(gamesList.empty()) {
                ui.printString("there is no available room to join:");
                ui.printString("\n");
                continue;
            }
            ui.printString("please choose a game to join:");
            for(int i = 0; i < gamesList.size(); i++) {
                ui.printString(gamesList[i]);
            }
            ui.printString("\n");
            //reconnect to server
            connectToServer();
        }
    } while(choice == 3 || choiceLegality == ILLEGAL_CHOICE);

}