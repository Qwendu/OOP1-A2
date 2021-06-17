#include "Player.hpp"

Player::Player(){



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
