#include "Inky.h"
#include "Constants.h"

bool Inky::Scatter()
{
	return true;
}

sf::Vector2f Inky::getTargetPosition(const sf::Vector2f& pacmanPos)
{
	sf::Vector2f cornerPosition = sf::Vector2f{ static_cast<float>(screenHeight), static_cast<float>(screenHeight) };

	if (mode == GhostMode::Scatter)
	{
		return cornerPosition;
	}

	sf::Vector2f distanceVectorPacman = pacmanPos - getPosition();
	float distancePacman = distanceVectorPacman.length();

	sf::Vector2f distanceVectorCorner = cornerPosition - getPosition();
	float distanceCorner = distanceVectorCorner.length();

	if (distancePacman < 3 * blockSize)
	{
		localScatterMode = true;
	}
	else if (distanceCorner < 4 * blockSize)
	{
		localScatterMode = false;
	}

	if (localScatterMode)
	{
		return cornerPosition;
	}
	else
	{
		return pacmanPos;
	}
}

Inky::Inky() : Ghosts("assets/inky1.png", '2')
{
}

