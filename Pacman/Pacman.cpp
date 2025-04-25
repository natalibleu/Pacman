#include "Pacman.h"
#include "Map.h"
#include "Constants.h"
#include "Score.h"
#include "Timers.h"
#include <iostream>

sf::Vector2f WrapCoords(const sf::Vector2f& p)
{
    float sw = static_cast<float>(screenWidth);
    float sh = static_cast<float>(screenHeight);

    return { std::fmod(p.x + sw, sw), std::fmod(p.y + sh, sh) };
}

sf::Vector2i ConvertCoordinates(sf::Vector2f p)
{

    p = WrapCoords(p);

    int c = static_cast<int>(p.x) / blockSize;
    int r = static_cast<int>(p.y) / blockSize;

    return sf::Vector2i{ r,c };
}


void Pacman::SetGhosts(Ghosts& blinky, Ghosts& pinky, Ghosts& inky, Ghosts& clyde)
{
    ghosts[0] = &blinky;
    ghosts[1] = &pinky;
    ghosts[2] = &inky;
    ghosts[3] = &clyde;
}

void Pacman::EatFruits(sf::Vector2f p)
{
    sf::Vector2i indexes = ConvertCoordinates(p);

    maze[indexes.x][indexes.y] = ' ';
    currentScore++;
}

bool Pacman::HasEatenFruit(sf::Vector2f p)
{
    sf::Vector2i indexes = ConvertCoordinates(p);

    return maze[indexes.x][indexes.y] == '.';
}

void Pacman::EatEnergizer(sf::Vector2f p)
{
    sf::Vector2i indexes = ConvertCoordinates(p);

    maze[indexes.x][indexes.y] = ' ';
    currentScore++;


    for (int i = 0; i < 4; i++)
    {
        ghosts[i]->setMode(GhostMode::Frightened);

    }
}

bool Pacman::HasEatenEnergizer(sf::Vector2f p)
{
    sf::Vector2i indexes = ConvertCoordinates(p);

    return maze[indexes.x][indexes.y] == 'o';
}

Ghosts* Pacman::HasEatenGhost(sf::Vector2f p)
{
    sf::Vector2i indexes = ConvertCoordinates(p);// Tile position of p
    for (const auto& ghost : ghosts) { // Assuming ghosts is a std::vector<Ghosts>
        // Get ghost's runtime pixel position and convert to tile position
        sf::Vector2f ghostPos = ghost->GetPosition();
        sf::Vector2i ghostTile = ConvertCoordinates(ghostPos);
        if (ghostTile == indexes) {
            std::cout << "collided with ghost" << std::endl;
            return ghost; // Ghost is at this tile
        }
    }
    return 0;
}

void Pacman::EatGhost(Ghosts* ghost)
{

    currentScore += 200;
    std::cout << "Eaten ghost" << std::endl;
    ghost->ResetGhost();

}


void Pacman::DrawPacman(sf::RenderWindow& window) //self explanatory
{
    // Draw the pacman sprite at its current position.
    window.draw(pacmanSprite);

    // Draw a 2nd sprite that "wraps around" to the left side of the screen.
    auto currentPosition = pacmanSprite.getPosition();
    pacmanSprite.setPosition(pacmanSprite.getPosition() - sf::Vector2f{ static_cast<float>(screenWidth), 0.0f });
    window.draw(pacmanSprite);

    // Restore the sprite's current position.
    pacmanSprite.setPosition(currentPosition);
}

sf::Vector2f GetNextTile(MoveDirection dir)
{
    switch (dir)
    {
    case MoveDirection::None:
        return { 0, 0 };
    case MoveDirection::Up:
        return { 0, -32 };
    case MoveDirection::Down:
        return { 0, 32 };
    case MoveDirection::Left:
        return { -32, 0 };
    case MoveDirection::Right:
        return { 32, 0 };
    }

    return { 0, 0 };
}

// Return true if the tile is not blocked
bool CanMove(sf::Vector2f p)
{
    sf::Vector2i indexes = ConvertCoordinates(p);

    // Grid cells with a # are walls.
    return maze[indexes.x][indexes.y] != '#' && maze[indexes.x][indexes.y] != '=';
}

