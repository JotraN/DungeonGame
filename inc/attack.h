#ifndef ATTACK_H
#define ATTACK_H

#include <SFML/System.hpp>
#include "sprite.h"
#include "enemy.h"
#include "directions.h"

class Attack : public Sprite{
	public:
		Attack(sf::Vector2f position, Direction dir, double damage);
		virtual ~Attack();

		void draw(sf::RenderWindow &window);
		virtual void update(sf::Vector2f position) = 0;
		virtual void attackEnemy(Enemy &enemy) = 0;

	protected:
		double damage;
		bool canAttack;
		float offsetX;
		float offsetY;
		sf::Clock clock;
		sf::Time animationTimer;

	private:
		virtual void loadTextureRects() = 0;
		virtual void animate() = 0;
		// Rotate and adjust attack according to player's position,
		virtual void setOffsets(Direction dir) = 0;
		virtual void loadColor() = 0;
};

#endif
