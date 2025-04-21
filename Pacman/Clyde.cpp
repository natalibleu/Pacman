#include "Clyde.h"
#include "Pacman.h"
#include "Constants.h"
#include "Blinky.h"

void Clyde::GetBlinkyPos(sf::Vector2f newBlinkyPos)
{
    blinkyPos = newBlinkyPos;
}

sf::Vector2f Clyde::getTargetPosition(const sf::Vector2f& pacmanPos)
{
    if (mode == GhostMode::Scatter)
    {
        return sf::Vector2f{ 0.f, static_cast<float>(screenHeight) };
    }

    //Clyde targeting 2 blocks ahead of Pacman
    sf::Vector2f clydeTarget = pacmanPos + sf::Vector2f(static_cast<float>(2 * blockSize), 0.f);

    //getting vector from Blinky's position to Clyde's target
    sf::Vector2f vectorToTarget = clydeTarget - blinkyPos;

    //doubling the vector.
    sf::Vector2f doubledVector = vectorToTarget * 2.f;

    //targeting the cell the doubled vector points to from Clyde's current position
    sf::Vector2f currentPos = ghostSprite.getPosition();
    sf::Vector2f finalTarget = currentPos + doubledVector;

    //converting to grid coordinates and snap to nearest cell
    int targetColumn = static_cast<int>(finalTarget.x / blockSize) * blockSize;
    int targetRow = static_cast<int>(finalTarget.y / blockSize) * blockSize;

    return sf::Vector2f(static_cast<float>(targetColumn), static_cast<float>(targetRow));
}

Clyde::Clyde() : Ghosts("assets/clyde1.png", '3')
{

}
