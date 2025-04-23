#include <array>
#include <string>
#include "Map.h"
#include <SFML/Graphics.hpp>

char maze[rows][columns] = { // P is Pacman's spawn point; 123 is each ghosts spawn point, 1 is for , 2 is for , 3 is for 
	" ################### ", //each o is for the boosters and each . is for the fruits, = is the door,
	" #........#........# ",
	" #o##.###.#.###.##o# ",
	" #.................# ",
	" #.##.#.#####.#.##.# ",
	" #....#...#...#....# ",
	" ####.### # ###.#### ",
	"    #.#   0   #.#    ",
	"#####.# ##=## #.#####",
	"     .  #123#  .     ",
	"#####.# ##### #.#####",
	"    #.#       #.#    ",
	" ####.# ##### #.#### ",
	" #........#........# ",
	" #.##.###.#.###.##.# ",
	" #o.#.....P.....#.o# ",
	" ##.#.#.#####.#.#.## ",
	" #....#...#...#....# ",
	" #.######.#.######.# ",
	" #.................# ",
	" ################### "
};

void Map::DrawMap(unsigned int x, unsigned int y, sf::RenderWindow& window)
{
	//drawing map for each #
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (maze[i][j] == '#')
			{
				wallSprite.setPosition(sf::Vector2f(static_cast<float>(x + j * texture.getSize().x),
					static_cast<float>(y + i * texture.getSize().y)));
				window.draw(wallSprite);
			}
		}
	}
}

Map::Map() : texture("assets/stena1.png"), wallSprite(texture) 
{
}