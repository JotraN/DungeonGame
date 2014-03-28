#ifndef RANGE_ATTACK_H
#define RANGE_ATTACK_H

#include "attack.h"

class RangeAttack : public Attack{
	public:
		RangeAttack(sf::Vector2f position, Direction dir, double damage);
		~RangeAttack();

		void update(sf::Vector2f position);
		void attackEnemy(Enemy &enemy);

	private:
		void loadTextureRects();
		void animate();
		void setOffsets(Direction dir);
		void loadColor();

		int rangeLife;
		float speed;
		Direction atkDir;
};

#endif
