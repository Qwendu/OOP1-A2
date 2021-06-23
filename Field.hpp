#ifndef H_GAME
#define H_GAME

#include <array>
#include <vector>

#include "Tile.hpp"
#include "qb.hpp"
#include "Random.hpp"
#include "Game.hpp"

struct Field{
	const static inline int WIDTH = 7;
	const static inline int HEIGHT = 7;
	Stacklocator<sizeof(Tile) * (WIDTH * HEIGHT + 1)> field_allocator_;
	std::array<Tile*, (WIDTH * HEIGHT + 1)> tile_ptr_array_ = {};
	Oop::Random& random_;
	Game& game_;
	Field(Oop::Random&, Game& game);

	void initializeDefaultTiles(Blk&);
	void randomTiles(std::vector<Tile* >);
	void printField();
	void setPlayer(Player*);
	bool movePlayerXTimes(Player*, Tile::ROTATION, int);
	Tile* testMove(int, Tile::ROTATION, int);
	Tile* getTileWithPlayer(Player*);
	int getTileIndexWithPlayer(Player*);
	bool isOpenInDirection(int, Tile::ROTATION);

	std::vector<Tile*> createTileVector();
};


#endif