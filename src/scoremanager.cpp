#include "scoremanager.h"
#include <fstream>
#include <sstream>
#include <algorithm>

ScoreManager::ScoreManager(){
	if(!texture.loadFromFile("images/gameover.png")){
	}
	if(!font.loadFromFile("fonts/minecraftia.ttf")){}
	scoreBackground.setTexture(texture);
}

ScoreManager::~ScoreManager(){
}

void ScoreManager::draw(sf::RenderWindow &window){
	scoreBackground.setTexture(texture);
	window.draw(scoreBackground);
	sf::Text text;
	text.setFont(font);
	// Draw name
	text.setCharacterSize(70);
	text.setPosition(50, 480);
	text.setString(name);
	window.draw(text);
	// Draw score
	text.setCharacterSize(150);
	text.setPosition(200, 180);
	text.setString(score);
	window.draw(text);
}

void ScoreManager::processEvents(sf::Event &event){
	if(event.type == sf::Event::KeyPressed){
		if(event.key.code == sf::Keyboard::Return){
			scores.push_back(paddedScore() + name);
		} else if(event.key.code == sf::Keyboard::BackSpace){
			name = name.substr(0, name.size() - 1);
		}
	}
	if(event.type == sf::Event::TextEntered){
		// ASCII text, ignore backspace, limit name length
		if(event.text.unicode < 128 && event.text.unicode != 8 && name.size() <= 12){
			name += toupper(static_cast<char>(event.text.unicode));
		}
	}
}

void ScoreManager::setScore(int newScore){
	std::ostringstream oss;
	oss << newScore;
	score = oss.str();
}

void ScoreManager::saveScores(){
	std::sort(scores.begin(), scores.end(), std::greater<std::string>());
	// Limit to only top 5 scores
	if(scores.size() > 5)
		scores.pop_back();
	std::ofstream scoreFile;
	scoreFile.open("data/scores");
	for(int i = 0; i < scores.size(); i++){
		scoreFile << scores[i] + "\n";
	}
	scoreFile.close();
	// Reset entered text
	name = "";
}

void ScoreManager::loadScores(){
	std::ifstream scoreFile;
	scoreFile.open("data/scores");
	std::string line;
	while(std::getline(scoreFile, line))
		scores.push_back(line);
	scoreFile.close();
}

std::string ScoreManager::paddedScore(){
	int width = 10;
	int paddedSpace = width - score.size();
	std::string paddedScore = score;
	for(int i = 0; i < paddedSpace; i++)
		paddedScore += " ";
	return paddedScore;
}
