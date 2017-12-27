
#include "Client.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

using namespace std;

/*****************************************************************************************************
* function name: Client - constructor			            		        	                     *
* the input: serverIP = ip address, serverPort = port number.       			                     *
* the output: -                                                                                      *
* the function operation: -                                                                          *
*****************************************************************************************************/
Client::Client(const char *serverIP, int serverPort): serverIP(serverIP), serverPort(serverPort), clientSocket(0) {
    cout << "Client" << endl;
}

/*****************************************************************************************************
* function name: connectToServer    			            		        	                     *
* the input: -                                                         			                     *
* the output: 1 = this computer is the first player, 2 = this computer is the second player.         *
* the function operation: the function will connect to the server and get the number from him.       *
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
    cout << "Connected to server" << endl;
    cout << "waiting for other player to Join" << endl;
    int n = read(clientSocket, &playerNumber, sizeof(playerNumber));
    return playerNumber;
}

/*****************************************************************************************************
* function name: sendPoint          			            		        	                     *
* the input: arg1 = the x cord of the cell, arg2= the y cord of the cell.                            *
* the output: -                                                                                      *
* the function operation: the function will send the arguments to the server by the client object.   *
*****************************************************************************************************/
void Client::sendPoint(int arg1, char comma, int arg2) {
    int n = write(clientSocket, &arg1, sizeof(arg1));
    if (n == -1) {
        throw "Error writing arg1 to socket";
    }
    n = write(clientSocket, &comma, sizeof(comma));
    if (n == -1) {
        throw "Error writing comma to socket";
    }
    n = write(clientSocket, &arg2, sizeof(arg2));
    if (n == -1) {
        throw "Error writing arg2 to socket";
    }
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