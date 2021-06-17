#include <iostream>
#include "Player.hpp"
#include "Tile.hpp"
#include "Treasure.hpp"
#include "Game.hpp"

int main(int argc, char* argv[]){
	if(argc != 1)
		return 1;
	argv[0] = *argv;
	Game g;

	return g.start();
}
