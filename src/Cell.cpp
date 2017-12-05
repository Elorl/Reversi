/******************************************
* Student name: Elor Lichtziger
* Student: 308541739
* Exercise name: ex1
******************************************/


#include "../include/Cell.h"
#include <iostream>

using namespace std;

/*****************************************************************************************************
* function name: Cell - constructor			            		        	                         *
* the input:        			                                                                     *
* the output: -                                                                                      *
* the function operation: -                                                                          *
*****************************************************************************************************/
Cell::Cell(int x, int y, Color clr) {
    xCord = x;
    yCord = y;
    color = clr;
}
/*****************************************************************************************************
* function name: Cell - default constructor						        	                         *
* the input:        			                                                                     *
* the output: -                                                                                      *
* the function operation: -                                                                          *
*****************************************************************************************************/
Cell::Cell() {
    this->xCord = 0;
    this->yCord = 0;
    this->setColor(Empty);
}
/*****************************************************************************************************
* function name: getColor               						        	                         *
* the input:        			                                                                     *
* the output: return the cell's color.                                                               *
* the function operation: -                                                                          *
*****************************************************************************************************/
Color Cell::getColor() {
    return color;
}
/*****************************************************************************************************
* function name: getX               						        	                             *
* the input:        			                                                                     *
* the output: return the cell's x cord value.                                                        *
* the function operation: -                                                                          *
*****************************************************************************************************/
int Cell::getX() {
    return xCord;
}
/*****************************************************************************************************
* function name: setX               						        	                             *
* the input: an int.  			                                                                     *
* the output: -                                                                                      *
* the function operation: insert the x value to the x member in the class.                           *
*****************************************************************************************************/
void Cell::setX(int x) {
    this->xCord = x;
}
/*****************************************************************************************************
* function name: getY               						        	                             *
* the input:        			                                                                     *
* the output: return the cell's y cord value.                                                        *
* the function operation: -                                                                          *
*****************************************************************************************************/
int Cell::getY() {
    return yCord;
}
/*****************************************************************************************************
* function name: setY               						        	                             *
* the input: an int.  			                                                                     *
* the output: -                                                                                      *
* the function operation: insert the y value to the y member in the class.                           *
*****************************************************************************************************/
void Cell::setY(int y) {
    this->yCord = y;
}
/*****************************************************************************************************
* function name: setColor             						        	                             *
* the input: a color.  			                                                                     *
* the output: -                                                                                      *
* the function operation: insert the color to the color member in the class.                         *
*****************************************************************************************************/
void Cell::setColor(Color clr) {
    color = clr;
}