#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <vector>
#include "sprite.h"

class Player;
class Inventory;

class Item : public Sprite{
	public:
		Item();
		Item(float posX, float posY);
		virtual ~Item();
	
		void draw(sf::RenderWindow &window);
		void draw(sf::RenderWindow &window, float posX, float posY);
		void update();

		virtual void use(Inventory &inv, Player &player) = 0;
		
		std::string getName() const;

	protected:
		sf::Texture itemTexture;
		sf::Sprite itemSprite;
		std::string name;

	private:
		void loadTextureRects();
		void animate();
		sf::Clock clock;
		sf::Time animationTimer;
};

#endif
