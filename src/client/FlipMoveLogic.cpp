
#include "FlipMoveLogic.h"



using namespace std;
/*****************************************************************************************************
* function name: ManualLogic - constructor		    					        	                 *
* the input: board = the game's board, player1 and player2 = the players.                            *
* the output: -                                                                                      *
* the function operation:                                                                            *
*****************************************************************************************************/
FlipMoveLogic::FlipMoveLogic(Board *board, Player *player1, Player *player2) :
        GameLogic(board), player1(player1), player2(player2) {
    this->counter = 0;
}

/*****************************************************************************************************
* function name: checkOpt            	    					        	                         *
* the input: the color of the player.                                                                *
* the output: -                                                                                      *
* the function operation: this function runs all over the board and looking for a cell that belongs  *
* to the player.                                                                                     *
*****************************************************************************************************/
int FlipMoveLogic::checkOpt(Color color) {
    this->counter = 0;
    Color negColor, originColor;
    for(int i = 0; i < this->board->getRowsNum(); i++) {
        for (int j = 0; j < this->board->getColumnsNum(); j++) {
            if(this->board->boardArr[i][j].getColor() == color) {
                int row = i;
                int column = j;
                if(color == White) {
                    originColor = White;
                    negColor = Black;
                } else {
                    originColor = Black;
                    negColor = White;
                }
                scanAround(row, column, originColor, negColor, Find);
            }
        }
    }
    return counter;
}

/*****************************************************************************************************
* function name: scanOpt            	    					        	                         *
* the input: row, column = the point cords, originColor = player's color, negColor = rival's color.  *
* the output: -                                                                                      *
* the function operation: this function runs all over the 8 cells near the cell with the original    *
* color. if there is a negative cell, its possibly an option, so the function will find this cell    *
* and will send him to directionScan, to find if this cell is a truly option.                        *
*****************************************************************************************************/
void FlipMoveLogic::scanAround(int row, int column, Color originColor, Color negColor) {
    Action action = Upside;
    scanAround(row, column, originColor, negColor, action);
}

/*****************************************************************************************************
* function name: scanOpt            	    					        	                         *
* the input: row, column = the point cords, originColor = player's color, negColor = rival's color.  *
* the output: -                                                                                      *
* the function operation: this function runs all over the 8 cells near the cell with the original    *
* color. if there is a negative cell, its possibly an option, so the function will find this cell    *
* and will send him to directionScan, to find if this cell is a truly option.                        *
*****************************************************************************************************/
void FlipMoveLogic::scanAround(int row, int column, Color playerColor, Color negColor, Action act) {
    Action action = act;
    int startX = row, startY = column;
    int changeX = 0, changeY = 0;
    int rowsNum = this->board->getRowsNum();
    int columnsNum = this->board->getColumnsNum();
    //runs the near cells.
    for (int i = row - 1; i <= row + 1 ; ++i) {
        for (int j = column - 1; j <= column + 1 ; ++j) {
            //check if the cords is not in the board.
            if(i < 0 || i >= rowsNum || j < 0 || j >= columnsNum) {
                continue;
            } else {
                //check if this cell is irrelevant = empty or in the same color as the player.
                if(this->board->boardArr[i][j].getColor() == playerColor
                   || this->board->boardArr[i][j].getColor() == Empty) {
                    continue;
                } else {
                    changeX = i - startX;
                    changeY = j - startY;
                    //check if the next step is to continue with the search or to upside down the disks.
                    if(action == Upside) {
                        if(!(this->board->boardArr[startX][startY].getColor() == playerColor)) {
                            this->optionsMatrix[startX][startY].setColor(playerColor);
                        }
                        //add the cell to the option array(relevant cell).
                        //this->optionsMatrix[i][j].setColor(playerColor);
                        this->directionScanFlip(i, j, changeX, changeY, playerColor, negColor);
                    } else {
                        this->directionScan(i, j, changeX, changeY, playerColor, negColor);
                    }
                }
            }
        }
    }
}

