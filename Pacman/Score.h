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

	void UpdateScore(sf::RenderWindow& window);
	void Reset();
};
