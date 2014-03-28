#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "states.h"

class Menu{
	public:
		Menu();
		~Menu();

		void draw(sf::RenderWindow &window);
		void processEvents(sf::Event &event, State &currentState);

	private:
		void loadScores();
		sf::Font font;
		std::vector<std::string> menuItems;
		std::vector<std::string> scores;
		// Keeps track of menu selection
		int selector;
};

#endif
