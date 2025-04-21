#pragma once
#include "Ghosts.h"

class Blinky : public Ghosts
{
public:
	sf::Vector2f getTargetPosition(const sf::Vector2f& pacmanPos) override; //overriding
	Blinky();
};

