#include "item.h"

Item::Item(){
}

Item::Item(float posX, float posY){
	loadTexture("images/itemspritesheet.png");
	sprite.setPosition(posX, posY);

	animationTimer = clock.getElapsedTime();
}

Item::~Item(){
}

void Item::loadTextureRects(){
	animationFrames.push_back(sf::IntRect(0, 0, 32, 32));
	animationFrames.push_back(sf::IntRect(32, 0, 32, 32));
	animationFrames.push_back(sf::IntRect(64, 0, 32, 32));
}

// Draw bag sprite seen in rooms
void Item::draw(sf::RenderWindow &window){
	window.draw(sprite);
}

// Draw each item's sprite in inventory
void Item::draw(sf::RenderWindow &window, float posX, float posY){
	itemSprite.setPosition(posX, posY);
	// Prevent white square problem
	itemSprite.setTexture(itemTexture);
	window.draw(itemSprite);
}

void Item::update(){
	animate();
}

void Item::animate(){
	if(clock.getElapsedTime().asSeconds() - animationTimer.asSeconds() > 0.25f){
		if(sprite.getTextureRect() == animationFrames[0])
			sprite.setTextureRect(animationFrames[1]);
		else if(sprite.getTextureRect() == animationFrames[1])
			sprite.setTextureRect(animationFrames[2]);
		else if(sprite.getTextureRect() == animationFrames[2])
			sprite.setTextureRect(animationFrames[0]);
		animationTimer = clock.getElapsedTime();
	}
}

std::string Item::getName() const{
	return name;
}
