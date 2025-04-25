#pragma once
#include <string>
#include <SFML/Graphics.hpp>

//map directions
const int rows = 22;
const int columns = 22;
extern char maze[rows][columns];
const char mazeLayout[rows][columns] = { // P is Pacman's spawn point; 123 is each ghosts spawn point, 1 is for , 2 is for , 3 is for 
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

class Map {
private:
	sf::Texture texture;
	sf::Sprite wallSprite;
public:
	Map();
	void DrawMap(unsigned int x, unsigned int y, sf::RenderWindow& window);
	void Reset();
};