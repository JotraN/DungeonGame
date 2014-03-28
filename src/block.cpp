#include "block.h"

Block::Block(float posX, float posY){
	loadTexture("images/block.png");
	sprite.setPosition(posX, posY); 
}

Block::~Block(){
}

void Block::loadTextureRects(){
	animationFrames.push_back(sf::IntRect(0, 0, 64, 64));
}
