
#ifndef REVERSI_CONSOLEUI_H
#define REVERSI_CONSOLEUI_H

#include "UserInterface.h"

class ConsoleUI :public UserInterface {
public:
    void printBoard(Board& b);
    void printPoints(int bPoints, int wPoints);
    void printOptions(Cell** optionsMatrix, int rows, int cols);
    void requestIndices(bool isFirstTime = true);
    void announceTurnPlayer(Player &player);
    void noPossibleMove();
    void gameOver();
    int choosePlayerType();

};


#endif //REVERSI_CONSOLEUI_H
