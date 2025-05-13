#pragma once
#include <SFML/Graphics.hpp>

class Pellets 
{
public: 
	void DrawPellets(sf::RenderWindow& window);
	Pellets();

private:
	int collectedFood = 0;

	sf::Texture pelletsTexture;
	sf::Sprite pelletsSprite;

};

