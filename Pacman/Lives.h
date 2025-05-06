#pragma once
#include "SFML/Graphics.hpp"
#include "Pacman.h"
#include "Ghosts.h"
#include "Audio.h"

class Lives
{
private:
    sf::Texture livesTexture;
    sf::Sprite livesSprite;

    Audio audio;

    int lives = 3;

public:
    Lives();
    bool IsColliding(sf::FloatRect& pacman, sf::FloatRect& ghost);
    void CheckCollision(sf::RenderWindow& window, Pacman& pacman,Audio& audio, Ghosts& blinky, Ghosts& pinky, Ghosts& inky, Ghosts& clyde);
    void CheckGhost(Pacman& pacman, Ghosts& ghost, Audio& audio);
    int GetLives() { return lives; }
    void Reset();
};