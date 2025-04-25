#include "Ghosts.h"
#include "Constants.h"
#include "Map.h"
#include <iostream>

sf::Vector2f WrapCoords2(const sf::Vector2f& p)
{
    float sw = static_cast<float>(screenWidth);
    float sh = static_cast<float>(screenHeight);

    return { std::fmod(p.x + sw, sw), std::fmod(p.y + sh, sh) };
}

sf::Vector2i ConvertCoordinates2(sf::Vector2f p)
{

    p = WrapCoords2(p);

    int c = static_cast<int>(p.x) / blockSize;
    int r = static_cast<int>(p.y) / blockSize;

    return sf::Vector2i{ r,c };
}

bool CanMoveTo(sf::Vector2f p)
{
    sf::Vector2i indexes = ConvertCoordinates2(p);

    // Grid cells with a # are walls.
    return maze[indexes.x][indexes.y] != '#';
}

sf::Vector2f GetNextTile(Direction dir)
{
    switch (dir)
    {
    case Direction::None:
        return { 0, 0 };
    case Direction::Up:
        return { 0, -32 };
    case Direction::Down:
        return { 0, 32 };
    case Direction::Left:
        return { -32, 0 };
    case Direction::Right:
        return { 32, 0 };
    }

    return { 0, 0 };
}

void Ghosts::setMode(GhostMode newMode)
{
    // Change the mode of the ghost
    mode = newMode;
    // Reset the timer
    modeTimer.Start();
    // if we are in frightened mode, change the sprite
    if (mode == GhostMode::Frightened) {
        if (!ghostTexture.loadFromFile("assets/frightened.png")) {
            return;
        }
        ghostSprite.setTexture(ghostTexture);
    }
    // else, we set it to default
    else {
        ghostTexture = defaultTexture;
        ghostSprite.setTexture(ghostTexture);
    }
}

void Ghosts::ResetGhost()
{
    setMode(GhostMode::Chase);
    MapSearch();
}

Direction Ghosts::OppositeDirection(Direction dir) //this returns the opposite of the last direction that I have been in
{
    switch (dir) {
    case Direction::Up: return Direction::Down;
    case Direction::Down: return Direction::Up;
    case Direction::Left: return Direction::Right;
    case Direction::Right: return Direction::Left;
    default: return Direction::None;
    }
}

bool Ghosts::MoveTo(float deltaTime)
{
    interpolationTimer += deltaTime;

    if (interpolationTime > 0.0f)
    {
        float t = std::min(1.0f, interpolationTimer / interpolationTime);
        sf::Vector2f newPosition = currentTile + t * (nextTile - currentTile);
        ghostSprite.setPosition(WrapCoords2(newPosition));
    }
    return interpolationTimer >= interpolationTime;
}

void Ghosts::Move(float deltaTime, const sf::Vector2f& pacmanPos, const sf::Vector2f& ghostPos)
{
    // update the timer of the ghost
    modeTimer.Update(deltaTime);
    // Check the mode timer and adjust the mode if necessary
    //std::cout << modeTimer.Time() << std::endl;
    if (modeTimer.Time() < 0.f) {
        switch (mode)
        {
        case GhostMode::Scatter:
            setMode(GhostMode::Chase);
            break;
        case GhostMode::Chase:
            setMode(GhostMode::Scatter);
            break;
        case GhostMode::Frightened:
            setMode(GhostMode::Chase);
            break;
        default:
            setMode(GhostMode::Chase);
            break;
        }
    }


    sf::Vector2f targetPosition = getTargetPosition(pacmanPos);

    if (MoveTo(deltaTime)) {
        currentTile = WrapCoords2(nextTile);

        //choosing direction toward Pacman
        float bestDist = mode == GhostMode::Chase || mode == GhostMode::Scatter ? std::numeric_limits<float>::max() : std::numeric_limits<float>::min();
        Direction bestDir = Direction::None;
        for (auto dir : { Direction::Up, Direction::Down, Direction::Left, Direction::Right }) {
            sf::Vector2f next = currentTile + GetNextTile(dir);
            if (mode == GhostMode::Chase || mode == GhostMode::Scatter) {
                if (CanMoveTo(next) && dir != OppositeDirection(currentMoveDirection)) {
                    float dist = std::abs(next.x - targetPosition.x) + std::abs(next.y - targetPosition.y);
                    if (dist < bestDist) {
                        bestDist = dist;
                        bestDir = dir;
                    }
                }
            }
            else {
                if (CanMoveTo(next) && dir != OppositeDirection(currentMoveDirection)) {
                    float dist = std::abs(next.x - targetPosition.x) + std::abs(next.y - targetPosition.y);
                    if (dist > bestDist) {
                        bestDist = dist;
                        bestDir = dir;
                    }
                }
            }

        }


        if (bestDir != Direction::None) {
            nextTile = currentTile + GetNextTile(bestDir);
            currentMoveDirection = bestDir;
        }
        else {
            nextTile = currentTile; // Stay put
            currentMoveDirection = Direction::None;
        }

        interpolationTime = std::abs(nextTile.x - currentTile.x) + std::abs(nextTile.y - currentTile.y) > 0
            ? blockSize / moveSpeed
            : 0.0f;
        interpolationTimer = 0.0f;
    }
}

void Ghosts::MapSearch()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (maze[i][j] == mapSymbol)
            {
                float x = static_cast<float>(j * blockSize);
                float y = static_cast<float>(i * blockSize);

                currentTile = nextTile = sf::Vector2f{ x, y };

                ghostSprite.setPosition(currentTile);
            }
        }
    }
}

void Ghosts::Draw(sf::RenderWindow& window)
{
    window.draw(ghostSprite);
}

sf::Vector2f Ghosts::GetPosition() const
{
    return ghostSprite.getPosition();
}

Ghosts::Ghosts(const std::string& texturePath, char a)
    : ghostTexture(texturePath), modeTimer(7.f), defaultTexture(ghostTexture),
    ghostSprite(ghostTexture, sf::IntRect{ { 0,0, },{ 32, 32} })
    /*  frightenedTexture("assets/frightened.png"),
      frightenedSprite(frightenedTexture)*/
{
    modeTimer.Start();
    mapSymbol = a;
    MapSearch();
}