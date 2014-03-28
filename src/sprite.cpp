#include "sprite.h"

Sprite::Sprite(){
}

Sprite::~Sprite(){
}

void Sprite::draw(sf::RenderWindow &window){
	// Avoid any white rectangle problems with SFML
	sprite.setTexture(texture);
	window.draw(sprite);
}

void Sprite::loadTexture(std::string textureLocation){
	if(!texture.loadFromFile(textureLocation)){
		// TODO handle texture error
	}
	sprite.setTexture(texture);
	loadTextureRects();
	sprite.setTextureRect(animationFrames[0]);
}

sf::FloatRect Sprite::getGlobalBounds() const{
	return sprite.getGlobalBounds();
}
