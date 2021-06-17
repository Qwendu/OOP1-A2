#include "Game.hpp"

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



Game::Game()
	:	random_(Oop::Random::getInstance())
		,game_field_(random_){
	

};



int Game::start(){
	game_field_.printField();
	return 0;
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

	for(int row_idx = 0; row_idx < HEIGHT; row_idx++){
		for(int hit = 0; hit < 9; hit++){
			for(int col_idx = 0; col_idx < WIDTH; col_idx++){
				tile_ptr_array_.at(row_idx * WIDTH + col_idx)->printLine(hit);
			}
			std::cout << std::endl;
		}
	}
};
