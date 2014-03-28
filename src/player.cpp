#include "player.h"
#include "physattack.h"
#include "rangeattack.h"
#include <sstream>

Player::Player() : speed(4), velX(0), velY(0), health(5), maxHealth(5), 
	sprint(10), walkSpeed(4), stamina(10), maxStamina(10), atkDmg(1){
	loadTexture("images/playerspritesheet.png");
	loadSoundFiles();

	if(!screenDimText.loadFromFile("images/overlay.png")){
	}
	screenDim.setTexture(screenDimText);

	sprite.setPosition(150, 150);
	playerDir = SOUTH;

	collidedEnemy = false;
	collidedWall = false;

	attack = NULL;
	attacked = false;

	aniTime = clock.getElapsedTime();
	sprintTime = clock.getElapsedTime();

	inventoryOpened = false;
	// Create default weapon
	weapon = new Weapon("first sword", 1);
	inventory.addItem(weapon);

	healthBar.setFillColor(sf::Color::Red);
	healthBar.setPosition(5, 10);
	staminaBar.setFillColor(sf::Color::Green);
	staminaBar.setPosition(5, 20);
}

Player::~Player(){
}

void Player::loadTextureRects(){
	// Down sprites
	animationFrames.push_back(sf::IntRect(0, 0, 38, 50));
	animationFrames.push_back(sf::IntRect(38, 0, 38, 50));
	animationFrames.push_back(sf::IntRect(38*2, 0, 38, 50));
	// Right sprites
	animationFrames.push_back(sf::IntRect(0, 50, 38, 50));
	animationFrames.push_back(sf::IntRect(38, 50, 38, 50));
	animationFrames.push_back(sf::IntRect(38*2, 50, 38, 50));
	// Left sprites
	animationFrames.push_back(sf::IntRect(0, 100, 38, 50));
	animationFrames.push_back(sf::IntRect(38, 100, 38, 50));
	animationFrames.push_back(sf::IntRect(38*2, 100, 38, 50));
	// Up sprites
	animationFrames.push_back(sf::IntRect(0, 150, 38, 50));
	animationFrames.push_back(sf::IntRect(38, 150, 38, 50));
	animationFrames.push_back(sf::IntRect(38*2, 150, 38, 50));
}

void Player::loadSoundFiles(){
	if (!atkBuffer.loadFromFile("sounds/atksound.wav")){
	}
	atkSound.setBuffer(atkBuffer);
	if (!hitBuffer.loadFromFile("sounds/hurt.wav")){
	}
	hitSound.setBuffer(hitBuffer);
	if (!pickBuffer.loadFromFile("sounds/pickup.wav")){
	}
	pickSound.setBuffer(pickBuffer);
	if (!stairsBuffer.loadFromFile("sounds/stairs.wav")){
	}
	stairsSound.setBuffer(stairsBuffer);
}

void Player::processEvents(sf::Event &event){
	processInventoryEvent(event);
	if(inventoryOpened)
		inventory.processEvents(event, *this);
	else{
		processAttackEvent();

		// Prevent player from trying to walk through walls
		if(!collidedWall){
			processSprintEvent();
			processMoveEvent();
		}
	}
}

void Player::processInventoryEvent(sf::Event &event){
	// Check event rather than isKeyPressed
	// because events are polled
	if(event.type == sf::Event::KeyPressed){
		if(event.key.code == sf::Keyboard::I){
			// Stop player if moving
			velX = 0;
			velY = 0;
			inventory.resetSelectors();
			if(inventoryOpened)
				inventoryOpened = false;
			else
				inventoryOpened = true;
		}
	}
}

void Player::processAttackEvent(){
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
		// One attack for one key press
		if(!attacked && stamina != 0){
			atkSound.play();
			attacked = true;
			delete attack;
			attack = new PhysicalAttack(sprite.getPosition(), playerDir, atkDmg);
	//		attack = new RangeAttack(sprite.getPosition(), playerDir, atkDmg);
			stamina -= 1;
		}
	} else
		attacked = false;
}

