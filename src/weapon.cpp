#include "weapon.h"
#include "player.h"
#include "inventory.h"

Weapon::Weapon(){
	if(!itemTexture.loadFromFile("images/weapon.png", sf::IntRect(0, 0, 70, 70))){
	}
	generateLevel();
	generateName();	
	name += " sword";
	loadColor();
}

Weapon::Weapon(int x, int y) : Item(x, y){
	if(!itemTexture.loadFromFile("images/weapon.png", sf::IntRect(0, 0, 70, 70))){
	}
	generateLevel();
	generateName();	
	name += " sword";
	loadColor();
}

Weapon::Weapon(std::string wepName, int lvl){
	if(!itemTexture.loadFromFile("images/weapon.png", sf::IntRect(0, 0, 70, 70))){
	}
	name = wepName;
	level = lvl;
	loadColor();
}

Weapon::~Weapon(){
}

void Weapon::loadColor(){
	switch(level){
		case 1:
			break;
		case 2:
			itemSprite.setColor(sf::Color(255, 0, 255, 50));
			break;
		case 3:
			itemSprite.setColor(sf::Color(255, 255, 0, 50));
			break;
	}
}

void Weapon::use(Inventory &inv, Player &player){
	player.setEquippedWeapon(Weapon(getName(), level));
}

double Weapon::getDamage(){
	damage = level*1.25;
	return damage;
}

int Weapon::getLevel() const{
	return level;
}

void Weapon::generateLevel(){
	level = rand() % 3 + 1;
}

void Weapon::generateName(){
	const std::string adj0[] = {"angry", "bewildered", "clumsy", "defeated", "embarrassed"};
	const std::string adj1[] = {"agreeable", "brave", "calm", "delightful", "eager"};
	const std::string adj2[] = {"adorable", "beautiful", "clean", "drab", "elegant"};
	switch(level){
		case 1:
			name = adj0[rand() % sizeof(adj0)/sizeof(adj0[0])];
			break;
		case 2:
			name = adj1[rand() % sizeof(adj1)/sizeof(adj1[0])];
			break;
		case 3:
			name = adj2[rand() % sizeof(adj2)/sizeof(adj2[0])];
			break;
	}
}
