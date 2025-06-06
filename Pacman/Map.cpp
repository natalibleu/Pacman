#include <array>
#include <string>
#include "Map.h"
#include <SFML/Graphics.hpp>

char maze[rows][columns];

void Map::DrawMap(sf::RenderWindow& window)
{
	//drawing map for each #
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (maze[i][j] == '#')
			{
				wallSprite.setPosition(sf::Vector2f(static_cast<float>(j * texture.getSize().x),
					static_cast<float>(i * texture.getSize().y)));
				window.draw(wallSprite);
			}
		}
	}
}

void Map::Reset()
{
	for (int i = 0; i < rows; ++i)
		for (int j = 0; j < columns; ++j)
			maze[i][j] = mazeLayout[i][j];
}

Map::Map() : texture("assets/stena1.png"), wallSprite(texture)
{
	Reset();
}