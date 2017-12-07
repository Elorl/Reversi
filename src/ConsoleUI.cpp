
#include "ConsoleUI.h"
/*****************************************************************************************************
* function name: printBoard.        							        	                         *
* the input:        			                                                                     *
* the output: a print of the board.                                                                  *
* the function operation: there is a nested loop that runs all the board and print the cells.        *
*****************************************************************************************************/
void ConsoleUI::printBoard(Board& b) {
    int rowsNum = b.getRowsNum();
    int colsNum = b.getColumnsNum();
    Cell** boardArr = b.boardArr;

    cout << "current board:" << endl << endl;
    //print the first line.
    cout << " | ";
    for(int i=1; i<rowsNum +1; i++) {
        cout << i << " | ";
    }
    cout << endl;
    cout << string(colsNum * 4 + 2, '-') << endl;

    //print the next ones lines.
    //the loop runs all over the array's rows.
    for(int row = 0; row < rowsNum; row++)
    {
        cout << row + 1<< "|";
        //the loop runs all over the array's columns.
        for(int column = 0; column<colsNum; column++)
        {
            //check if the cell is empty or not.
            if(boardArr[row][column].getColor() == Empty){
                cout << "   |";
            } else {
                if(boardArr[row][column].getColor() == White) {
                    cout << ' ' << 'O' << " |";
                } else {
                    cout << ' ' << 'X' << " |";
                }
            }
        }
        cout << endl;
        cout << string(colsNum * 4 + 2, '-') << endl;
    }
}


/*****************************************************************************************************
* function name: printPoints                              	    					        	     *
* the input: -                                                                                       *
* the output: -                                                                                      *
* the function operation: print the results of the game.                                             *
*****************************************************************************************************/
void ConsoleUI::printPoints(int bPoints, int wPoints) {
    cout << "Black player got " << bPoints << " points" << endl;
    cout << "White player got " << wPoints << " points" << endl;
    if(bPoints > wPoints) {
        cout<< "the winner is: the Black player";
    } else if(bPoints < wPoints) {
        cout<< "the winner is: the White player";
    } else {
        cout<< "Its a draw";
    }
}

/*****************************************************************************************************
* function name: printOpt            		    					        	                     *
* the input: count = the number of options to print.                                                 *
* the output: -                                                                                      *
* the function operation: print the options to the user.                                             *
*****************************************************************************************************/
void ConsoleUI::printOptions(Cell** optionsMatrix, int rows, int cols) {
    cout << "Possible moves: "<<endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j <cols; j++) {
            if (optionsMatrix[i][j].getColor() != Empty) {
                cout << '(' << optionsMatrix[i][j].getX() + 1<< ',' << optionsMatrix[i][j].getY() + 1 << ')';
            }
        }
    }
}

/*****************************************************************************************************
* function name: requestIndices            		    					        	                 *
* the input: count = the number of options to print.                                                 *
* the output: -                                                                                      *
* the function operation: print the options to the user.                                             *
*****************************************************************************************************/

void ConsoleUI::requestIndices(bool isFirstTime) {
    if(isFirstTime) {
        cout << "Please enter your move row,col:  ";
        return;
    }
    cout << "Please enter correct move row,col:  ";
}

void ConsoleUI::announceTurnPlayer(Player &player) {
    cout << player.getSymbol() << " turn." << endl;
}

void ConsoleUI::noPossibleMove() {
    cout << "No possible moves. Play passes back to the other player." << endl;
}

void ConsoleUI::gameOver() {
    cout << "No possible moves. Game over!" << endl;
}
int ConsoleUI::choosePlayerType() {
    int i;
    cout << "choose an opponent type:" <<endl;
    cout<< "1. a human local player" << endl;
    cout<< "2. an AI player" << endl;
    cout<< "3. a remote player" << endl;
    cin >> i;

    while(i < 1 || i > 3) {
        cin.clear();
        cin.ignore('\n');
        cout << "Please choose correct type:"<<endl;
        cout<< "1. a human local player" << endl;
        cout<< "2. an AI player" << endl;
        cout<< "3. a remote player" << endl;
        cin >> i;
    }
    return i;
}