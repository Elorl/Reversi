
#define DEFAULT_SIZE 8
#include "Board.h"
#include "Game.h"
#include "FlipMoveLogic.h"
#include "AIPlayer.h"
#include "ManualPlayer.h"
#include "ConsoleUI.h"
#include "RemotePlayer.h"
#include <libio.h>
#include <cstdio>
#include <cstdlib>
#include <fstream>


/*****************************************************************************************************
* function name: main											        	                         *
* the input: -					                                                                     *
* the output: the function will print the board with the lines and rows numbers, and the boards      *
* the function operation: the function will create a board object and will run the printBoard func   *
*****************************************************************************************************/
pair<string, int> readFIle();

int main() {
    //ManualPlayer mP1(Black);

    Board b(DEFAULT_SIZE,DEFAULT_SIZE);
    Board *board = &b;
    ConsoleUI consoleUI;
    Player *p1, *p2;
    Client *client;
    int i = consoleUI.choosePlayerType();
    switch (i) {
        case 1:
            p1 = new ManualPlayer(Black, consoleUI);
            p2 = new ManualPlayer(White, consoleUI);
            break;
        case 2:
            p1 = new ManualPlayer(Black, consoleUI);
            p2 =  new AIPlayer(White, board);
            break;
        case 3:
            pair <string, int> pair;
            pair = readFIle();
            client = new Client(pair.first.c_str(), pair.second);
            int number = client->connectToServer();
            if(number == 1) {
                p1 = new ManualPlayer(Black, consoleUI, client);
                p2 = new RemotePlayer(White, consoleUI, client);
            } else if(number == 2) {
                p1 = new RemotePlayer(Black, consoleUI, client);
                p2 = new ManualPlayer(White, consoleUI, client);
            }
            break;
    }
    FlipMoveLogic logic(board, p1, p2);
    GameLogic *l;
    l = &logic;
    p2->setLogic(l);
    Game game(board, p1, p2, l, consoleUI);
    game.run();
    //check if there is a client object inside the players.
    if(p1->sendToServer() || p2->sendToServer()) {
        delete(client);
    }
    delete(p1);
    delete(p2);
}

pair<string, int> readFIle() {
    int i = 0;
    bool flag = false;
    pair <string, int> pair;
    ifstream settings;
    string ip, port;
    settings.open("../settings.txt");
    if(settings == NULL) {
        cout << "there is no settings file.";
        pair.first = "-1";
        pair.second = -1;
    } else {
        getline(settings,ip);
        getline(settings,port);
    }
    int prt = atoi(port.c_str());
        pair.first = ip;
        pair.second = prt;
    return pair;
}