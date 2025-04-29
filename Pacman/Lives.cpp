#include "Lives.h"
#include "Constants.h"

sf::Vector2f WrapCoords3(const sf::Vector2f & p)
{
    float sw = static_cast<float>(screenWidth);
    float sh = static_cast<float>(screenHeight);

    return { std::fmod(p.x + sw, sw), std::fmod(p.y + sh, sh) };
}

sf::Vector2i ConvertCoordinates3(sf::Vector2f p)
{

    p = WrapCoords3(p);

    int c = static_cast<int>(p.x) / blockSize;
    int r = static_cast<int>(p.y) / blockSize;

    return sf::Vector2i(c, r);
}

Lives::Lives() : livesTexture("assets/heart.png"), livesSprite(livesTexture) //sf::IntRect{ {300,300}, {42,42} })
{
}

bool Lives::IsAlive(sf::FloatRect& pacman, sf::FloatRect& ghost)
{
    if (pacman.findIntersection(ghost) != std::nullopt)
    {
        return true;
    }
    return false;
}

void Lives::CheckCollision(sf::RenderWindow& window, Pacman& pacman, Ghosts& blinky, Ghosts& pinky, Ghosts& inky, Ghosts& clyde)
{
    for (int i = 0; i < lives; ++i) {
        livesSprite.setPosition(sf::Vector2f(static_cast<float>(545 + (i * blockSize)), static_cast<float>(5)));
        window.draw(livesSprite);
    }

    CheckGhost(pacman, blinky);
    CheckGhost(pacman, pinky);
    CheckGhost(pacman, inky);
    CheckGhost(pacman, clyde);
}

void Lives::CheckGhost(Pacman& pacman, Ghosts& ghost)
{
    if (ghost.GetMode() == GhostMode::Frightened)
        return;

    auto pacBounds = pacman.GetSprite().getGlobalBounds();
    auto ghostBounds = ghost.GetSprite().getGlobalBounds();

    if (IsAlive(pacBounds, ghostBounds))
    {
        --lives;
        if (lives == 0)
        {
            Reset();
        }
    }
}

void Lives::Reset()
{
    lives = 3;
}