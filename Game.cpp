#include "Game.hpp"

#include "qb.hpp"
#include "Random.hpp"
#include "Input.hpp"
#include <iostream>
#include <vector>


Game::Game()
	:	random_(Oop::Random::getInstance())
		,game_field_(random_){
	
	players_ = {nullptr, nullptr, nullptr, nullptr};
	//get number of players
	createAndSetPlayers();
	distributeTreasuresToPlayers();
};



int Game::start(){
	return loop();
};

void Game::createAndSetPlayers(){
	Blk player_mem = game_allocator_.allocate(sizeof(Player) * number_of_players_);
	Player* player = (Player*)player_mem.ptr;
	for(int i = 0; i < number_of_players_; i++, player++){
		player = new (player) Player((Player::COLOR) i);
		players_.at(i) = player;
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
	if(red_collected_treasures < 10) std::cout << " ";
	if(total_treasure_count < 10) std::cout << " ";
	std::cout << "  V                 V                 V    Treasure: "<< yellow_collected_treasures << "/"<< total_treasure_count << std::endl;
};

void Game::printFooter(){
	int total_treasure_count = players_.at(0)->treasures_.size();
	int green_collected_treasures = 0;
       	if(number_of_players_ >= 3) green_collected_treasures = players_.at((size_t)Player::COLOR::GREEN)->collected_treasures_;
	int blue_collected_treasures = 0;
       	if(number_of_players_ == 4) blue_collected_treasures = players_.at((size_t)Player::COLOR::BLUE)->collected_treasures_;

	if(number_of_players_ >= 3)	std::cout << "Player Green(G)";
	else std::cout << "               ";
	std::cout << "  Ʌ                 Ʌ                 Ʌ";
	if(number_of_players_ == 4) std::cout << "    Player Blue(B)";
	std::cout << std::endl;
	if(number_of_players_ >= 3) std::cout << "Treasure: " << green_collected_treasures << "/" << total_treasure_count;
	else std::cout << "              ";
	if(green_collected_treasures < 10) std::cout << " ";
	if(total_treasure_count < 10) std::cout << " ";
	std::cout  << "  |                 |                 |";
	if(number_of_players_ == 4) std::cout << "    Treasure: " << blue_collected_treasures << "/" << total_treasure_count;
	std::cout << std::endl;
};

void Game::distributeTreasuresToPlayers(){
	Blk treasure_memory = game_allocator_.allocate(sizeof(Treasure) * 24);
	Treasure* treasure = (Treasure*)treasure_memory.ptr;
	std::vector<Treasure*> treasures_to_give_away;
	for(int i = 0; i < 24; i++, treasure++){
		treasures_to_give_away.push_back(new (treasure) Treasure(i));
	}
	for(int t_id = 0; t_id < 24 / number_of_players_; t_id++){
		for(int i = 0; i < number_of_players_; i++){
			size_t index = random_.getRandomCard(treasures_to_give_away.size()) - 1;
			Treasure* ptr = treasures_to_give_away.at(index);
			players_.at(i)->giveTreasure(ptr);
			treasures_to_give_away.erase(treasures_to_give_away.begin() + index);
		}
	}
};
