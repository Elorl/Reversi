
#include "ManualPlayer.h"

using namespace std;

/*****************************************************************************************************
* function name: ManualPlayer - constructor							        	                         *
* the input: a color and ui object			                                                         *
* the output: -                                                                                      *
* the function operation: -                                                                          *
*****************************************************************************************************/
ManualPlayer::ManualPlayer(Color color, UserInterface& ui, Board* board): ui(ui), board(board) {
    sendToSrvr = false;
    type = color;
    if(type == Black) {
        symbol = 'X';
    } else {
        symbol = 'O';
    }
}

/*****************************************************************************************************
* function name: ManualPlayer - constructor							        	                         *
* the input: a color, ui object and a client object.			                                     *
* the output: -                                                                                      *
* the function operation: -                                                                          *
*****************************************************************************************************/
ManualPlayer::ManualPlayer(Color color, UserInterface& ui,Board* board, Client* clnt): ui(ui), board(board){
    sendToSrvr = true;
    client = clnt;
    type = color;
    if(type == Black) {
        symbol = 'X';
    } else {
        symbol = 'O';
    }
}

/*****************************************************************************************************
* function name: getType        	    						        	                         *
* the input: -      			                                                                     *
* the output: the function return the color of the player                                            *
* the function operation: -                                                                          *
*****************************************************************************************************/
Color ManualPlayer::getType() {
    return this->type;
}

/*****************************************************************************************************
* function name: chooseOption        	    						        	                     *
* the input: int x int y    			                                                             *
* the output:                                                                                        *
* the function operation: -                                                                          *
*****************************************************************************************************/
void ManualPlayer::chooseOption(int *x, int *y) {
    int *inputX, *inputY;
    char dummy;
    int tempX, tempY;
    inputX = x;
    inputY = y;
    ui.announceTurnPlayer(symbol);
    ui.printOptions(logic->getOptionsMatrix(), board->getRowsNum(), board->getColumnsNum());
    ui.requestIndices();
    cin >> tempX >> dummy >> tempY;
    tempX--;
    tempY--;
    *inputX = tempX;
    *inputY = tempY;
}

/*****************************************************************************************************
* function name: send               	    						        	                     *
* the input: int *x int *y    			                                                             *
* the output:                                                                                        *
* the function operation: the function will send the int's to the server.                            *
*****************************************************************************************************/
void ManualPlayer::send(int *x, int *y) {
    if(*x == -2 && *y == -2) {
        client->sendString("close");
    } else {
        client->sendPoint(*x, ',', *y);
    }
}
/*****************************************************************************************************
* function name: noMove               	    						        	                     *
* the input:                			                                                             *
* the output:                                                                                        *
* the function operation: the function will send '-3' to the server that symbolize to change socket. *
*****************************************************************************************************/
void ManualPlayer::noMove() {
    if(sendToSrvr) {
        int x = -3;
        send(&x, &x);
    }
}