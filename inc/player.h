#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Audio.hpp>
#include "sprite.h"
#include "directions.h"
#include "inventory.h"
#include "room.h"
#include "attack.h"
#include "weapon.h"

class Player : public Sprite{
	public:
		Player();
		~Player();

		void processEvents(sf::Event &event);
		void draw(sf::RenderWindow &window);
		void update(Room &room);
		void drawStats(sf::RenderWindow &window);

		Weapon getEquippedWeapon();
		void setEquippedWeapon(Weapon newWeapon);
		void applyHealth(int amt);
		void applyStamina(int amt);

		void loadSoundFiles();
		sf::Vector2f getPosition() const;
		bool isDead();

	private:
		void loadTextureRects();
		void animate();
		void processInventoryEvent(sf::Event &event);
		void processAttackEvent();
		void processSprintEvent();
		void processMoveEvent();
		void regenStamina();
		void checkEnemyCollision(Room &room);
		void checkWallCollision(Room &room);
		void checkItemCollision(Room &room);
		void checkStairsCollision(Room &room);

		float velX, velY;
		float speed, sprint, walkSpeed;
		float stamina, maxStamina;
		int health, maxHealth;
		double atkDmg;
		bool collidedEnemy;
		bool collidedWall;
		bool attacked;
		bool inventoryOpened;

		sf::SoundBuffer atkBuffer;
		sf::Sound atkSound;
		sf::SoundBuffer hitBuffer;
		sf::Sound hitSound;
		sf::SoundBuffer pickBuffer;
		sf::Sound pickSound;
		sf::SoundBuffer stairsBuffer;
		sf::Sound stairsSound;

		sf::Clock clock;
		// Timers
		sf::Time invTime;
		sf::Time sprintTime;
		sf::Time aniTime;

		Direction playerDir;

		sf::RectangleShape healthBar;
		sf::RectangleShape staminaBar;
		sf::Texture screenDimText;
		sf::Sprite screenDim;

		// Needs to be pointer since Attack is an abstract type
		Attack *attack;
		Weapon *weapon;

		Inventory inventory;
};

#endif
