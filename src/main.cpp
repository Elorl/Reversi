/******************************************
* Student name: Elor Lichtziger           *
* Student: 308541739                      *
* Exercise name: ex1                      *
******************************************/
#define DEFAULTSIZE 8
#include "../include/Board.h"
#include "../include/Game.h"
#include "../include/FlipMoveLogic.h"
#include "../include/AIPlayer.h"
#include "../include/ManualPlayer.h"
#include "../include/ConsoleUI.h"


/*****************************************************************************************************
* function name: main											        	                         *
* the input: -					                                                                     *
* the output: the function will print the board with the lines and rows numbers, and the boards      *
* the function operation: the function will create a board object and will run the printBoard func   *
*****************************************************************************************************/


int main() {
    //ManualPlayer mP1(Black);
    Board b(DEFAULTSIZE,DEFAULTSIZE);
    Board *board = &b;
    ConsoleUI consoleUI;
    ManualPlayer manualPlayer1(Black, consoleUI);
    Player *mp1 = &manualPlayer1;
    Player* p2 = NULL;
    AIPlayer* ai;
    ManualPlayer* p3;
    char c = consoleUI.choosePlayerType();
    if(c == 'a') {
        ai =  new AIPlayer(White, board);
        p2 = ai;
    } else if( c == 'h') {
        p3 = new ManualPlayer(White, consoleUI);
        p2 = p3;
    }

    FlipMoveLogic logic(board, mp1, p2);
    GameLogic *l;
    l = &logic;
    p2->setLogic(l);
    Game game(board, mp1, p2, l, consoleUI);
    game.run();
    if(c == 'a') {
        delete ai;
    } else {
        delete p3;
    }
}