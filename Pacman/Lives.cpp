#include "Lives.h"
#include "Constants.h"

bool between(float x, float y, float z)
{
    if (x >= y && x < z)
    {
        return true;
    }
    return false;
}

Lives::Lives() : livesTexture("assets/heart.png"), livesSprite(livesTexture) //sf::IntRect{ {300,300}, {42,42} })
{
}

bool Lives::IsColliding(sf::FloatRect& pacman, sf::FloatRect& ghost)
{
    sf::Vector2f ghostCenter = ghost.getCenter();
    sf::Vector2f pacmanCenter = pacman.getCenter();

    if (between(pacmanCenter.x, ghostCenter.x - 8, ghostCenter.x + 8) && between(pacmanCenter.y, ghostCenter.y - 8, ghostCenter.y + 8))
    {
        return true;
    }
    return false;
}

void Lives::CheckCollision(sf::RenderWindow& window, Pacman& pacman, Audio& audio, Ghosts& blinky, Ghosts& pinky, Ghosts& inky, Ghosts& clyde)
{
    for (int i = 0; i < lives; ++i)
    {
        livesSprite.setPosition(sf::Vector2f(static_cast<float>(545 + (i * blockSize)), static_cast<float>(5)));
        window.draw(livesSprite);
    }

    CheckGhost(pacman, blinky, audio);
    CheckGhost(pacman, pinky, audio);
    CheckGhost(pacman, inky, audio);
    CheckGhost(pacman, clyde, audio);
}

void Lives::CheckGhost(Pacman& pacman, Ghosts& ghost, Audio& audio)
{
    auto pacBounds = pacman.GetSprite().getGlobalBounds();
    auto ghostBounds = ghost.GetSprite().getGlobalBounds();
    if (IsColliding(pacBounds, ghostBounds))
    {
        if (ghost.GetMode() == GhostMode::Frightened)
        {
            pacman.EatGhost(&ghost);
            return;
        }
        lives--;
        pacman.Reset();
        pacman.ResetGhosts();
        audio.UpdateSound(LoadAudio::EatGhost);
    }
}

void Lives::Reset()
{
    lives = 3;
}