void Pacman::UpdateAnimation(float deltaTime)
{
    int currentAnimationPosition = 0; //current section

    switch (currentMoveDirection)
    {
    case MoveDirection::Right:
        currentAnimationPosition = 0;
        break;
    case MoveDirection::Up:
        currentAnimationPosition = 6;
        break;
    case MoveDirection::Left:
        currentAnimationPosition = 12;
        break;
    case MoveDirection::Down:
        currentAnimationPosition = 18;
        break;
    default:
        currentAnimationPosition = 0;
        return;
    }

    // deltaTime is the time that has passed between the iterations of the game while loop
    animationTimer += deltaTime; // we increase the value of the timer with deltaTime step
    if (animationTimer > animationEndTime)
    {
        // when the timer reaches the end, we set it to zero
        animationTimer = 0.0f;
        // and we change the animation to the next frame
        currentFrame++;
        currentFrame = currentFrame % 6;
    }

    int animationIndex = currentFrame + currentAnimationPosition;
    pacmanSprite.setTextureRect(sf::IntRect{ {animationIndex * 32 + 2, 0}, {28, 32} });
}

bool Pacman::MoveTo(float deltaTime)
{
    interpolationTimer += deltaTime; //to track progress of interpolation time

    if (interpolationTime > 0.0f)
    {
        float t = std::min(1.0f, interpolationTimer / interpolationTime); //how far pacman has moved between both tiles
        sf::Vector2f newPosition = currentTile + t * (nextTile - currentTile); //the distance between the current and next tile; linear interpolation
        pacmanSprite.setPosition(WrapCoords(newPosition));
    }
    return interpolationTimer >= interpolationTime;
}

bool Pacman::Move(float deltaTime)
{
    // Update pacman's next move direction.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        nextMoveDirection = MoveDirection::Up;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        nextMoveDirection = MoveDirection::Down;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        nextMoveDirection = MoveDirection::Left;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        nextMoveDirection = MoveDirection::Right;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
        nextMoveDirection = MoveDirection::Right;

    Ghosts* res = HasEatenGhost(currentTile);
    if (res != 0)
    {
        if (res->GetMode() == GhostMode::Frightened) {
            EatGhost(res);
        }
        else {
            return false;
        }
    }

    // Move pacman towards the next tile.
    if (MoveTo(deltaTime))
    {
        currentTile = WrapCoords(nextTile);

        if (HasEatenFruit(currentTile))
        {
            EatFruits(currentTile);
        }

        if (HasEatenEnergizer(currentTile))
        {
            EatEnergizer(currentTile);
        }

        // if we can go to the nextMoveDirection we go there
        if (CanMove(currentTile + GetNextTile(nextMoveDirection))) // Checks if we can move to the next tile, which is calculated by (currentTile + (Direction in which we are going))
        {
            nextTile = currentTile + GetNextTile(nextMoveDirection);

            // We change direction 
            currentMoveDirection = nextMoveDirection;
        }
        // If we cannot go to nextMoveDirection, we go to currentMoveDirection
        else if (CanMove(currentTile + GetNextTile(currentMoveDirection)))
        {
            nextTile = currentTile + GetNextTile(currentMoveDirection);
        }

        interpolationTime = (nextTile - pacmanSprite.getPosition()).length() / moveSpeed; //from the next position we remove the current position of the Pacman and we get the length of the distance to the next position
        // After that we divide it by the move speed (180) and we receive the time at which we will get to the next tile
        interpolationTimer = 0.0f;
    }

    UpdateAnimation(deltaTime);
    return true;
}

sf::Vector2f Pacman::GetPosition()
{
    return pacmanSprite.getPosition();
}

void Pacman::Die()
{
    //collision with ghosts always when not in booster

}

Pacman::Pacman() : pacmanTexture("assets/Pacman.png"), pacmanSprite(pacmanTexture, sf::IntRect{ {0,0}, {32,32} })
{
    Reset();
}

void Pacman::Reset()
{
    currentMoveDirection = MoveDirection::None;
    nextMoveDirection = MoveDirection::None;
    currentFrame = 0;
    animationTimer = 0;


    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (maze[i][j] == 'P')
            {
                float x = static_cast<float>(j * blockSize);
                float y = static_cast<float>(i * blockSize);

                currentTile = nextTile = sf::Vector2f{ x, y };

                pacmanSprite.setPosition(currentTile);
            }
        }
    }
}