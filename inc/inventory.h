#ifndef INVENTORY_H
#define INVENTORY_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "item.h"

class Player;

class Inventory{
	public:
		Inventory();
		~Inventory();

		void draw(sf::RenderWindow &window, Player &player);
		void processEvents(sf::Event &event, Player &player);
		void addItem(Item *item);
		void removeItem(Item *item);
		bool isFull();
		void resetSelectors();

		const std::vector<Item*> getItems() const;

	private:
		sf::Texture texture;
		sf::Sprite invBackground;
		sf::RectangleShape invSelectorBox;
		sf::Font font;

		std::vector<Item*> items;
		int selector;
		bool errorMsgd;
};

#endif
