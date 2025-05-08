#include "Pacman.h"
#include "Map.h"
#include "Constants.h"
#include "Score.h"
#include "Timers.h"

void Pacman::SetGhosts(Ghosts& blinky, Ghosts& pinky, Ghosts& inky, Ghosts& clyde)
{
    ghosts[0] = &blinky;
    ghosts[1] = &pinky;
    ghosts[2] = &inky;
    ghosts[3] = &clyde;
}

void Pacman::EatFruits(sf::Vector2f p)
{
    audio.UpdateSound(LoadAudio::EatFood);

    sf::Vector2i indexes = ConvertCoordinates(p);

    maze[indexes.x][indexes.y] = ' ';
    currentScore++;
    eatenPellets++;
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
    eatenEnergizers++;
    audio.UpdateSound(LoadAudio::EatFood);

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

void Pacman::EatGhost(Ghosts* ghost)
{
    currentScore += 200;
    audio.UpdateSound(LoadAudio::EatGhost);
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

void Pacman::EndingAnimation(float deltaTime)
{
    if (!won)
    {
        won = true;

        if (!pacmanTexture.loadFromFile("assets/ending.png")) {
            return;
        }
        pacmanSprite.setTexture(pacmanTexture);
        animationTimer = 0;
        currentFrame = 0;
    }

    animationTimer += deltaTime; // we increase the value of the timer with deltaTime step
    currentFrame = animationTimer * 10;

    if (currentFrame > 11)
    {
        return;
    }

    pacmanSprite.setTextureRect(sf::IntRect{ {currentFrame * 38, 0}, {32, 32} });
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

Pacman::Pacman() : defaultTexture("assets/Pacman.png"), pacmanSprite(pacmanTexture, sf::IntRect{ {0,0}, {32,32} })
{
    Reset();
}

void Pacman::Reset()
{
    currentMoveDirection = MoveDirection::None;
    nextMoveDirection = MoveDirection::None;
    currentFrame = 0;
    animationTimer = 0;

    won = false;

    pacmanTexture = defaultTexture;
    pacmanSprite.setTexture(pacmanTexture);

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
    pacmanSprite.setTextureRect(sf::IntRect{ {2, 0}, {28, 32} });
}

void Pacman::ResetGhosts()
{
    for (int i = 0; i < 4; i++) {
        ghosts[i]->ResetGhost();
    }
}