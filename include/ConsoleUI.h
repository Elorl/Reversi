//Avner Merhavi 203090436

// 29/11/17.
//

#ifndef EX1_CONSOLEUI_H
#define EX1_CONSOLEUI_H

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
    char choosePlayerType();

};


#endif //EX1_CONSOLEUI_H
