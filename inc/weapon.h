#ifndef WEAPON_H
#define WEAPON_H

#include "item.h"

class Weapon : public Item{
	public:
		Weapon();
		Weapon(int x, int y);
		Weapon(std::string wepName, int lvl);
		~Weapon();

		void use(Inventory &inv, Player &player);

		double getDamage();
		int getLevel() const;

	private:
		void generateName();
		void generateLevel();
		void loadColor();
		double damage;
		int level;
};

#endif
