#ifndef POTION_H
#define POTION_H

#include "item.h"

class Potion : public Item{
	public:
		Potion();
		Potion(int x, int y);
		~Potion();

		void use(Inventory &inv, Player &player);
		
	private:
		void generatePotion();
		enum Type{
			HEALTH,
			STAMINA
		};
		Type type;
};

#endif
