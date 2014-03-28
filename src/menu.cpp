#include "menu.h"
#include <fstream>
#include <sstream>

Menu::Menu() : selector(0){
	if(!font.loadFromFile("fonts/minecraftia.ttf")){
	}

	menuItems.push_back("PLAY");
	menuItems.push_back("QUIT");
	loadScores();
}

Menu::~Menu(){
}

void Menu::draw(sf::RenderWindow &window){
	window.clear(sf::Color(255, 255, 255));
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(24);

	int posX = 235;
	int posY = 50;
	text.setColor(sf::Color::Black);
	// Draw scores
	for(int i = 0; i < scores.size(); i++){
		std::ostringstream ostr;
		ostr << i+1;
		text.setString(ostr.str() + ". " +  scores[i]);
		text.setPosition(sf::Vector2f(posX, posY));
		window.draw(text);	
		posY += 30;
	}

	posX = 350;
	posY = 250;
	// Draw menu items
	for(int i = 0; i < menuItems.size(); i++){
		if(selector == i)
			text.setColor(sf::Color::Red);
		else
			text.setColor(sf::Color::Black);

		text.setString(menuItems[i]);
		text.setPosition(sf::Vector2f(posX, posY));
		window.draw(text);	

		// Increment to draw next item below
		posY += 30;
	}
}

void Menu::processEvents(sf::Event &event, State &currentState){
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		if(selector < menuItems.size() - 1)
			selector++;
			
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		if(selector > 0)
			selector--;

	if(event.type == sf::Event::KeyPressed){
		if(event.key.code == sf::Keyboard::Return){
			if(selector == 0)
				currentState = PLAY;
			else
				currentState = QUIT;
		}
	}
}

void Menu::loadScores(){
	std::ifstream scores;
	scores.open("data/scores");
	std::string line;
	std::string scoresF = "";
	while(std::getline(scores, line))
		this->scores.push_back(line);
	scores.close();
}
