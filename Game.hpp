#ifndef H_GAME
#define H_GAME

#include <array>
#include <vector>
#include "Tile.hpp"
#include "qb.hpp"
#include "Random.hpp"



struct Field{
	const static inline int WIDTH = 7;
	const static inline int HEIGHT = 7;
	Stacklocator<sizeof(Tile) * (WIDTH * HEIGHT + 1)> field_allocator_;
	std::array<Tile*, (WIDTH * HEIGHT + 1)> tile_ptr_array_ = {};
	Oop::Random& random_;
	Field(Oop::Random&);

	void initializeDefaultTiles(Blk&);
	void randomTiles(std::vector<Tile* >);
	void printField();
	std::vector<Tile*> createTileVector();
};

struct Game{
	enum InputCommand {};
	Stacklocator<sizeof(Player) * 4> game_allocator;
	Oop::Random& random_;
	Field game_field_;	
	std::array<Player, 4> players_ = {};
	Game();
	int start();
};


#endif
