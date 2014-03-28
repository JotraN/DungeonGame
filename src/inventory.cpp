#include "player.h"
#include "inventory.h"
#include "weapon.h"

Inventory::Inventory() : selector(0){
	if(!texture.loadFromFile("images/inventory.png")){
	}
	if(!font.loadFromFile("fonts/minecraftia.ttf")){
	}
	invBackground.setTexture(texture);
	invBackground.setPosition(210, 40);

	invSelectorBox.setSize(sf::Vector2f(60, 60));
	invSelectorBox.setFillColor(sf::Color::Transparent);
	invSelectorBox.setOutlineColor(sf::Color(255, 255, 0, 100));
	invSelectorBox.setOutlineThickness(5);
	invSelectorBox.setPosition(70, 75);
	errorMsgd = false;
}

Inventory::~Inventory(){
}

void Inventory::draw(sf::RenderWindow &window, Player &player){
	invBackground.setTexture(texture);
	window.draw(invBackground);

	// Draw equipped item
	sf::Text equipped;
	equipped.setFont(font);
	equipped.setCharacterSize(14);
	equipped.setColor(sf::Color::Black);
	equipped.setString(player.getEquippedWeapon().getName());
	equipped.setPosition(305, 548);
	window.draw(equipped);

	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(14);
	text.setColor(sf::Color::Black);
	text.setPosition(270, 414);
	float posX = 232;
	float posY = 64;
	// Draw each item
	for(int i = 0; i < items.size(); i++){
		std::string itemName = items[i]->getName();
		text.setString(itemName);

		items[i]->draw(window, posX, posY);

		if(selector == i){
			invSelectorBox.setPosition(posX+5, posY+5);
			window.draw(text);
		}
		window.draw(invSelectorBox);
		posX += 115;
		// Move down one line every 3 spots
		if(i != 0 && (i+1) % 3 == 0){
			posY += 115;
			posX = 232;
		}
	}
	if(errorMsgd){
		text.setCharacterSize(20);
		text.setPosition(220, 450);
		text.setString("Cannot drop \nequipped weapon.");
		window.draw(text);
	}
}

void Inventory::processEvents(sf::Event &event, Player &player){
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		if(selector < items.size() - 1)
			selector++;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		if(selector > 0)
			selector--;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		if(selector + 3 < items.size())
			selector += 3;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		if(selector - 3 >= 0)
			selector -= 3;

	// Uses event since events are queued
	if(event.type == sf::Event::KeyPressed){
		errorMsgd = false;
		if(event.key.code == sf::Keyboard::U)
			items[selector]->use(*this, player);
		else if(event.key.code == sf::Keyboard::D){
			if(items[selector]->getName() != player.getEquippedWeapon().getName()){
				removeItem(items[selector]);
			} else
				errorMsgd = true;
		}
	}
}

void Inventory::addItem(Item *item){
	items.push_back(item);
}

void Inventory::removeItem(Item *item){
	for(int i = 0; i < items.size(); i++){
		if(items[i] == item){
			items.erase(items.begin()+i);
			break;
		}
	}
}

bool Inventory::isFull(){
	return items.size() >= 9;
}

void Inventory::resetSelectors(){
	selector = 0;
	errorMsgd = false;
}

const std::vector<Item*>Inventory::getItems() const{
	return items;
}
