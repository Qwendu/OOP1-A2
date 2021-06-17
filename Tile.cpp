#include "Tile.hpp"

Tile::Tile(): my_treasure_(0){


};



Tile::Tile(TYPE type, ROTATION rotation): t_(type), r_(rotation){
	representation_ = setRepresentation();
};


Tile::Tile(TYPE type, ROTATION rotation, int treasure_id):t_(type), r_(rotation), my_treasure_(new Treasure(treasure_id)){
	representation_ = setRepresentation();
};

void Tile::printLine(int line_idx){
	std::string line_to_print = representation_.at((size_t)r_).substr(line_idx * 9, line_idx * 9 + 9);
	switch(line_idx){
	case 2:
		rebuildStringTreasure(line_to_print);
		break;
	case 3:
		rebuildStringPlayer(line_to_print);
		break;
	case 4:
		rebuildString(line_to_print);
	}
	std::cout << line_to_print << std::flush;
};

void Tile::rebuildStringTreasure(std::string& line){
	if(!my_treasure_){
		line.replace(3, 3, "   ");
		
	}else{
		line.replace(3,3, my_treasure_->getTreasureString());
	}
	line = rebuildString(line);
};

void Tile::rebuildStringPlayer(std::string& line){
	std::string players = "P";
	for(size_t i = 0; i < players_.size(); i++){
		if(players_.at(i))
			players += players_.at(i)->getColorString();
	}
	line.replace(2 + 1*(players.size() > 4), players.size(), players);
	line = rebuildString(line);
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
