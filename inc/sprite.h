#ifndef SPRITE_H
#define SPRITE_H

#include <SFML/Graphics.hpp>

class Sprite{
	public:
		Sprite();
		virtual ~Sprite();

		virtual void draw(sf::RenderWindow &window);
		virtual sf::FloatRect getGlobalBounds() const;

	protected:
		sf::Texture texture;
		sf::Sprite sprite;
		std::vector<sf::IntRect> animationFrames;
		void loadTexture(std::string textureLocation);

	private:
		virtual void loadTextureRects() = 0;
};

#endif