void Player::processSprintEvent(){
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
		if(stamina != 0){
			// Decrease stamina each 0.5f sec sprinting
			if(clock.getElapsedTime().asSeconds() - sprintTime.asSeconds() > 0.5f){
				stamina -= 1;
				sprintTime = clock.getElapsedTime();
			}
			speed = sprint;
		} else
			speed = walkSpeed;
	} else
		speed = walkSpeed;
}

void Player::processMoveEvent(){
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		velX = -speed;
		if(sprite.getTextureRect() != animationFrames[8])
			sprite.setTextureRect(animationFrames[7]);
		playerDir = WEST;
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		velX = speed;
		if(sprite.getTextureRect() != animationFrames[5])
			sprite.setTextureRect(animationFrames[4]);
		playerDir = EAST;
	} else
		velX = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
		velY = -speed;
		if(sprite.getTextureRect() != animationFrames[11])
			sprite.setTextureRect(animationFrames[10]);
		playerDir = NORTH;
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
		velY = speed;
		if(sprite.getTextureRect() != animationFrames[2])
			sprite.setTextureRect(animationFrames[1]);
		playerDir = SOUTH;
	} else
		velY = 0;
}

void Player::draw(sf::RenderWindow &window){
	// Needed to prevent white square bug when game restarted
	sprite.setTexture(texture);
	// Draw attack under player
	if(playerDir == NORTH){
		if(attack != NULL)
			attack->draw(window);
		window.draw(sprite);
	} else{
		window.draw(sprite);
		if(attack != NULL)
			attack->draw(window);
	}
}

void Player::drawStats(sf::RenderWindow &window){
	window.setView(window.getDefaultView());
	screenDim.setTexture(screenDimText);
	window.draw(screenDim);
	if(inventoryOpened)
		inventory.draw(window, *this);

	if(health != 0)
		healthBar.setSize(sf::Vector2f(20*health, 10));
	else
		healthBar.setSize(sf::Vector2f(1, 10));
	if(stamina != 0)
		staminaBar.setSize(sf::Vector2f(10*stamina, 10));
	else
		staminaBar.setSize(sf::Vector2f(1, 10));
	window.draw(healthBar);
	window.draw(staminaBar);
}

void Player::update(Room &room){
	if(!inventoryOpened){
		regenStamina();
		animate();
		sprite.move(velX, velY);

		if(attack != NULL)
			attack->update(sprite.getPosition());

		checkEnemyCollision(room);
		checkWallCollision(room);
		checkItemCollision(room);
		checkStairsCollision(room);
	}
}

void Player::animate(){		
	// If not moving
	if(velX == 0 && velY == 0){
		switch(playerDir){
			case NORTH:
				sprite.setTextureRect(animationFrames[9]);
				break;
			case SOUTH:
				sprite.setTextureRect(animationFrames[0]);
				break;
			case WEST:
				sprite.setTextureRect(animationFrames[6]);
				break;
			case EAST:
				sprite.setTextureRect(animationFrames[3]);
				break;
			default:
				sprite.setTextureRect(animationFrames[0]);
				break;
		}
	} 
	if(clock.getElapsedTime().asSeconds() - aniTime.asSeconds() > 0.1f){
		if(collidedEnemy){
			if(sprite.getColor() == sf::Color(255, 255, 255))
				sprite.setColor(sf::Color(255, 0, 255));
			else
				sprite.setColor(sf::Color(255, 255, 255));
		}else
			sprite.setColor(sf::Color(255, 255, 255));
		if(playerDir == SOUTH){
			if(sprite.getTextureRect() == animationFrames[1])
				sprite.setTextureRect(animationFrames[2]);
			else if(sprite.getTextureRect() == animationFrames[2])
				sprite.setTextureRect(animationFrames[1]);
		} else if(playerDir == EAST){
			if(sprite.getTextureRect() == animationFrames[4])
				sprite.setTextureRect(animationFrames[5]);
			else if(sprite.getTextureRect() == animationFrames[5])
				sprite.setTextureRect(animationFrames[4]);
		} else if(playerDir == WEST){
			if(sprite.getTextureRect() == animationFrames[7])
				sprite.setTextureRect(animationFrames[8]);
			else if(sprite.getTextureRect() == animationFrames[8])
				sprite.setTextureRect(animationFrames[7]);
		} else{
			if(sprite.getTextureRect() == animationFrames[10])
				sprite.setTextureRect(animationFrames[11]);
			else if(sprite.getTextureRect() == animationFrames[11])
				sprite.setTextureRect(animationFrames[10]);
		}
		aniTime = clock.getElapsedTime();
	}
}

