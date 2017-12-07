
#define DEFAULT_SIZE 8
#include "Board.h"
#include "Game.h"
#include "FlipMoveLogic.h"
#include "AIPlayer.h"
#include "ManualPlayer.h"
#include "ConsoleUI.h"


/*****************************************************************************************************
* function name: main											        	                         *
* the input: -					                                                                     *
* the output: the function will print the board with the lines and rows numbers, and the boards      *
* the function operation: the function will create a board object and will run the printBoard func   *
*****************************************************************************************************/


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
            //יצירת שחקן remote וקליינט
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