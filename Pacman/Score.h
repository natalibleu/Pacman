#pragma once
#include <SFML/Graphics.hpp>

extern int currentScore;

class Score
{
public:
	Score();
	void UpdateScore();
	void Reset();
	void Draw(sf::RenderWindow& window);

private:
	sf::Font font;
	sf::Text text;
};
