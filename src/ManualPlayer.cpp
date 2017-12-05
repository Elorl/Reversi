/******************************************
* Student name: Elor Lichtziger
* Student: 308541739
* Exercise name: ex1
******************************************/


#include "../include/ManualPlayer.h"

using namespace std;

/*****************************************************************************************************
* function name: Player - constructor							        	                         *
* the input: a color.			                                                                     *
* the output: -                                                                                      *
* the function operation: -                                                                          *
*****************************************************************************************************/
ManualPlayer::ManualPlayer(Color color, UserInterface& ui): ui(ui){
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
* the input: int x int y    			                                                                     *
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
