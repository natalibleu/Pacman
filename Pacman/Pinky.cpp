#include "Pinky.h"
#include "Pacman.h"
#include "Constants.h"

sf::Vector2f Pinky::getTargetPosition(const sf::Vector2f& pacmanPos)
{
	if (mode == GhostMode::Scatter)
	{
		return sf::Vector2f{ static_cast<float>(screenHeight), 0.f };
	}

	sf::Vector2f targetPacmanPos = pacmanPos + sf::Vector2f(static_cast<float>(4 * blockSize), 0.f);

	return targetPacmanPos;
}

Pinky::Pinky() : Ghosts("assets/pinky1.png", '1')
{
	
}
