#include "Inky.h"
#include "Constants.h"

bool Inky::Scatter()
{
	return true;
}

sf::Vector2f Inky::getTargetPosition(const sf::Vector2f& pacmanPos)
{

	//calculating the corresponding corner position to each ghost
	sf::Vector2f cornerPosition = sf::Vector2f{ static_cast<float>(screenHeight), static_cast<float>(screenHeight) };

	if (mode == GhostMode::Scatter)
	{
		return cornerPosition;
	}

	//how far the Inky is from Pacman in the current time
	sf::Vector2f distanceVectorPacman = pacmanPos - GetPosition();
	float distancePacman = distanceVectorPacman.length();

	//how far the Inky is from the corner in the current time
	sf::Vector2f distanceVectorCorner = cornerPosition - GetPosition();
	float distanceCorner = distanceVectorCorner.length();

	//change to localScatterMode after going too close to Pacman
	if (distancePacman < 3 * blockSize)
	{
		localScatterMode = true;
	}
	//after getting too close to the corner, we switch to Chase mode again
	else if (distanceCorner < 4 * blockSize)
	{
		localScatterMode = false;
		setMode(GhostMode::Chase);
	}

	//depending on the different condition, we return the associative target
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
