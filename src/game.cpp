#include "game.h"
#include <ctime>
#include <fstream>

Game::Game() : running(true){
	srand(time(0));
	window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "GAME");
	window.setVerticalSyncEnabled(true);

	room.generateRooms();

	camera.setCenter(player.getPosition());
	camera.setSize(sf::Vector2f(800, 600));

	currentState = MENU;

	if(!font.loadFromFile("fonts/minecraftia.ttf")){}

	scoreMan.loadScores();
}

Game::~Game(){
}

void Game::run(){
	while(running){
		update();
		processEvents();
		display();
	}
}

void Game::processEvents(){
	sf::Event event;
	while(window.pollEvent(event)){
		if(event.type == sf::Event::Closed)
			running = false;
		if(currentState == PLAY){
			if(event.type == sf::Event::KeyPressed && 
					event.key.code == sf::Keyboard::Escape)
				currentState = PAUSE;
			player.processEvents(event);
		} else if(currentState == PAUSE){
			if(event.type == sf::Event::KeyPressed){ 
				if(event.key.code == sf::Keyboard::Escape)
					currentState = PLAY;
				else if(event.key.code == sf::Keyboard::BackSpace)
					currentState = GAMEOVER;
			}
		} else if(currentState == GAMEOVER){
			scoreMan.processEvents(event);
			if(event.type == sf::Event::KeyPressed)
				if(event.key.code == sf::Keyboard::Return)
					restart();	
		} else if(currentState == MENU){
			menu.processEvents(event, currentState);
		}	
	}
}

void Game::display(){
	if(currentState == PLAY){
		window.clear(sf::Color(82, 57, 23));
		window.setView(camera);
		room.draw(window);
		player.draw(window);
		player.drawStats(window);
	} else if(currentState == MENU){
		window.clear(sf::Color::White);
		menu.draw(window);
	} else if(currentState == GAMEOVER){
		scoreMan.draw(window);
	} else if(currentState == PAUSE){
		drawPause();
	}
	window.display();
}

void Game::drawPause(){
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(50);
	text.setColor(sf::Color::White);
	text.setPosition(100, SCREEN_HEIGHT/3);
	text.setString("Paused\nESCAPE to resume.\nBACKSPACE to quit.");
	window.draw(text);
}

void Game::update(){
	if(currentState == PLAY){
		player.update(room);
		camera.setCenter(player.getPosition());
		if(player.isDead())
			currentState = GAMEOVER;
	} else if(currentState == GAMEOVER){
		scoreMan.setScore(room.getLvl());
	} else if(currentState == QUIT){
		running = false;
	}
}

void Game::restart(){
	scoreMan.saveScores();
	player = Player();
	// Must load manually outside of constructor due to soundbuffers
	player.loadSoundFiles();
	room = Room();
	room.generateRooms();
	currentState = MENU;
	menu = Menu();
}