/*****************************************************************************************************
* function name: directionScan            	    					        	                     *
* the input: i, j = the point cords, changeRow and changeColumn = the change between the points,     *
* originColor = player's color, negColor = rival's color.                                            *
* the output: -                                                                                      *
* the function operation: this function will search the next cell in the relevant direction(depends  *
* the value of the DELTA(changeRow, changeColums). if the cell is what we are looking for, the       *
* function will and the cell to the options array.                                                   *
*****************************************************************************************************/
void FlipMoveLogic::directionScan(int i, int j, int changeRow, int changeColumn, Color playerColor, Color negColor) {
    bool flag = true;
    while(flag){
        i += changeRow;
        j += changeColumn;
        //check if the cell is irrelevant = the same color as the player (XOX) or not in the board.
        if(i < 0 || j < 0 || i >= this->board->getRowsNum()
           || j >= this->board->getColumnsNum()||this->board->boardArr[i][j].getColor() == playerColor) {
            return;
            //we found an empty cell after cells with negColor, so this is valid option.
        } else if(this->board->boardArr[i][j].getColor() == Empty) {
            this->optionsMatrix[i][j].setColor(playerColor);
            counter++;
            flag = false;
            //the cell is with negColor, so continue scanning.
        } else {
            //נניח הצבע ההתחלתי היה שחור, זה חיפש עכשיו לבנים ופגש עוד לבן, אז פועלים באופן רקורסיבי
            directionScan(i, j, changeRow, changeColumn, playerColor, negColor);
        }
    }
}

/*****************************************************************************************************
* function name: directionScanFlip            	    					        	                 *
* the input: i, j = the point cords, changeRow and changeColumn = the change between the points,     *
* originColor = player's color, negColor = rival's color.                                            *
* the output: -                                                                                      *
* the function operation: this function will search the next cell in the relevant direction(depends  *
* the value of the DELTA(changeRow, changeColums). if the cell is what we are looking for, the       *
* function will add the cell to the options array, so in the end of the function all the array will  *
* upside down.                                                                                       *
*****************************************************************************************************/
void FlipMoveLogic::directionScanFlip(int i, int j, int changeRow, int changeColumn, Color originColor, Color negColor) {
    int x = i, y = j;
    if(x < 0 || x >= this->board->getRowsNum() || y < 0 || y >= this->board->getColumnsNum()) {
        this->clearOptions();
        return;
    }
    //if the next cell is negative color, add to
    if(this->board->boardArr[i][j].getColor() == negColor) {
        //add the cell to the option array(relevant cell).
        this->optionsMatrix[i][j].setColor(originColor);
        x += changeRow;
        y += changeColumn;
        this->directionScanFlip(x, y, changeRow, changeColumn, originColor, negColor);
        //find the originColor cell, so we can upside down the option array.
    } else if(this->board->boardArr[i][j].getColor() == originColor){
        for(int a = 0; a < this->board->getRowsNum(); a++) {
            for(int b = 0; b < this->board->getColumnsNum(); b++) {
                if(this->optionsMatrix[a][b].getColor() != Empty) {
                    this->flip(a, b, originColor);
                }
            }
        }
        //the cell is irrelevant.
    } else {
        this->clearOptions();
        return;
    }
    this->clearOptions();
}

/*****************************************************************************************************
* function name: flip            	    					        	                         *
* the input: i, j = the cell cords, color = the new color of the upside down cell.                   *
* the output: -                                                                                      *
* the function operation: this function will increase/ decreade the player's points and will change  *
* cell's color to the new color.                                                                     *
*****************************************************************************************************/
void FlipMoveLogic::flip(int x, int y, Color color) {
    if(this->board->boardArr[x][y].getColor() == Empty) {
        if(this->player1->getType() == color) {
            this->player1->increase();
        } else {
            this->player2->increase();
        }
    } else {
        if(this->player1->getType() == color) {
            this->player1->increase();
            this->player2->decrease();
        } else {
            this->player2->increase();
            this->player1->decrease();
        }
    }
    this->board->boardArr[x][y].setColor(color);
    //cout << "try";
}