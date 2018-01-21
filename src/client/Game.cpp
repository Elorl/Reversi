
#include "Game.h"
#include <limits>

using namespace std;

/*****************************************************************************************************
* function name: Game - constructor		    					        	                         *
* the input: board = the game's board, player1 and player2 = the players.                            *
* the output: -                                                                                      *
* the function operation:                                                                            *
*****************************************************************************************************/
Game::Game(Board *board, Player *player1, Player *player2, GameLogic *logic, UserInterface& ui) :
        board(board), player1(player1), player2(player2), logic(logic), ui(ui) {

}

/*****************************************************************************************************
* function name: Run            		    					        	                         *
* the input: -                                                                                       *
* the output: -                                                                                      *
* the function operation: this function runs the game.                                               *
*****************************************************************************************************/
void Game::run() {
    int *inputX , *inputY, counter;
    inputX = new int;
    inputY = new int;
    char dummy;
    bool run = true, flag = false;
    Player *currentPlayer = player1;
    player1->setRivalCounter(player2->getCounter());
    player2->setRivalCounter(player1->getCounter());
    Color neg = White;
    while(run){
        counter = 0;
        this->logic->clearOptions();
        ui.printBoard(*board);
        //check the options the player has.
        counter = logic->checkOpt(currentPlayer->getType());
        //check if there is a possible option.
        if(counter > 0) {
            flag = false;
            currentPlayer->chooseOption(inputX, inputY);
            //check if this is a valid chooseOption.
            if(!this->logic->isOptEmpty(inputX, inputY)) {
                do {
                    //check if this is not an integer.
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skip bad chooseOption
                    }
                    ui.requestIndices(false);
                    cin >> *inputX >> dummy >> *inputY;
                    (*inputX)--;
                    (*inputY)--;
                } while(!(this->logic->isOptEmpty(inputX, inputY)));
            }
            //now, startMenu to upside down all the relevant disks.
            this->logic->clearOptions();
            //upside down the relevant disks.
            this->logic->scanAround(*inputX, *inputY, currentPlayer->getType(), neg);
            //check if there is a connection to server.
            if(currentPlayer->sendToServer() == true) {
                //send the choice of the player to the server.
                currentPlayer->send(inputX, inputY);
            }
        //there is no possible option.
        } else {
            ui.noPossibleMove();
            //update the server, if there is one in the game about that.
            currentPlayer->noMove();
            //if flag = true, so this is the second player that has no possible moves.
            if(flag) {
                ui.gameOver();
                run = false;
            } else {
                flag = true;
            }
        }
        if(currentPlayer == player1) {
            currentPlayer = player2;
            neg =  Black;
        } else {
            currentPlayer = player1;
            neg = White;
        }
    }
    this->ui.printPoints(this->player1->getCount(), this->player2->getCount());
    this->logic->clearOptions();
    //send to the server massage that the game is end.
    if(currentPlayer->sendToServer() == true) {
        int endGame = -2;
        currentPlayer->send(&endGame, &endGame);
    }
    delete inputX;
    delete inputY;
}

