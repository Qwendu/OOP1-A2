#ifndef H_PLAYER
#define H_PLAYER

#include <vector>
#include "Treasure.hpp"


struct Player{
	enum COLOR {RED = 0, YELLOW, GREEN, BLUE};
	COLOR c_;
	int collected_treasures_ = 0;
	std::vector <Treasure *> treasures_;

	Player(COLOR);
	std::string getColorString();

	void collectTreasure();
	void giveTreasure(Treasure*);
};









#endif
