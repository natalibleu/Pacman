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
    // Save current mode if switching to Frightened
    if (newMode == GhostMode::Frightened && mode != GhostMode::Frightened) {
        prevMode = mode;
    }
    mode = newMode;
}

void Ghosts::Update()
{
    switch (mode)
    {
    case GhostMode::Scatter:
        break;
    case GhostMode::Chase:
        break;
    //case GhostMode::Frightened:
    //    ghostSprite = frightenedSprite;
    //    break;
    }
}

//void Ghosts::PacmanEatsEnergizer(std::vector<Ghosts>& ghosts, Timers& frightenedTimer, float frightenedDuration, Pacman& pacman) 
//{
//    frightenedTimer.FrightenedTimer(frightenedDuration);
//
//    for (auto& ghost : ghosts) 
//    {
//        ghost.setMode(GhostMode::Frightened);
//    }
//
//    std::cout << "Ghosts are frightened!" << std::endl;
//
//    if (pacman.hasEatenEnergizer) {
//        PacmanEatsEnergizer(ghosts, frightenedTimer, 7.f); // 7 seconds of frightened mode
//    }
//}

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

    sf::Vector2f targetPosition = getTargetPosition(pacmanPos);

    if (MoveTo(deltaTime)) {
        currentTile = WrapCoords2(nextTile);

        //choosing direction toward Pacman
        float bestDist = std::numeric_limits<float>::max();
        Direction bestDir = Direction::None;
        for (auto dir : { Direction::Up, Direction::Down, Direction::Left, Direction::Right }) {
            sf::Vector2f next = currentTile + GetNextTile(dir);
            if (CanMoveTo(next) && dir != OppositeDirection(currentMoveDirection)) {
                float dist = std::abs(next.x - targetPosition.x) + std::abs(next.y - targetPosition.y);
                if (dist < bestDist) {
                    bestDist = dist;
                    bestDir = dir;
                }
            }
        }

        if (mode == GhostMode::Frightened) {

            bestDir = OppositeDirection(bestDir);
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

void Ghosts::MapSearch(char a, sf::Sprite& sprite)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (maze[i][j] == a)
            {
                float x = static_cast<float>(j * blockSize);
                float y = static_cast<float>(i * blockSize);

                currentTile = nextTile = sf::Vector2f{ x, y };

                sprite.setPosition(currentTile);
            }
        }
    }
}

void Ghosts::Draw(sf::RenderWindow& window)
{
    window.draw(ghostSprite);
}

sf::Vector2f Ghosts::getPosition() const
{
    return ghostSprite.getPosition();
}

bool Ghosts::Scatter()
{
    return false;
}

Ghosts::Ghosts(const std::string& texturePath, char a)
    : ghostTexture(texturePath), 
    ghostSprite(ghostTexture, sf::IntRect{ { 0,0, },{ 32, 32} })
  /*  frightenedTexture("assets/frightened.png"), 
    frightenedSprite(frightenedTexture)*/
{
    MapSearch(a, ghostSprite);
}
