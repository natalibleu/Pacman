#pragma once
#include "Ghosts.h"

class Clyde : public Ghosts
{
private:
	sf::Vector2f blinkyPos;

public:
	void GetBlinkyPos(sf::Vector2f newBlinkyPos);
	sf::Vector2f getTargetPosition(const sf::Vector2f& pacmanPos) override; //overriding
	Clyde();
};

