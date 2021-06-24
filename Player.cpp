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


void Player::giveTreasure(Treasure* treasure_to_add_to_vector){
	treasures_.push_back(treasure_to_add_to_vector);	
};
