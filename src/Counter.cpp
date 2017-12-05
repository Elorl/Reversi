/******************************************
* Student name: Elor Lichtziger
* Student: 308541739
* Exercise name: ex1
******************************************/


#include "../include/Counter.h"
#include <iostream>

using namespace std;

/*****************************************************************************************************
* function name: Counter - constructor							        	                         *
* the input:        			                                                                     *
* the output: -                                                                                      *
* the function operation: -                                                                          *
*****************************************************************************************************/
Counter::Counter() {
    this->count = 2;
}
/*****************************************************************************************************
* function name: increase							                       	                         *
* the input: an int number to add to the counter.                                                    *
* the output: -                                                                                      *
* the function operation: increase the counter by the number.                                        *
*****************************************************************************************************/
void Counter::increase(int number) {
    this->count += number;
}
/*****************************************************************************************************
* function name: decrease							                       	                         *
* the input: an int number to decrease from the counter.                                             *
* the output: -                                                                                      *
* the function operation: decrease the counter by the number.                                        *
*****************************************************************************************************/
void Counter::decrease(int number) {
    this->count -= number;
    if(this->count < 0) {
        this->count = 0;
    }
}
/*****************************************************************************************************
* function name: get							                          	                         *
* the input: -                                                                                       *
* the output: the value of the counter.                                                              *
* the function -                                                                                     *
*****************************************************************************************************/
int Counter::get() {
    return this->count;
}

void Counter::setCount(int count) {
    Counter::count = count;
}
