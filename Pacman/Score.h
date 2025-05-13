#pragma once
#include <SFML/Graphics.hpp>

extern int currentScore;

class Score
{
private:
	sf::Font font;
	sf::Text text;

public:
	Score();

	void UpdateScore();
	void Reset();
	void Draw(sf::RenderWindow& window);
};
