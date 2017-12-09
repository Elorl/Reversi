
#include "RemotePlayer.h"

/*****************************************************************************************************
* function name: Player - constructor							        	                         *
* the input: a color, ui object and client object.			                                                                     *
* the output: -                                                                                      *
* the function operation: -                                                                          *
*****************************************************************************************************/
RemotePlayer::RemotePlayer(Color color, UserInterface &ui, Client *clnt): ui(ui) {
    sendToSrvr = false;
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
Color RemotePlayer::getType() {
    return this->type;
}

void RemotePlayer::send(int *x, int *y) {
}

void RemotePlayer::chooseOption(int *x, int *y) {
    int *inputX, *inputY;
    pair<int, int> dot;
    inputX = x;
    inputY = y;
    dot = client->readPoint();
    *inputX = dot.first;
    *inputY = dot.second;
}
