#pragma once
#include "Ghosts.h"

class Inky : public Ghosts
{
private: 
	bool localScatterMode = false;

public:
	sf::Vector2f getTargetPosition(const sf::Vector2f& pacmanPos) override; //overriding
	bool Scatter();
	Inky();
};

