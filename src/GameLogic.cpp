/******************************************
* Student name: Elor Lichtziger
* Student: 308541739
* Exercise name: ex1
******************************************/

#include "../include/GameLogic.h"
#include <iostream>
using namespace std;
/*****************************************************************************************************
* function name: GameLogic - constructor		    					        	                 *
* the input: board                           *
* the output: -                                                                                      *
* the function operation:                                                                            *
*****************************************************************************************************/
GameLogic::GameLogic(Board *board){
    this->board = board;
    // allocating options array
    optionsMatrix = new Cell *[board->getRowsNum()];
    for (int i = 0; i < board->getRowsNum(); i++) {
        optionsMatrix[i] = new Cell[board->getColumnsNum()];
    }
    //filling with corresponding indices
    for(int i = 0; i < this->board->getRowsNum(); i++) {
        for( int j = 0; j < this->board->getColumnsNum(); j++) {
            this->optionsMatrix[i][j].setX(i);
            this->optionsMatrix[i][j].setY(j);
        }
    }
}

/*****************************************************************************************************
* function name: GameLogic - destructor		    					        	                     *
* the input: board                                                                                   *
* the output: -                                                                                      *
* the function operation:                                                                            *
*****************************************************************************************************/

GameLogic::~GameLogic() {
    for (int i = 0; i < board->getRowsNum(); i++) {
        delete[] optionsMatrix[i];
    }
    delete[] optionsMatrix;
}

/*****************************************************************************************************
* function name: initializeOpt            		    					        	                 *
* the input: -                                                                                       *
* the output: -                                                                                      *
* the function operation: initialize the array of options.                                           *
*****************************************************************************************************/

void GameLogic::clearOptions() {
    for(int i = 0; i < this->board->getRowsNum(); i++) {
        for(int j = 0; j < this->board->getColumnsNum(); j++) {
            this->optionsMatrix[i][j].setColor(Empty);
        }
    }
}

/******************************************************************************************************
* function name: validOpt            	    					        	                          *
* the input: i, j = the cell cords                                                                    *
* the output: true = the input is a valid cell, false = the cell is not valid.                        *
* the function operation: this function will check if the index are legal and the cell is valid option*
******************************************************************************************************/
bool GameLogic::isOptEmpty(int *x, int *y) {
    int validX = *x;
    int validY = *y;
    //check if the indexs are legal and if the cell is truly a valid option.
    if(validX >= 0 && validX < this->board->getRowsNum()
       && validY >= 0 && validY < this->board->getColumnsNum()) {
        if(this->optionsMatrix[*x][*y].getColor() != Empty) {
            return true;
        }
    }
    return false;
}
/******************************************************************************************************
* function name: getOptionsMatrix           	    					        	                  *
* the input:                                                                                          *
* the output:                                                                                         *
* the function operation: gets matrix of options                                                      *
******************************************************************************************************/
Cell** GameLogic::getOptionsMatrix() {
    return  optionsMatrix;
}

/******************************************************************************************************
* function name: setOptions          	    					        	                          *
* the input: -                                                                                        *
* the output: -                                                                                       *
* the function operation: setting options matrix
******************************************************************************************************/
void GameLogic::setOptions(Cell** optionMatrix) {
    for (int i = 0; i < this->board->getRowsNum(); i++) {
        for (int j = 0; j < this->board->getColumnsNum(); j++) {
            this->optionsMatrix[i][j] = optionsMatrix[i][j];
        }
    }
}