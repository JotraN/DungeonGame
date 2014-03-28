#include "spinbaddie.h"

SpinBaddie::SpinBaddie(float x, float y, int lvl) : Enemy(x, y, lvl){
	loadTexture("images/enemyspritesheet.png");
	health = 2;
	speed = 0.5*lvl;
	damage = 1;
	createRadar();
}

SpinBaddie::~SpinBaddie(){
}

void SpinBaddie::loadTextureRects(){
	animationFrames.push_back(sf::IntRect(0, 0, 50, 50));
	animationFrames.push_back(sf::IntRect(50, 0, 50, 50));
	animationFrames.push_back(sf::IntRect(100, 0, 50, 50));
}
