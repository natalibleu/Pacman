#pragma once
#include <SFML/Graphics.hpp>

class Energizer 
{
public:
	void DrawEnergizer(sf::RenderWindow& window);
	Energizer();

private:
	sf::Texture energizerTexture;
	sf::Sprite energizerSprite;
};

