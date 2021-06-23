#include "Tile.hpp"

Tile::Tile(): my_treasure_(0){


};



Tile::Tile(TYPE type, ROTATION rotation): t_(type), r_(rotation){
	representation_ = setRepresentation();
	players_ = {nullptr, nullptr, nullptr, nullptr};

};


Tile::Tile(TYPE type, ROTATION rotation, int treasure_id):t_(type), r_(rotation), my_treasure_(new (treasure_allocator_.allocate(sizeof(Treasure)).ptr) Treasure(treasure_id)){
	representation_ = setRepresentation();
	players_ = {nullptr, nullptr, nullptr, nullptr};
};

Tile::Tile(TYPE type, ROTATION rotation, Player* og_player): t_(type), r_(rotation),ogp_(og_player){
	representation_ = setRepresentation();
	players_ = {nullptr, nullptr, nullptr, nullptr};
};

void Tile::printLine(int line_idx){
	std::string line_to_print = representation_.at((size_t)r_).substr(line_idx * 9,  9);
	switch(line_idx){
	case 2:
		if(ogp_ != nullptr) rebuildStringPlayerStart(line_to_print);
		else if(my_treasure_ != nullptr) rebuildStringTreasure(line_to_print);
		break;
	case 3:
		rebuildStringPlayer(line_to_print);
		break;
	case 4:
		rebuildString(line_to_print);
	}
	std::cout << rebuildString(line_to_print) << std::flush;
};

void Tile::rebuildStringTreasure(std::string& line){
	if(!my_treasure_){
		line.replace(3, 3, "   ");
		
	}else{
		line.replace(3,3, my_treasure_->getTreasureString());
	}
};

void Tile::rebuildStringPlayer(std::string& line){
	//count players
	size_t p_count = 0;
	for(auto player : players_){
		if(player != nullptr) p_count++;
	}
	std::string players = " P";
	if(p_count == 4){
		players = "P";
	}
	if(p_count == 0){
		line.replace(2 ,5 , "     ");
		return;
	}
	for(size_t i = 0; i < players_.size(); i++){
		if(players_.at(i))
			players += players_.at(i)->getColorString();
	}
	line.replace(2, players.size(), players);
};

void Tile::rebuildStringPlayerStart(std::string& line){
	if(ogp_ == nullptr) return;
	line.replace(3,3, "(" + ogp_->getColorString() + ")");
};


std::string Tile::rebuildString(std::string line){
	std::string converted_line;
	for(size_t i = 0; i < line.size(); i++){
		if(line.at(i) == '#')
			converted_line += "█";
		else
			converted_line += line.at(i);
	}
	return converted_line;
};

std::array<std::string, 4> Tile::setRepresentation(){
	switch(t_){
		case I:
			return {
			"##     ####     ####     ####     ####     ##"
			,"#########                           #########"
			,"##     ####     ####     ####     ####     ##"
			,"#########                           #########"
			};
		case L:
			return {
			"##     ####       ##       ##       #########"
			,"##     ##       ##       ##       ###########"
			,"#########       ##       ##       ####     ##"
			,"###########       ##       ##       ##     ##"
			};
		case T:
			return {
			"##     ####       ##       ##       ##     ##"
			,"##     ##                           #########"
			,"##     ##       ##       ##       ####     ##"
			,"#########                           ##     ##"
			};
		case X:
			return {
			"##     ####     ####     ####     ####     ##"
			,"#########                           #########"
			,"##     ####     ####     ####     ####     ##"
			,"#########                           #########"
			};
		case O:
			return {
			"##     ####     ####     ####     ####     ##"
			,"#########                           #########"
			,"##     ####     ####     ####     ####     ##"
			,"#########                           #########"
			};
		case U:
			return {
			"##     ####     ####     ####     ####     ##"
			,"#########                           #########"
			,"##     ####     ####     ####     ####     ##"
			,"#########                           #########"
			};
	}
};

bool Tile::hasPlayer(Player* player){
	for(Player* p : players_){
		if(p == player) return true;
	}
	return false;
};


void Tile::addPlayer(Player* player){
	players_.at((size_t)player->c_) = player;
}

void Tile::removePlayer(Player* player){
	players_.at((size_t)player->c_) = nullptr;
}


Tile::ROTATION Tile::flipped(Tile::ROTATION r){
	switch(r){
	case DEG0:
		return DEG180;
	case DEG90:
		return DEG270;
	case DEG180:
		return DEG0;
	case DEG270:
		return DEG90;
	}
};

Tile::ROTATION Tile::rotatedLeft(Tile::ROTATION r, int i){
	int rotation = (int) r;
	for(int iter = 0; iter < i; iter++){
		rotation++;
		if(rotation > 3) rotation = 0;
		if(rotation < 0) rotation = 3;
	}
	return (ROTATION) rotation;
};

Tile::ROTATION Tile::rotatedRight(Tile::ROTATION r, int i){
	int rotation = (int) r;
	for(int iter = 0; iter < i; iter++){
		rotation--;
		if(rotation > 3) rotation = 0;
		if(rotation < 0) rotation = 3;
	}
	return (ROTATION) rotation;
};
