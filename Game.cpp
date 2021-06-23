#include "Game.hpp"

#include "qb.hpp"
#include "Random.hpp"
#include <iostream>
#include <vector>


Game::Game()
	:	random_(Oop::Random::getInstance())
		,game_field_(random_, *this){
	
	players_ = {nullptr, nullptr, nullptr, nullptr};
	//get number of players
	
	createAndSetPlayers();
	distributeTreasuresToPlayers();
};



int Game::start(){
	return loop();
};

void Game::createAndSetPlayers(){
	Blk player_mem = game_allocator.allocate(sizeof(Player) * number_of_players);
	Player* player = (Player*)player_mem.ptr;
	for(int i = 0; i < number_of_players; i++, player++){
		player = new (player) Player((Player::COLOR) i);
		game_field_.setPlayer(player);
	}
};

int Game::loop(){
	printField();
	return 0;
};

void Game::printField(){
	//Header
	printHeader();
	//Field
	game_field_.printField();
	//Footer
	printFooter();
};

void Game::printHeader(){
	int total_treasure_count = players_.at(0)->treasures_.size();
	int red_collected_treasures = players_.at((size_t)Player::COLOR::RED)->collected_treasures_;
	int yellow_collected_treasures = players_.at((size_t)Player::COLOR::YELLOW)->collected_treasures_;
	
	std::cout << "Player Red(R)    |                 |                 |    Player Yellow(Y)" << std::endl;
	std::cout << "Treasure: " << red_collected_treasures << "/" << total_treasure_count;
	//Next two lines are for alignment
	if(red_collected_treasures >= 10) std::cout << " ";
	if(total_treasure_count >= 10) std::cout << " ";
	std::cout << "  V                 V                 V    Treasure: "<< yellow_collected_treasures << "/"<< total_treasure_count << std::endl;
};

void Game::printFooter(){
	int total_treasure_count = players_.at(0)->treasures_.size();
	int green_collected_treasures = players_.at((size_t)Player::COLOR::GREEN)->collected_treasures_;
	int blue_collected_treasures = players_.at((size_t)Player::COLOR::BLUE)->collected_treasures_;

	if(players_.at((size_t)Player::COLOR::GREEN) != nullptr)	std::cout << "Player Green(G)";
	else std::cout << "               ";
	std::cout << "  Ʌ                 Ʌ                 Ʌ";
	if(players_.at((size_t)Player::COLOR::BLUE) != nullptr) std::cout << "    Player Blue(B)";
	std::cout << std::endl;
	if((players_.at((size_t)Player::COLOR::GREEN) != nullptr) std::cout << "Treasure: " << green_collected_treasures << "/" << total_treasure_count;
	if(red_collected_treasures >= 10) std::cout << " ";
	if(total_treasure_count >= 10) std::cout << " ";
	std::cout << std::endl << "  |                 |                 |    Treasure: " << blue_collected_treasures << "/" << total_treasure_count << std::endl;
};

void Game::distributeTreasuresToPlayers(){



};
