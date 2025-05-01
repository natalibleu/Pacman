#pragma once
#include "Map.h"
#include "Pacman.h"
#include "Pellets.h"
#include "Energizer.h"
#include "Score.h"
#include "Blinky.h"
#include "Pinky.h"
#include "Inky.h"
#include "Clyde.h"
#include "Ghosts.h"
#include "Constants.h"
#include "Lives.h"

class Game
{
    //making the objects
    Map map;
    Score score;
    Pacman pacman;
    Pellets pellet;
    Energizer energizer;
    Blinky blinky;
    Pinky pinky;
    Inky inky;
    Clyde clyde;
    Lives lives;

    bool isRunning = true;
    bool gameWon = false;

public:
    Game();
    void Update(sf::RenderWindow& window, sf::Time& elapsedTime);
    void Reset();
    void CheckLives();
    void CheckWin(sf::Time& elapsedTime);
};