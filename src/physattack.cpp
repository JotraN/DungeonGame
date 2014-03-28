#include "physattack.h"

PhysicalAttack::PhysicalAttack(sf::Vector2f position, Direction dir, double damage) : Attack(position, dir, damage){
	loadTexture("images/attackspritesheet.png");
	setOffsets(dir);
	sprite.setPosition(position.x+offsetX, position.y+offsetY);
	loadColor();
}

PhysicalAttack::~PhysicalAttack(){
}

void PhysicalAttack::update(sf::Vector2f position){
	if(canAttack){
		animate();
		sprite.setPosition(position.x+offsetX, position.y+offsetY);
	}
}

void PhysicalAttack::attackEnemy(Enemy &enemy){
	if(canAttack)
		if(sprite.getGlobalBounds().intersects(enemy.getGlobalBounds()))
			enemy.hit(damage);
}

void PhysicalAttack::loadTextureRects(){
	animationFrames.push_back(sf::IntRect(0, 0, 75, 50));
	animationFrames.push_back(sf::IntRect(75, 0, 75, 50));
	animationFrames.push_back(sf::IntRect(150, 0, 75, 50));
	animationFrames.push_back(sf::IntRect(225, 0, 75, 50));
	animationFrames.push_back(sf::IntRect(300, 0, 75, 50));
	animationFrames.push_back(sf::IntRect(375, 0, 75, 50));
	animationFrames.push_back(sf::IntRect(450, 0, 75, 50));
}

void PhysicalAttack::animate(){
	if(clock.getElapsedTime().asSeconds() - animationTimer.asSeconds() > 0.02f){
		if(sprite.getTextureRect() == animationFrames[0])
			sprite.setTextureRect(animationFrames[1]);
		else if(sprite.getTextureRect() == animationFrames[1])
			sprite.setTextureRect(animationFrames[2]);
		else if(sprite.getTextureRect() == animationFrames[2])
			sprite.setTextureRect(animationFrames[3]);
		else if(sprite.getTextureRect() == animationFrames[3])
			sprite.setTextureRect(animationFrames[4]);
		else if(sprite.getTextureRect() == animationFrames[4])
			sprite.setTextureRect(animationFrames[5]);
		else if(sprite.getTextureRect() == animationFrames[5])
			sprite.setTextureRect(animationFrames[6]);
		// Stop attack when finished animating attack
		else if(sprite.getTextureRect() == animationFrames[6])
			canAttack = false;
		animationTimer = clock.getElapsedTime();
	}
}

void PhysicalAttack::setOffsets(Direction dir){
	if(dir == SOUTH){
		offsetX = -17;
		offsetY = 20;
	} else if(dir == NORTH){
		offsetX = 57;
		offsetY = 20;
		sprite.rotate(180);
	} else if(dir == WEST){
		offsetX = 22;
		offsetY = -20;
		sprite.rotate(90);
	} else{
		offsetX = 17;
		offsetY = 55;
		sprite.rotate(270);
	}
}

void PhysicalAttack::loadColor(){
	if(damage < 2)
		return;
	else if(damage < 3)
		sprite.setColor(sf::Color(255, 0, 255));
	else
		sprite.setColor(sf::Color(255, 255, 0));
}
