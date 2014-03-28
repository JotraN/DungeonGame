#include "attack.h"

Attack::Attack(sf::Vector2f position, Direction dir, double damage) :
	offsetX(0), offsetY(0){
	// Start animation frame timer
	animationTimer = clock.getElapsedTime();
	canAttack = true;
	this->damage = damage;
}

Attack::~Attack(){
}

void Attack::draw(sf::RenderWindow &window){
	if(canAttack)
		window.draw(sprite);
}
