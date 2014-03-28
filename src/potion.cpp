#include "potion.h"
#include "player.h"
#include "inventory.h"

Potion::Potion(){
	if(!itemTexture.loadFromFile("images/potion.png", sf::IntRect(0, 0, 70, 70))){
	}
	generatePotion();
}

Potion::Potion(int x, int y) : Item(x, y){
	if(!itemTexture.loadFromFile("images/potion.png", sf::IntRect(0, 0, 70, 70))){
	}
	generatePotion();
}

Potion::~Potion(){
}

void Potion::use(Inventory &inv, Player &player){
	inv.removeItem(this);
	if(type == HEALTH)
		player.applyHealth(3);
	else
		player.applyStamina(3);
}

void Potion::generatePotion(){
	if(rand() % 2 == 0){
		type = HEALTH;
		name = "health potion";
	}else{
		type = STAMINA;
		itemSprite.setColor(sf::Color::Green);
		name = "stamina potion";
	}
}
