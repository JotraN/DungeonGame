#ifndef SCORE_MANAGER_H
#define SCORE_MANAGER_H

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

class ScoreManager{
	public:
		ScoreManager();
		~ScoreManager();

		void draw(sf::RenderWindow &window);
		void processEvents(sf::Event &event);
		void setScore(int newScore);
		void saveScores();
		void loadScores();
		
	private:
		std::string paddedScore();	
		sf::Texture texture;
		sf::Sprite scoreBackground;
		sf::Font font;
		std::vector<std::string> scores;
		std::string name;
		std::string score;
};

#endif
