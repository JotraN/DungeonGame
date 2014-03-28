#include "rangeattack.h"

RangeAttack::RangeAttack(sf::Vector2f position, Direction dir, double damage) : Attack(position, dir, damage){
	loadTexture("images/magicspritesheet.png");
	setOffsets(dir);
	sprite.setPosition(position.x+offsetX, position.y+offsetY);
	
	rangeLife = 0;
	speed = 3;
	atkDir = dir;
}

RangeAttack::~RangeAttack(){
}

void RangeAttack::update(sf::Vector2f position){
	if(canAttack){
		animate();
		if(atkDir == SOUTH)
			sprite.move(0, speed);
		else if(atkDir == NORTH)
			sprite.move(0, -speed);
		else if(atkDir == EAST)
			sprite.move(speed, 0);
		else
			sprite.move(-speed, 0);
	}
}

void RangeAttack::attackEnemy(Enemy &enemy){
	if(canAttack)
		if(sprite.getGlobalBounds().intersects(enemy.getGlobalBounds())){
			enemy.hit(damage);
			canAttack = false;
		}
}

void RangeAttack::loadTextureRects(){
	animationFrames.push_back(sf::IntRect(0, 0, 54, 54));
	animationFrames.push_back(sf::IntRect(54, 0, 54, 54));
	animationFrames.push_back(sf::IntRect(108, 0, 54, 54));
	animationFrames.push_back(sf::IntRect(162, 0, 54, 54));
	animationFrames.push_back(sf::IntRect(216, 0, 54, 54));
	animationFrames.push_back(sf::IntRect(270, 0, 54, 54));
}

void RangeAttack::animate(){
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
		else if(sprite.getTextureRect() == animationFrames[5]){
			 if(rangeLife == 10)
				canAttack = false;
			sprite.setTextureRect(animationFrames[3]);
			rangeLife++;
		}
		animationTimer = clock.getElapsedTime();
	}
}

void RangeAttack::setOffsets(Direction dir){
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

void RangeAttack::loadColor(){
	if(damage < 2)
		return;
	else if(damage < 3)
		sprite.setColor(sf::Color(255, 0, 255));
	else
		sprite.setColor(sf::Color(255, 255, 0));
}
