#include "Treasure.hpp"


Treasure::Treasure(int id): id_(id){
	if(id_ >= 0 && id_ < (int)treasure_names_.size()){
		name_ = treasure_names_.at(id_);
	}
};
