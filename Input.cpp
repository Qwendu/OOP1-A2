#include "Input.hpp"

#include <iostream>
#include "Player.hpp"


namespace Input{

void playerPrompt(Player::COLOR color){
	switch(color){
	case Player::COLOR::RED:
		std::cout << "RED";
		break;
	case Player::COLOR::YELLOW:
		std::cout << "YELLOW";
		break;
	case Player::COLOR::GREEN:
		std::cout << "GREEN";
		break;
	case Player::COLOR::BLUE:
		std::cout << "BLUE";	
	}
	std::cout << " >" << std::flush;
};































}
