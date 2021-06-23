#include "Treasure.hpp"


Treasure::Treasure(int id): id_(id){
	if(id_ >= 0 && id_ < (int)treasure_names_.size()){
		name_ = treasure_names_.at(id_);
	}
};


std::string Treasure::getTreasureString(){
	std::string treasure_string = "T";
	if(id_ < 10) treasure_string += "0";
	return treasure_string + std::to_string(id_);
};
