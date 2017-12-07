
#define DEFAULT_SIZE 8
#include "Board.h"
#include "Game.h"
#include "FlipMoveLogic.h"
#include "AIPlayer.h"
#include "ManualPlayer.h"
#include "ConsoleUI.h"
#include "Client.h"
#include <utility>
#include <libio.h>
#include <cstdio>
#include <cstdlib>


/*****************************************************************************************************
* function name: main											        	                         *
* the input: -					                                                                     *
* the output: the function will print the board with the lines and rows numbers, and the boards      *
* the function operation: the function will create a board object and will run the printBoard func   *
*****************************************************************************************************/
pair<const char*, int> readFIle();

int main() {
    //ManualPlayer mP1(Black);

    Board b(DEFAULT_SIZE,DEFAULT_SIZE);
    Board *board = &b;
    ConsoleUI consoleUI;
    ManualPlayer manualPlayer1(Black, consoleUI);
    Player *mp1 = &manualPlayer1;
    Player* p2;
    AIPlayer* ai;
    ManualPlayer* p3;
    int i = consoleUI.choosePlayerType();
    switch (i) {
        case 1:
            p3 = new ManualPlayer(White, consoleUI);
            p2 = p3;
        case 2:
            ai =  new AIPlayer(White, board);
            p2 = ai;
        case 3:
            pair <const char*, int> pair;
            pair = readFIle();
            Client client(pair.first, pair.second);
    }
    FlipMoveLogic logic(board, mp1, p2);
    GameLogic *l;
    l = &logic;
    p2->setLogic(l);
    Game game(board, mp1, p2, l, consoleUI);
    game.run();
    if(i == 2) {
        delete ai;
    } else {
        delete p3;
    }
}

pair<const char*, int> readFIle() {
    int i = 0, prt;
    bool flag = false;
    pair <const char*, int> pair;
    FILE *settings;
    settings = fopen("../settings.txt", "r");
    char ip[15], port[5];
    char buffer[1];
    //check if the opening of the source file have been failed.
    if (settings == NULL) {
        printf("there is no settings file.");
        pair.first = NULL;
        pair.second = NULL;
    } else {
        while (fread(buffer, 1, 1, settings)) {
            if(buffer[0] == ',') {
                ip[i] = '\0';
                flag = true;
                i = 0;
            } else {
                if(!flag) {
                    ip[i] = buffer[0];
                    i++;
                } else {
                    port[i] = buffer[0];
                    i++;
                }
            }
        }
        pair.first = ip;
        pair.second = atoi(port);
    }
    return pair;
};