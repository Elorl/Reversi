
#define DEFAULT_SIZE 8
#include "Board.h"
#include "Game.h"
#include "FlipMoveLogic.h"
#include "AIPlayer.h"
#include "ManualPlayer.h"
#include "ConsoleUI.h"
#include "RemotePlayer.h"
#include <cstdlib>
#include <fstream>


/*****************************************************************************************************
* function name: readFIle											        	                     *
* the input: -					                                                                     *
* the output: the function will print the board with the lines and rows numbers, and the boards      *
* the function operation: the function will create a board object and will run the printBoard func   *
*****************************************************************************************************/
pair<string, int> readFIle();

int main() {
    Board b(DEFAULT_SIZE,DEFAULT_SIZE);
    Board *board = &b;
    ConsoleUI consoleUI;
    AIPlayer *ai;
    Player *p1, *p2;
    Client *client;
    int i = consoleUI.choosePlayerType();
    switch (i) {
        case 1:
            p1 = new ManualPlayer(Black, consoleUI, board);
            p2 = new ManualPlayer(White, consoleUI, board);
            break;
        case 2:
            p1 = new ManualPlayer(Black, consoleUI, board);
            ai =  new AIPlayer(White, consoleUI, board);
            p2 = ai;
            break;
        case 3:
            pair <string, int> pair;
            pair = readFIle();
            //allocate new client object
            client = new Client(pair.first.c_str(), pair.second);
            int number = client->connectToServer();
            //check who is the first player, this computer(Manual) or the other on(Remote).
            if(number == 1) {
                p1 = new ManualPlayer(Black, consoleUI, board, client);
                p2 = new RemotePlayer(White, consoleUI, client);
            } else if(number == 2) {
                p1 = new RemotePlayer(Black, consoleUI, client);
                p2 = new ManualPlayer(White, consoleUI, board, client);
            }
            break;
    }
    FlipMoveLogic logic(board, p1, p2);
    GameLogic *l;
    l = &logic;
    p2->setLogic(l);
    p1->setLogic(l);
    Game game(board, p1, p2, l, consoleUI);
    game.run();
    //check if there is a client object inside the players.
    if(p1->sendToServer() || p2->sendToServer()) {
        delete(client);
    }
    delete(p1);
    if(i == 2) {
        delete(ai);
    } else {
        delete(p2);
    }

}


/*****************************************************************************************************
* function name: readFIle											        	                     *
* the input: -					                                                                     *
* the output: a pair with the ip address(pair.first) and the port(pair.second).                      *
* the function operation: the function will open settings file and scan the lines to get ip and port *
*****************************************************************************************************/
pair<string, int> readFIle() {
    int i = 0;
    bool flag = false;
    pair <string, int> pair;
    ifstream settings;
    string ip, port;
    //open the settings file.
    settings.open("settings.txt");
    //check if the open action was succeed.
    if(settings == NULL) {
        cout << "there is no settings file.";
        pair.first = "-1";
        pair.second = -1;
    //scan the lines to get the ip and port.
    } else {
        getline(settings,ip);
        getline(settings,port);
    }
    //convert the port from string to int.
    int prt = atoi(port.c_str());
    pair.first = ip;
    pair.second = prt;
    return pair;
}