#ifndef H_PLAYER
#define H_PLAYER

#include <vector>
#include "Treasure.hpp"


struct Player{
	enum Color {RED = 0, YELLOW, GREEN, BLUE};
	Color c_;
	std::vector <Treasure *> treasures_;

	Player();
	std::string getColorString();
};









#endif
