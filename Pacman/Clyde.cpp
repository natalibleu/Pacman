#include "Clyde.h"
#include "Pacman.h"
#include "Constants.h"
#include "Blinky.h"

void Clyde::GetBlinkyPos(sf::Vector2f& blinkyPos)
{
    this->blinkyPos = blinkyPos;
}

sf::Vector2f Clyde::getTargetPosition(const sf::Vector2f& pacmanPos)
{
    if (mode == GhostMode::Scatter)
    {
        //getting the corresponding corner position for each ghost
        return sf::Vector2f{ 0.f, static_cast<float>(screenHeight) };
    }

    //Clyde targeting 2 blocks ahead of Pacman
    sf::Vector2f clydeTarget = pacmanPos + sf::Vector2f(static_cast<float>(2 * blockSize), 0.f);

    //getting vector from Blinky's position to Clyde's target
    sf::Vector2f vectorToTarget = clydeTarget - blinkyPos;

    //doubling the resulted vector.
    sf::Vector2f doubledVector = vectorToTarget * 2.f;

    //getting Clyde's current position
    sf::Vector2f currentPos = ghostSprite.getPosition();

    //gives the vector position of the doubled position from the current position
    sf::Vector2f finalTarget = currentPos + doubledVector;

    //converting to grid coordinates and putting it to the nearest cell
    int targetColumn = static_cast<int>(finalTarget.x / blockSize) * blockSize;
    int targetRow = static_cast<int>(finalTarget.y / blockSize) * blockSize;

    return sf::Vector2f(static_cast<float>(targetColumn), static_cast<float>(targetRow));
}

Clyde::Clyde() : Ghosts("assets/clyde1.png", '3')
{

}
