#include "stairs.h"
#include "room.h"
#include <iostream>

Stairs::Stairs(int posX, int posY){
	texture = sf::Texture();
	if (!texture.loadFromFile("images/stair.png", sf::IntRect(0, 0, 64, 64))){
	}

	sprite = sf::Sprite();
	sprite.setTexture(texture);
	sprite.setPosition(sf::Vector2f(posX, posY)); 
}

Stairs::~Stairs(){
}

void Stairs::draw(sf::RenderWindow &window){
	sprite.setTexture(texture);
	window.draw(sprite);
}

sf::FloatRect Stairs::getGlobalBounds() const{
	return sprite.getGlobalBounds();
}
