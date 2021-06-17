#ifndef H_TREASURE
#define H_TREASURE

#include <string>
#include <array>

struct Treasure{
	constexpr static std::array<const char*, 24> treasure_names_ = {
		"Totenkopf"
			,"Schwert"
			,"Goldsack"
			,"Schlüsselbund"
			,"Sombrero"
			,"Ritterhelm"
			,"Buch"
			,"Krone"
			,"Schatztruhe"
			,"Kerzenleuchte"
			,"Schatzkarte"
			,"Goldring"
			,"Eule"
			,"Hofnarr"
			,"Eidechse"
			,"Käfer"
			,"Flaschengeist"
			,"Kobold"
			,"Schlange"
			,"Geist"
			,"Fledermaus"
			,"Spinne"
			,"Ratte"
			,"Motte"
	};
	std::string name_;
	int id_ = -1;
	bool found_ = false;
	
	Treasure(int id);

	std::string getTreasureString();

};










#endif
