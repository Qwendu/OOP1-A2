#include "Field.hpp"


#include "qb.hpp"
#include "Random.hpp"
#include <iostream>
#include <vector>

Field::Field(Oop::Random& random) 
	:	random_(random){
	Blk mem_block = field_allocator_.allocate(sizeof(Tile) * 16);
	initializeDefaultTiles(mem_block);
	randomTiles(createTileVector());
};

void Field::initializeDefaultTiles(Blk& b){
	Tile* tile_pointer = (Tile*)b.ptr;
	//Starter Tiles for the Players
	tile_ptr_array_.at(0 * WIDTH + 0) = new (tile_pointer++) Tile(Tile::TYPE::L, Tile::ROTATION::DEG270);
	tile_ptr_array_.at(0 * WIDTH + 6) = new (tile_pointer++) Tile(Tile::TYPE::L, Tile::ROTATION::DEG180);
	tile_ptr_array_.at(6 * WIDTH + 0) = new (tile_pointer++) Tile(Tile::TYPE::L, Tile::ROTATION::DEG0);
	tile_ptr_array_.at(6 * WIDTH + 6) = new (tile_pointer++) Tile(Tile::TYPE::L, Tile::ROTATION::DEG90);
	//T Tiles unmoveable
	tile_ptr_array_.at(0 * WIDTH + 2) = new (tile_pointer++) Tile(Tile::TYPE::T, Tile::ROTATION::DEG270, 1);
	tile_ptr_array_.at(0 * WIDTH + 4) = new (tile_pointer++) Tile(Tile::TYPE::T, Tile::ROTATION::DEG270, 2);

	tile_ptr_array_.at(2 * WIDTH + 0) = new (tile_pointer++) Tile(Tile::TYPE::T, Tile::ROTATION::DEG0, 3);
	tile_ptr_array_.at(2 * WIDTH + 2) = new (tile_pointer++) Tile(Tile::TYPE::T, Tile::ROTATION::DEG0, 4);
	tile_ptr_array_.at(2 * WIDTH + 4) = new (tile_pointer++) Tile(Tile::TYPE::T, Tile::ROTATION::DEG270, 5);
	tile_ptr_array_.at(2 * WIDTH + 6) = new (tile_pointer++) Tile(Tile::TYPE::T, Tile::ROTATION::DEG180, 6);

	tile_ptr_array_.at(4 * WIDTH + 0) = new (tile_pointer++) Tile(Tile::TYPE::T, Tile::ROTATION::DEG0, 7);
	tile_ptr_array_.at(4 * WIDTH + 2) = new (tile_pointer++) Tile(Tile::TYPE::T, Tile::ROTATION::DEG90, 8);
	tile_ptr_array_.at(4 * WIDTH + 4) = new (tile_pointer++) Tile(Tile::TYPE::T, Tile::ROTATION::DEG180, 9);
	tile_ptr_array_.at(4 * WIDTH + 6) = new (tile_pointer++) Tile(Tile::TYPE::T, Tile::ROTATION::DEG180, 10);

	tile_ptr_array_.at(6 * WIDTH + 2) = new (tile_pointer++) Tile(Tile::TYPE::T, Tile::ROTATION::DEG90, 11);
	tile_ptr_array_.at(6 * WIDTH + 4) = new (tile_pointer++) Tile(Tile::TYPE::T, Tile::ROTATION::DEG90, 12);
};

void Field::randomTiles(std::vector<Tile*> tile_ptr_vector){
	for(size_t i = 0; i < tile_ptr_array_.size(); i++){
		Tile* ptr = tile_ptr_array_.at(i);
		if(ptr != nullptr) continue;
		int index = random_.getRandomCard(tile_ptr_vector.size()) - 1;
		ptr = tile_ptr_vector.at(index);
		tile_ptr_vector.erase(tile_ptr_vector.begin() + index);
		tile_ptr_vector.shrink_to_fit();
		tile_ptr_array_.at(i) = ptr;
	}

}

std::vector<Tile*> Field::createTileVector(){
	std::vector<Tile*> tile_ptr_vector;
	tile_ptr_vector.reserve(11 + 11 + 12);
	Blk allocation_block = field_allocator_.allocate(sizeof(Tile) * (11 + 11 + 12));
	Tile* ptr = (Tile*)allocation_block.ptr;
	for(int i = 0; i < 11; i ++){
		tile_ptr_vector.push_back(new (ptr++) Tile(Tile::TYPE::L, Tile::ROTATION::DEG0));
	}
	for(int i = 0; i < 11; i++){
		tile_ptr_vector.push_back(new (ptr++) Tile(Tile::TYPE::I, Tile::ROTATION::DEG0));
	}
	for(int i = 0; i < 12; i++){
		tile_ptr_vector.push_back(new (ptr++) Tile(Tile::TYPE::T, Tile::ROTATION::DEG0, 13+ i));
	}
	return tile_ptr_vector;
};

