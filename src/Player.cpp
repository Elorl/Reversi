
#include "Player.h"

using namespace std;
/*****************************************************************************************************
* function name: Player - constructor		    					        	                     *
* the input: board = the player's color,                                                             *
* the output: -                                                                                      *
* the function operation:                                                                            *
*****************************************************************************************************/
Player::Player(Color color): type(color), counter(new Counter()), rivalCounter(NULL){
    if(color == Black) {
        this->symbol = 'X';
    } else if(color == White) {
        this->symbol ='O';
    }
    if(color == Black) {
        rivalColor = White;
    }
    else if(color == White) {
        rivalColor = Black;
    }
}
/*****************************************************************************************************
* function name: Player - default constructor		    					        	             *
* the input: -                                                                                       *
* the output: -                                                                                      *
* the function operation:                                                                            *
*****************************************************************************************************/
Player::Player(): counter(new Counter()), rivalCounter(NULL){
    this->type = Black;
    this->symbol = 'X';
}

/*****************************************************************************************************
* function name: Player - destructor	    					        	             *
* the input: -                                                                                       *
* the output: -                                                                                      *
* the function operation:                                                                            *
*****************************************************************************************************/
Player::~Player() {
    delete counter;
}
/*****************************************************************************************************
* function name: getCount      	    						        	                             *
* the input: -      			                                                                     *
* the output: the function return the amount of disks the player has.                                *
* the function operation: -                                                                          *
*****************************************************************************************************/
int Player::getCount() {
    return counter->get();
}
/*****************************************************************************************************
* function name: getsimbol      	    						        	                         *
* the input: -      			                                                                     *
* the output: the function return the char that represent the player.                                *
* the function operation: -                                                                          *
*****************************************************************************************************/
char Player::getSymbol() {
    return symbol;
}
/*****************************************************************************************************
* function name: increase      	    						            	                         *
* the input: -      			                                                                     *
* the output: the function increase the counter by one.                                              *
* the function operation: -                                                                          *
*****************************************************************************************************/
void Player::increase(int k) {
    this->counter->increase(k);
}
/*****************************************************************************************************
* function name: decrease      	    						            	                         *
* the input: -      			                                                                     *
* the output: the function decrease the counter by one.                                              *
* the function operation: -                                                                          *
*****************************************************************************************************/
void Player::decrease(int k) {
    this->counter->decrease(k);
}

/*****************************************************************************************************
* function name: setCount      	    						            	                         *
* the input: -      			                                                                     *
* the output: -                                              *
* the function operation: setting counter value                                                                         *
*****************************************************************************************************/
void Player::setCount(int count) {
    counter->setCount(count);
}

/*****************************************************************************************************
* function name: setRivalCounter      	    						            	                         *
* the input: -      			                                                                     *
* the output:                                              *
* the function operation: setting rival counter                                                                         *
*****************************************************************************************************/
void Player::setRivalCounter( Counter *rivalCounter) {
    Player::rivalCounter = rivalCounter;
}

/*****************************************************************************************************
* function name: getCount      	    						            	                         *
* the input: -      			                                                                     *
* the output:                                              *
* the function operation: getting counter                                                                        *
*****************************************************************************************************/
 Counter *Player::getCounter()  {
    return counter;
}
/*****************************************************************************************************
* function name: setLogic      	    						            	                         *
* the input: -      			                                                                     *
* the output:                                               *
* the function operation: setting logic                                                                    *
*****************************************************************************************************/
void Player::setLogic(GameLogic *logic) {
    Player::logic = logic;
}
