
#include "RemotePlayer.h"

using namespace std;

/*****************************************************************************************************
* function name: RemotePlayer - constructor							        	                         *
* the input: a color, ui object and a client object.			                                     *
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

/*****************************************************************************************************
* function name: send               	    						        	                     *
* the input: int *x int *y    			                                                             *
* the output:                                                                                        *
* the function operation: the function will send the int's to the server.                            *
*****************************************************************************************************/
void RemotePlayer::send(int *x, int *y) {
}

/*****************************************************************************************************
* function name: chooseOption        	    						        	                     *
* the input: int x int y    			                                                             *
* the output:                                                                                        *
* the function operation:the function will get the choice from the server and update the x,y pointers*
*****************************************************************************************************/
void RemotePlayer::chooseOption(int *x, int *y) {
    int *inputX, *inputY;
    pair<int, int> dot;
    inputX = x;
    inputY = y;
    ui.waitingMoveRemote();
    dot = client->readPoint();
    *inputX = dot.first;
    *inputY = dot.second;
    ui.printMove(symbol, *inputX, *inputY);
}
