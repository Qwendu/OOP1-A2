#ifndef H_INPUT
#define H_INPUT

#include <iostream>


namespace Input{

	int getPlayerCount();
	void playerPrompt(Player::COLOR);
	
	enum PRI_COM {ST, HT, GO, QUIT, ROTATE, INSERT, GAMEFIELD, FINISH};
	enum SEC_COM {RIGHT, UP, LEFT, DOWN, ON, OFF};

	std::map PRI_COM_MAP = {




	};

	struct command{
		PRI_COM pc;
		SEC_COM sc;
		int number;
		std::string pc_str;
		std::string sc_str;
		std::string number_str;
	};


	command getCommand();
}


#endif
