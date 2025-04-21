#include "Blinky.h"
#include "Pacman.h"
#include "Constants.h"

Blinky::Blinky() : Ghosts("assets/blinky1.png", '0')
{

}

sf::Vector2f Blinky::getTargetPosition(const sf::Vector2f& pacmanPos)
{
	if (mode == GhostMode::Scatter)
	{
		return sf::Vector2f{ 0.f, 0.f };
	}
	return pacmanPos;
}
