#ifndef PHYS_ATTACK_H
#define PHYS_ATTACK_H

#include "attack.h"

class PhysicalAttack : public Attack{
	public:
		PhysicalAttack(sf::Vector2f position, Direction dir, double damage);
		~PhysicalAttack();

		void update(sf::Vector2f position);
		void attackEnemy(Enemy &enemy);

	private:
		void loadTextureRects();
		void animate();
		void setOffsets(Direction dir);
		void loadColor();
};

#endif
