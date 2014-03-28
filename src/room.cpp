#include "room.h"
#include "spinbaddie.h"
#include "weapon.h"
#include "potion.h"
#include <stdlib.h>

Room::Room() : lvl(0){
}

Room::~Room(){
	blocks.clear();
	enemies.clear();
}

void Room::generateRooms(){
	lvl++;
	int roomNum = 10 + lvl;
	// Limit to 40 rooms
	if(roomNum > 40)
		roomNum = 40;

	int x = 0, y = 0;

	std::string tileMap = "";
	tileMap += "XXXXXXXXXXXX\n";
	tileMap += "X          X\n";
	tileMap += "X          X\n";
	tileMap += "X          X\n";
	tileMap += "X          X\n";
	tileMap += "X          X\n";
	tileMap += "X          X\n";
	tileMap += "X          X\n";
	tileMap += "XXXXXXXXXXXX";

	for(int i = 0; i < roomNum; i++){
		std::string roomMap = tileMap;
		// Create first exit
		if(i == 0){
			doors.push(SOUTH);
			roomMap[109] = ' ';
			roomMap[110] = ' ';
		} else{
			createEntrance(roomMap);
			// Don't create exit in last room
			if(i != roomNum - 1)
				createExit(roomMap);
		} 
		createCornerBlocks(roomMap);
		if(i != roomNum - 1)
			createCenterBlocks(roomMap);
		// Add room pieces according to room map
		for(int j = 0; j < roomMap.size(); j++){
			if(roomMap[j] == 'X')
				addBlock(x, y);
			else if(roomMap[j] == '\n'){
				y += 64;
				x -= 64*13;
			} 
			// Add stairs in last room
			else if(j == 58 && i == roomNum - 1)
				stairs.push_back(Stairs(x, y));
			else{
				int randPiece = rand() % 100;
				if(randPiece == 0)
					addEnemy(x, y);
				else if(randPiece == 1)
					addItem(x, y);
			}
			x +=64;
		}
		// Move x and y coordinates to next position for new room
		if(doors.front() == SOUTH){
			x -= 64*12;
			y += 64;
		} else if(doors.front() == EAST){
			y -= 64*8;
		} else if(doors.front() == WEST){
			x -= 64*12*2;
			y -= 64*8;
		}
	}
}
void Room::createEntrance(std::string &roomMap, int offsetX, int offsetY){
	switch(doors.front()){
		case NORTH:
			roomMap[109] = ' ';
			roomMap[110] = ' ';
			break;
		case SOUTH:
			roomMap[5] = ' ';
			roomMap[6] = ' ';
			break;
		case WEST:
			roomMap[63] = ' ';
			roomMap[76] = ' ';
			break;
		case EAST:
			roomMap[52] = ' ';
			roomMap[65] = ' ';
			break;
	}
}

void Room::createExit(std::string &roomMap, int offsetX, int offsetY){
	bool exitCreated = false;
	int randDoor = rand() % 3;
	// Generate exit by random, exit to north is not
	// created to prevent rooms from overlapping.
	// Don't create an exit on an entrance.
	if(randDoor == 0 && doors.front() != NORTH){
		exitCreated = true;
		doors.push(SOUTH);
		roomMap[109] = ' ';
		roomMap[110] = ' ';
	} else if(randDoor == 1 && doors.front() != WEST){
		exitCreated = true;
		doors.push(EAST);
		roomMap[63] = ' ';
		roomMap[76] = ' ';
	} else if(randDoor == 2 && doors.front() != EAST){
		exitCreated = true;
		doors.push(WEST);
		roomMap[52] = ' ';
		roomMap[65] = ' ';
	}
	// Create default door to SOUTH if no exit created
	if(!exitCreated){
		exitCreated = true;
		doors.push(SOUTH);
		roomMap[109] = ' ';
		roomMap[110] = ' ';
	}
	doors.pop();
}

void Room::createCornerBlocks(std::string &roomMap){
	// Run random 4 times for each corner
	// Top left corner
	if(rand() % 2 == 1){
		roomMap[14] = 'X';
		roomMap[15] = 'X';
		roomMap[27] = 'X';
	}
	// Top right corner
	if(rand() % 2 == 1){
		roomMap[22] = 'X';
		roomMap[23] = 'X';
		roomMap[36] = 'X';
	}
	// Botton left corner
	if(rand() % 2 == 1){
		roomMap[79] = 'X';
		roomMap[93] = 'X';
		roomMap[92] = 'X';
	}
	// Botton right corner
	if(rand() % 2 == 1){
		roomMap[88] = 'X';
		roomMap[100] = 'X';
		roomMap[101] = 'X';
	}
}

void Room::createCenterBlocks(std::string &roomMap){
	if(rand() % 2 == 1){
		roomMap[57] = 'X';
		roomMap[58] = 'X';
		roomMap[70] = 'X';
		roomMap[71] = 'X';
	}
}

void Room::addBlock(int x, int y){
	blocks.push_back(Block(x, y));
}

void Room::addEnemy(int x, int y){
	enemies.push_back(SpinBaddie(x, y, lvl));
}

void Room::addItem(int x, int y){
	int randItem = rand() % 10;
	if(randItem == 1)	
		items.push_back(new Weapon(x, y));
	else if(randItem % 2 == 0)
		items.push_back(new Potion(x, y));
}

void Room::draw(sf::RenderWindow &window){
	for(int i = 0; i < blocks.size(); i++)
		blocks[i].draw(window);

	for(int i = 0; i < stairs.size(); i++)
		stairs[i].draw(window);

	for(int i = 0; i < enemies.size(); i++)
		enemies[i].draw(window);

	for(int i = 0; i < items.size(); i++)
		items[i]->draw(window);
}

void Room::clearRooms(){
	doors.pop();
	blocks.clear();
	enemies.clear();
	items.clear();
	stairs.clear();
}

int Room::getLvl() const{
	return lvl;
}

const std::vector<Block>& Room::getBlocks() const{
	return blocks;
}

const std::vector<Stairs>& Room::getStairs() const{
	return stairs;
}

std::vector<Enemy>& Room::getEnemies(){
	return enemies;
}

std::vector<Item*>& Room::getItems(){
	return items;
}
