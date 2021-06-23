#include "Player.hpp"


#include <iostream>
Player::Player(COLOR c): c_(c){


};


std::string Player::getColorString(){
	switch(c_){
		case(RED):
			return "R";
		case(YELLOW):
			return "Y";
		case(GREEN):
			return "G";
		case(BLUE):
			return "B";

	}
};

void Player::collectTreasure(){
	collected_treasures_++;
};
