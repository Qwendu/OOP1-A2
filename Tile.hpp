#ifndef H_TILES
#define H_TILES 

#include <string>
#include <array>
#include <iostream>

#include "Treasure.hpp"
#include "Player.hpp"

struct Tile{
	enum ROTATION {DEG0 = 0, DEG90, DEG180, DEG270};
	enum TYPE {T = 0, L, I, O, U, X};
	std::array<std::string, 4> representation_;
	TYPE t_;
	ROTATION r_;	
	Treasure* my_treasure_ = nullptr;
	std::array<Player*, 4> players_;	
	Tile(TYPE, ROTATION);
	Tile(TYPE, ROTATION, int);
	Tile();
	std::array<std::string, 4> setRepresentation();
	void printLine(int);
	void rebuildStringTreasure(std::string&);
	void rebuildStringPlayer(std::string&);
	std::string rebuildString(std::string);
};

#endif
