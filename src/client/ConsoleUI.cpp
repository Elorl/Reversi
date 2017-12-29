
#include <limits>
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
    cout << "Your possible moves: ";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j <cols; j++) {
            if (optionsMatrix[i][j].getColor() != Empty) {
                cout << '(' << optionsMatrix[i][j].getX() + 1<< ',' << optionsMatrix[i][j].getY() + 1 << ')';
            }
        }
    }
    cout << endl << endl;
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

/*****************************************************************************************************
* function name: announceTurnPlayer            		    					        	             *
* the input: count = the number of options to print.                                                 *
* the output: -                                                                                      *
* the function operation: print the options to the user.                                             *
*****************************************************************************************************/
void ConsoleUI::announceTurnPlayer(char symbol) {
    cout << symbol << ": It's your move." << endl;
}

/*****************************************************************************************************
* function name: noPossibleMove                                                                      *
* the input: -                                                                                       *
* the output: -                                                                                      *
* the function operation: prints an announcment that there are no possible moves.                    *
*****************************************************************************************************/
void ConsoleUI::noPossibleMove() {
    cout << "No possible moves. Play passes back to the other player." << endl;
}

/*****************************************************************************************************
* function name: gameOver                                                                            *
* the input: -                                                                                       *
* the output: -                                                                                      *
* the function operation: prints game over announcement.                                             *
*****************************************************************************************************/
void ConsoleUI::gameOver() {
    cout << "No possible moves. Game over!" << endl;
}

/*****************************************************************************************************
* function name: choosePlayerType                                                                    *
* the input: -                                                                                       *
* the output: -                                                                                      *
* the function operation: prints the options of the rival type and get the player choice             *
*****************************************************************************************************/
int ConsoleUI::choosePlayerType() {
    int i;
    cout << "choose an opponent type:" <<endl;
    cout<< "1. a human local player" << endl;
    cout<< "2. an AI player" << endl;
    cout<< "3. a remote player" << endl;
    cin >> i;
    while(i < 1 || i > 3) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Please choose correct type:"<<endl;
        cout<< "1. a human local player" << endl;
        cout<< "2. an AI player" << endl;
        cout<< "3. a remote player" << endl;
        cin >> i;
    }
    cin.clear();
    return i;
}

/*****************************************************************************************************
* function name: waitingMoveRemote                                                                   *
* the input: -                                                                                       *
* the output: -                                                                                      *
* the function operation: print to the console the massage about waiting for the second computer move*
*****************************************************************************************************/
void ConsoleUI::waitingMoveRemote() {
    cout << "waiting for other player's move..." << endl;
}

/*****************************************************************************************************
* function name: printMove                                                                           *
* the input: -                                                                                       *
* the output: -                                                                                      *
* the function operation: print the move the second player have been played.                         *
*****************************************************************************************************/
void ConsoleUI::printMove(char symbol, int x, int y) {
    cout << symbol << " played ";
    cout << '(' << x + 1 << ',' << y + 1 << ')';
    cout << endl << endl;
}

/*****************************************************************************************************
* function name: chooseRemoteGameOptions
* the input: -
* the output: returns choice number
* the function operation: print remote options and returns choice
*****************************************************************************************************/
int ConsoleUI::chooseRemoteGameOptions() {
    string gameName;
    cout<< "Choose option:"<<endl;
    cout<< "(1) start a new game"<<endl;
    cout<< "(2) join an existing game"<<endl;
    int x;
    cin>> x;

    while(x < 1 || x > 2) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout<< "Choose option:"<<endl;
        cout<< "(1) start a new game"<<endl;
        cout<< "(2) join an existing game"<<endl;
        cin>> x;
    }
    cin.clear();

    return x;
}

/*****************************************************************************************************
* function name: printString
* the input: -
* the output: -r
* the function operation: prints a given string
*****************************************************************************************************/

void ConsoleUI::printString(string str) {
    cout<<str<<endl;
}

/*****************************************************************************************************
* function name: getString
* the input: -
* the output: -
* the function operation: gets string from console
*****************************************************************************************************/
string ConsoleUI::getString() {
    string str;
    cin>>str;
    return str;
}