void Player::regenStamina(){
	if(stamina < maxStamina && speed == walkSpeed){
		if(clock.getElapsedTime().asSeconds() - sprintTime.asSeconds() > 2.0f){
			stamina += 1;
			sprintTime = clock.getElapsedTime();
		}
	}
}

void Player::checkEnemyCollision(Room &room){
	// Player invulnerable for 1.0f after enemy attack
	if(collidedEnemy)
		if(clock.getElapsedTime().asSeconds() - invTime.asSeconds() > 1)
			collidedEnemy = false;

	for(int i = 0; i < room.getEnemies().size(); i++){
		if(attack != NULL)
			attack->attackEnemy(room.getEnemies()[i]);
		if(room.getEnemies()[i].isAlive()){
			room.getEnemies()[i].update(sprite.getGlobalBounds(), room.getBlocks());
			if(sprite.getGlobalBounds().intersects(room.getEnemies()[i].getGlobalBounds())){
				if(!collidedEnemy){
					hitSound.play();
					invTime = clock.getElapsedTime();
					health -= room.getEnemies()[i].attack();
				}
				// (Attempt to) Prevent player from running through enemies
				if(velX != 0 || velY != 0){
					velX = -velX;
					velY = -velY;
				}
				collidedEnemy = true;
				break;
			}
		}
	}
}

void Player::checkWallCollision(Room &room){
	// Prevent player from moving automatically after bouncing off wall
	if(collidedWall){
		velX = 0;
		velY = 0;
	}

	for(int i = 0; i < room.getBlocks().size(); i++){
		if(sprite.getGlobalBounds().intersects(room.getBlocks()[i].getGlobalBounds())){
			velX = -velX;
			velY = -velY;
			collidedWall = true;
			break;
		}
		else
			collidedWall = false;
	}
}

void Player::checkItemCollision(Room &room){
	for(int i = 0; i < room.getItems().size(); i++){
		room.getItems()[i]->update();
		if(sprite.getGlobalBounds().intersects(room.getItems()[i]->getGlobalBounds())){
			// Add item and remove it from the room if inventory space available
			if(!inventory.isFull()){
				pickSound.play();
				inventory.addItem(room.getItems()[i]);
				room.getItems().erase(room.getItems().begin() + i);
			}
			break;
		}
	}
}

void Player::checkStairsCollision(Room &room){
	for(int i = 0; i < room.getStairs().size(); i++){
		if(sprite.getGlobalBounds().intersects(room.getStairs()[i].getGlobalBounds())){
			stairsSound.play();
			room.clearRooms();
			room.generateRooms();
			sprite.setPosition(150, 150);
			break;
		}
	}
}

void Player::applyHealth(int amt){
	health += amt;
	if(health > maxHealth)
		health = maxHealth;
}

void Player::applyStamina(int amt){
	stamina += amt;
	if(stamina > maxStamina)
		stamina = maxStamina;
}

bool Player::isDead(){
	return health <= 0;
}

void Player::setEquippedWeapon(Weapon newWeapon){
	weapon = new Weapon(newWeapon.getName(), newWeapon.getLevel());
	atkDmg  = weapon->getDamage();
}

Weapon Player::getEquippedWeapon(){
	return *weapon;
}

sf::Vector2f Player::getPosition() const{
	return sprite.getPosition();
}
