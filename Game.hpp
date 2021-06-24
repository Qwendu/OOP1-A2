#ifndef H_GAME
#define H_GAME

#include <array>
#include <vector>

#include "Tile.hpp"
#include "qb.hpp"
#include "Random.hpp"
#include "Field.hpp"

struct Game{
	enum InputCommand {};
	Stacklocator<sizeof(Player) * 4 + sizeof(Treasure) * 24> game_allocator_;
	Oop::Random& random_;
	Field game_field_;	
	std::array<Player*, 4> players_ = {};
	int number_of_players_ = 4;
	Game();
	int start();
	int loop();
	void createAndSetPlayers();
	void putPlayersOnField();
	void distributeTreasuresToPlayers();
	void printHeader();
	void printFooter();
	void printField();
};



#endif
