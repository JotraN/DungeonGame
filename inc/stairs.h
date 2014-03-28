#ifndef STAIRS_H
#define STAIRS_H

#include <SFML/Graphics.hpp>

class Room;

class Stairs{
	public:
		Stairs(int posX, int posY);
		~Stairs();

		void draw(sf::RenderWindow &window);
		sf::FloatRect getGlobalBounds() const;

	private:
		sf::Sprite sprite;
		sf::Texture texture;
};

#endif
