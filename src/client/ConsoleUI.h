
#ifndef REVERSI_CONSOLEUI_H
#define REVERSI_CONSOLEUI_H

#include "UserInterface.h"

/**
 *  ConsoleUI.
 */
class ConsoleUI :public UserInterface {
public:
    void printBoard(Board& b);
    void printPoints(int bPoints, int wPoints);
    void printOptions(Cell** optionsMatrix, int rows, int cols);
    void requestIndices(bool isFirstTime = true);
    void announceTurnPlayer(char symbol);
    void noPossibleMove();
    void gameOver();
    int choosePlayerType();
    void waitingMoveRemote();
    void printMove(char symbol, int x, int y);
    int chooseRemoteGameOptions();
    void printString(string str);
    string getString();
    void printGameName(string str);
};


#endif //REVERSI_CONSOLEUI_H
