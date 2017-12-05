//Avner Merhavi 203090436

// 28/11/17.
//

#include "../include/AIPlayer.h"

/*****************************************************************************************************
* function name: constructor							        	                         *
* the input:        			                                                                     *
* the output: -                                                                                      *
* the function operation: -                                                                          *
*****************************************************************************************************/
AIPlayer::AIPlayer(Color color, Board* board): board(board){
    type = color;
    if(type == Black) {
        symbol = 'X';
    } else {
        symbol = 'O';
    }

    if(color == Black) {
        rivalColor = White;
    }
    else if(color == White) {
        rivalColor = Black;
    }

    //allocate board backups
    initialBoardBackup = new Cell*[board->getRowsNum()];
    subBoardbackup = new Cell*[board->getRowsNum()];
    playerOptions = new Cell*[board->getRowsNum()];
    rivalOptions = new Cell*[board->getRowsNum()];
    for(int i = 0; i < board->getRowsNum(); i ++) {
        initialBoardBackup[i] = new Cell[board->getColumnsNum()];
        subBoardbackup[i] = new Cell[board->getColumnsNum()];
        rivalOptions[i] = new Cell[board->getColumnsNum()];
        playerOptions[i] = new Cell[board->getColumnsNum()];
    }
}
/*****************************************************************************************************
* function name: destructor							        	                         *
* the input:        			                                                                     *
* the output: -                                                                                      *
* the function operation: -                                                                          *
*****************************************************************************************************/
AIPlayer::~AIPlayer() {
    freeMatrix(initialBoardBackup);
    freeMatrix(subBoardbackup);
    freeMatrix(playerOptions);
    freeMatrix(rivalOptions);
}
/*****************************************************************************************************
* function name: getType							        	                         *
* the input:        			                                                                     *
* the output: -                                                                                      *
* the function operation: returns color of player                                                                        *
*****************************************************************************************************/
Color AIPlayer::getType() {
    return type;
}

/*****************************************************************************************************
* function name: chooseOption							        	                                 *
* the input:        			                                                                     *
* the output: -                                                                                      *
* the function operation: initializing the chosen options indices                                                                      *
*****************************************************************************************************/
void AIPlayer::chooseOption(int *x, int *y) {
    Cell chosenCell = chooseMinMax();
    *x = chosenCell.getX();
    *y = chosenCell.getY();
    //put this single option in the logic optionsMatrix
    logic->getOptionsMatrix()[*x][*y].setColor(this->getType());
}


/*****************************************************************************************************
* function name: chooseMinMax						        	                                     *
* the input:        			                                                                     *
* the output: -                                                                                      *
* the function operation: computing options and chooses the best in terms of minMax                                                                     *
*****************************************************************************************************/

Cell AIPlayer::chooseMinMax() {

    //save initial boardArr
    for(int i = 0; i < board->getRowsNum(); i ++) {
        for(int j = 0 ; j < board->getColumnsNum(); j++) {
            initialBoardBackup[i][j] =  board->boardArr[i][j];
        }
    }
    //save initial current player points counter
    Cell minMaxCell;
    int minOfRivalMax;

    int CurrentPointsBackpup;
    int rivalPointsBackup;
    CurrentPointsBackpup = this->getCount();
    rivalPointsBackup = rivalCounter->get();

    // check options (will be saved in internal logic member)
    logic->checkOpt(this->type);

    //save options of current player
    for(int i = 0; i < board->getRowsNum(); i ++) {
        for(int j = 0 ; j < board->getColumnsNum(); j++) {
            playerOptions[i][j] =  logic->getOptionsMatrix()[i][j];
        }
    }
    //play each option
    bool isFirstMove = true;
    int lastRivalMax;
    for(int i = 0; i < board->getRowsNum(); i ++) {
        for(int j = 0 ; j < board->getColumnsNum(); j++) {
            if(playerOptions[i][j].getColor() == this->type) {
                logic->clearOptions();
               logic->scanAround(i, j, this->type, this->rivalColor);

                //play all possible rivals moves, and get max
                lastRivalMax = getMaxRivalMove();
                if(isFirstMove) {
                    minOfRivalMax = lastRivalMax;
                    minMaxCell = Cell(i, j, this->type);
                    isFirstMove = false;
                } else if(lastRivalMax < minOfRivalMax ){
                    minOfRivalMax = lastRivalMax;
                    minMaxCell = Cell(i, j, this->type);
                }
            }
            // take back the boardArr, as if we did not play last option
            board->setBoardArr(initialBoardBackup);
            //set point back as if we did not play last option
            this->setCount(CurrentPointsBackpup);
            rivalCounter->setCount(rivalPointsBackup);
        }
    }
    return minMaxCell;

}

/*****************************************************************************************************
* function name: getMaxRivalMove						        	                                 *
* the input:        			                                                                     *
* the output: -                                                                                      *
* the function operation: returns the max score of rival move for a specific move of current player                                                                    *
*****************************************************************************************************/
int AIPlayer::getMaxRivalMove() {
    int maxScore;
    int rivalPointsBackup = rivalCounter->get();
    int currentPointsBackup  = this->getCount();

    // check options
    logic->checkOpt(rivalColor);

    //save options of rival
    for(int i = 0; i < board->getRowsNum(); i ++) {
        for(int j = 0 ; j < board->getColumnsNum(); j++) {
            rivalOptions[i][j] =  logic->getOptionsMatrix()[i][j];
        }
    }
    //save board state after current player move
    for(int i = 0; i < board->getRowsNum(); i ++) {
        for(int j = 0 ; j < board->getColumnsNum(); j++) {
            subBoardbackup[i][j] =  board->boardArr[i][j];
        }
    }

    //play each option
    bool isFirstMove = true;
    for(int i = 0; i < board->getRowsNum(); i ++) {
        for(int j = 0 ; j < board->getColumnsNum(); j++) {
            if(rivalOptions[i][j].getColor() == rivalColor) {
                logic->clearOptions();
                logic->scanAround(i, j, rivalColor, this->type);
                int moveScore = (rivalCounter->get()) - (this->getCount());

                if(isFirstMove) {
                    maxScore = moveScore;
                    isFirstMove = false;
                } else if(moveScore > maxScore) {
                    maxScore = moveScore;
                }
            }

            // take back the boardArr to state before playing
            board->setBoardArr(subBoardbackup);
            //take back counter as before checking option
            rivalCounter->setCount(rivalPointsBackup);
            this->counter->setCount(currentPointsBackup);
        }
    }
    return maxScore;

}
/*****************************************************************************************************
* function name: freeMatrix				        	                                                 *
* the input:        			                                                                     *
* the output: -                                                                                      *
* the function operation: free matrix                                                                   *
*****************************************************************************************************/
void  AIPlayer::freeMatrix(Cell **matrix) {
    for(int i = 0; i < board->getRowsNum(); i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}
