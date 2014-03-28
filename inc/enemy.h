#ifndef ENEMY_H
#define ENEMY_H

#include <vector>
#include "sprite.h"
#include "block.h"

class Enemy : public Sprite{
	public:
		Enemy(float x, float y, int lvl);
		virtual ~Enemy();

		void draw(sf::RenderWindow &window);
		void update(sf::FloatRect playerBounds, const std::vector<Block> &blocks);
		void hit(int dmg);
		int attack();
		bool isAlive();

	protected:
		void createRadar();
		float speed;
		int health;
		int damage;

	private:
		virtual void loadTextureRects();
		void animate();
		void move();
		void checkWallCollision(const std::vector<Block> &blocks);
		void checkPlayerCollision(sf::FloatRect playerBounds);

		float velX, velY;
		bool attacked;
		bool collidedBlock;
		sf::CircleShape radar;
		sf::Clock clock;
		sf::Time animationTimer;
		sf::Time attackedTimer;
};

#endif
