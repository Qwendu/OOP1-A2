#ifndef H_TILES
#define H_TILES 

#include <string>
#include <array>



struct Tile{
	static enum Rotation {DEG0 = 0, DEG90, DEG180, DEG270};
	static enum TileType {};
	std::array<std::string, 4> representation;


};












#endif