void Field::printField(){
	int row_offset = 2;	
	for(size_t row = 0; row < HEIGHT * 5; row++){
		std::string left_buffer = "    ";
		if(((int)row - row_offset) % 5 == 0) left_buffer.replace(3,1, std::to_string(((int)row - 3) / 5 + 1));
		if(((int)row - (row_offset + 5)) % 10 == 0) left_buffer.replace(0,3, "-->");
		std::cout << left_buffer;
		for(size_t col = 0; col < WIDTH; col++){
			tile_ptr_array_.at((row / 5) * WIDTH + col)->printLine(row % 5);
		}
		if(((int)row - (row_offset + 5)) % 10 == 0) std::cout << "<--";
		std::cout << std::endl;;
	}
};

void Field::setPlayer(Player* player){
	switch(player->c_){
		case Player::COLOR::RED:
			tile_ptr_array_.at(0)->players_.at((size_t)Player::COLOR::RED) = player;
			tile_ptr_array_.at(0)->ogp_ = player;	
			return;
		case Player::COLOR::YELLOW:
			tile_ptr_array_.at(6)->players_.at((size_t)Player::COLOR::YELLOW) = player;
			tile_ptr_array_.at(6)->ogp_ = player;
			return;
		case Player::COLOR::GREEN:
			tile_ptr_array_.at(6 * WIDTH)->players_.at((size_t)Player::COLOR::GREEN) = player;
			tile_ptr_array_.at(6 * WIDTH)->ogp_ = player;
			return;
		case Player::COLOR::BLUE:
			tile_ptr_array_.at(6 * WIDTH + 6)->players_.at((size_t)Player::COLOR::BLUE) = player;
			tile_ptr_array_.at(6 * WIDTH + 6)->ogp_ = player;
			return;
	}
};

bool Field::movePlayerXTimes(Player* player, Tile::ROTATION direction, int X){
	
	Tile* test = testMove(getTileIndexWithPlayer(player), direction, X);	
	if(test == nullptr) return false;
	getTileWithPlayer(player)->removePlayer(player);
	test->addPlayer(player);
	return true; 
};

Tile* Field::testMove(int index, Tile::ROTATION direction, int X){
	X--;
	if(!isOpenInDirection(index, direction)) return nullptr;
	int row = index / 7;
	int col = index % 7;
	switch(direction){
		case Tile::ROTATION::DEG0:
			col += 1;
			break;
		case Tile::ROTATION::DEG90:
			row -= 1;
			break;
		case Tile::ROTATION::DEG180:
			col -= 1;
			break;
		case Tile::ROTATION::DEG270:
			row += 1;
			break;
	}
	if(!(col >= 0 && col < WIDTH && row >= 0 && row < HEIGHT)) return nullptr;
	index = row * WIDTH + col;
	if(!isOpenInDirection(index, Tile::flipped(direction))) return nullptr;
	return testMove(index, direction, X);
};

Tile* Field::getTileWithPlayer(Player* player_to_find){
	for(Tile* tile : tile_ptr_array_){
		if(tile->hasPlayer(player_to_find)) return tile;
	}
	return nullptr;
};

int Field::getTileIndexWithPlayer(Player* player_to_find){
	for(size_t i = 0; i < tile_ptr_array_.size(); i++){
		if(tile_ptr_array_.at(i)->hasPlayer(player_to_find)) return i;
	}
	return -1;
};

bool Field::isOpenInDirection(int tidx, Tile::ROTATION direction){
	Tile* tile = tile_ptr_array_.at(tidx);
	switch(tile->t_){
		case(Tile::TYPE::O): return false;
		case(Tile::TYPE::U): return (direction == tile->r_);
		case(Tile::TYPE::X): return true;
		case(Tile::TYPE::L): return (direction == tile->r_ || Tile::rotatedRight(direction, 1) == tile->r_); 
		case(Tile::TYPE::T): return (direction == tile->r_ || Tile::rotatedLeft(direction, 1) == tile->r_ || Tile::rotatedRight(direction,1) == tile->r_);
		case(Tile::TYPE::I): return (direction % 2 == tile->r_ % 2);
	}
	return false;
};
