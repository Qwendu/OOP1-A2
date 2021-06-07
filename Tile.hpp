#ifndef H_TILES
#define H_TILES 

#include <string>
#include <array>

#include "Treasure.hpp"
#include "Player.hpp"

struct Tile{
	enum ROTATION {DEG0 = 0, DEG90, DEG180, DEG270};
	enum TYPE {T = 0, L, I, O, U, X};
	std::array<std::string, 4> representation_;
	Treasure my_treasure_;
	TYPE t_;
	ROTATION r_;	
	std::array<Player, 4> players_;
	
	Tile();

};

#endif
