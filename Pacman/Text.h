#pragma once
#include "SFML/Graphics.hpp"

class Text
{
public:
	Text();
	void WinningText(sf::RenderWindow& window);
	void LosingText(sf::RenderWindow& window);
	void StartGame(sf::RenderWindow& window);

private:
	sf::Font font;
	sf::Text text;
};

