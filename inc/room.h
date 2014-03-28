#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include <queue>
#include "directions.h"
#include "block.h"
#include "enemy.h"
#include "stairs.h"
#include "item.h"

class Room{
	public:
		Room();
		~Room();

		void generateRooms();
		void clearRooms();

		void draw(sf::RenderWindow &window);

		int getLvl() const;
		const std::vector<Block>& getBlocks() const;
		const std::vector<Stairs>& getStairs() const;
		std::vector<Enemy>& getEnemies();
		std::vector<Item*>& getItems();

	private:
		void createEntrance(std::string &tileMap, int offsetX=0, int offsetY=0);
		void createExit(std::string &tileMap, int offsetX=0, int offsetY=0);
		void createCornerBlocks(std::string &tileMap);
		void createCenterBlocks(std::string &tileMap);
		void addBlock(int x, int y);
		void addEnemy(int x, int y);
		void addItem(int x, int y);

		std::queue<Direction> doors;
		std::vector<Block> blocks;
		std::vector<Stairs> stairs;
		std::vector<Enemy> enemies;
		std::vector<Item*> items;
		int lvl;
};

#endif
