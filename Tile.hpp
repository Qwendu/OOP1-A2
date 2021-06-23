#ifndef H_TILES
#define H_TILES 

#include <string>
#include <array>
#include <iostream>

#include "qb.hpp"

#include "Treasure.hpp"
#include "Player.hpp"

struct Tile{
	enum ROTATION {DEG0 = 0, DEG90, DEG180, DEG270};
	enum TYPE {T = 0, L, I, O, U, X};
	std::array<std::string, 4> representation_;
	Stacklocator<sizeof(Treasure)> treasure_allocator_;
	TYPE t_;
	ROTATION r_;	
	Treasure* my_treasure_ = nullptr;
	Player* ogp_ = nullptr;
	std::array<Player*, 4> players_;	
	Tile(TYPE, ROTATION);
	Tile(TYPE, ROTATION, int);
	Tile(TYPE, ROTATION, Player*);
	Tile();
	std::array<std::string, 4> setRepresentation();
	void printLine(int);
	void rebuildStringTreasure(std::string&);
	void rebuildStringPlayer(std::string&);
	void rebuildStringPlayerStart(std::string&);
	bool hasPlayer(Player*);
	void addPlayer(Player*);
	void removePlayer(Player*);
	std::string rebuildString(std::string);

	ROTATION static flipped(ROTATION);
	ROTATION static rotatedRight(ROTATION, int);
	ROTATION static rotatedLeft(ROTATION, int);
};

#endif
