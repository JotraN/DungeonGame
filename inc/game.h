#ifndef GAME_H
#define GAME_H

#include <SFML/Window.hpp>
#include "room.h"
#include "player.h"
#include "menu.h"
#include "scoremanager.h"
#include "states.h"

class Game{
	public:
		Game();
		~Game();

		void run();

	private:
		const static int SCREEN_WIDTH = 800;
		const static int SCREEN_HEIGHT = 600;

		void processEvents();
		void display();
		void drawGameOver();
		void drawPause();
		void update();
		void restart();
		void saveScore();

		bool running;

		sf::RenderWindow window;
		sf::View camera;
		sf::Font font;

		Player player;
		Room room;
		Menu menu;
		ScoreManager scoreMan;
		State currentState;
};

#endif
