#include "enemy.h"

Enemy::Enemy(float posX, float posY, int lvl) :
	velX(0), velY(0), attacked(false), health(1), damage(1){
	sprite.setPosition(posX, posY);

	animationTimer = clock.getElapsedTime();
	collidedBlock = false;
	speed = 0.5*lvl;
}

Enemy::~Enemy(){
}

void Enemy::loadTextureRects(){
}

void Enemy::draw(sf::RenderWindow &window){
	if(isAlive()){
		sprite.setTexture(texture);
		window.draw(sprite);
	}
}

void Enemy::update(sf::FloatRect playerBounds, const std::vector<Block> &blocks){
	if(isAlive()){
		animate();
		if(!attacked){
			move();
			checkWallCollision(blocks);
			if(!collidedBlock)
				checkPlayerCollision(playerBounds);
		// After 0.5f seconds, set color back to normal after being attacked
		} else if(clock.getElapsedTime().asSeconds() - attackedTimer.asSeconds() > 0.5f){
			attacked = false;
			sprite.setColor(sf::Color(255, 255, 255));
		}
	}
}

void Enemy::animate(){
	if(clock.getElapsedTime().asSeconds() - animationTimer.asSeconds() > 0.05f){
		if(sprite.getTextureRect() == animationFrames[0])
			sprite.setTextureRect(animationFrames[1]);
		else if(sprite.getTextureRect() == animationFrames[1])
			sprite.setTextureRect(animationFrames[2]);
		else if(sprite.getTextureRect() == animationFrames[2])
			sprite.setTextureRect(animationFrames[0]);
		animationTimer = clock.getElapsedTime();
	}
}

void Enemy::move(){
	radar.move(velX, velY);
	sprite.move(velX, velY);
}

void Enemy::checkWallCollision(const std::vector<Block> &blocks){
	for(int i = 0; i < blocks.size(); i++){
		collidedBlock = false;
		if(sprite.getGlobalBounds().intersects(blocks[i].getGlobalBounds())){
			velY *= -1;
			velX *= -1;
			collidedBlock = true;
			break;
		}
	}
}

void Enemy::checkPlayerCollision(sf::FloatRect playerBounds){
	// Follow player
	if(radar.getGlobalBounds().intersects(playerBounds)){
		// Don't move through player
		if(sprite.getGlobalBounds().intersects(playerBounds) && !attacked){
			velX = -velX;
			velY = -velY;
			attacked = true;
		} else{
			// Check left and right radar collisions and move accordingly
			if(sprite.getGlobalBounds().left - playerBounds.left < 0)
				velX = speed;
			else
				velX = -speed;
			// Check up and down radar collisions
			if(sprite.getGlobalBounds().top - playerBounds.top < 0)
				velY = speed;
			else
				velY = -speed;
			attacked = false;
		}
	}
}

void Enemy::hit(int dmg){
	// if not already attacked by player
	if(!attacked){
		attackedTimer = clock.getElapsedTime();
		health -= dmg;
		attacked = true;
		sprite.setColor(sf::Color::Red);
	}
}

bool Enemy::isAlive(){
	return health > 0;
}

int Enemy::attack(){
	return damage;
}

void Enemy::createRadar(){
	// Seven times as big as sprite
	float radarSize = 7*sprite.getGlobalBounds().width;
	radar = sf::CircleShape(radarSize);
	// Move radar to set sprite as the center
	radar.setPosition(sf::Vector2f(sprite.getPosition().x-radarSize, 
				sprite.getPosition().y-radarSize));
}
