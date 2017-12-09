
#include "ManualPlayer.h"
#include "Client.h"

using namespace std;

/*****************************************************************************************************
* function name: ManualPlayer - constructor							        	                         *
* the input: a color and ui object			                                                         *
* the output: -                                                                                      *
* the function operation: -                                                                          *
*****************************************************************************************************/
ManualPlayer::ManualPlayer(Color color, UserInterface& ui): ui(ui) {
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
ManualPlayer::ManualPlayer(Color color, UserInterface& ui, Client* clnt): ui(ui){
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
    cout << endl << endl;
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
    client->sendPoint(*x, ',', *y);
}