#include <SFML/Graphics.hpp>
#include "Game.h"


Game::Game()
{
    pacman.SetGhosts(blinky, pinky, inky, clyde);

}

void Game::Update(sf::RenderWindow& window, sf::Time& elapsedTime)
{
    //implementing functions
    if (!pacman.Move(elapsedTime.asSeconds()))
        Reset();
    blinky.Move(elapsedTime.asSeconds(), blinky.getTargetPosition(pacman.GetPosition()));
    pinky.Move(elapsedTime.asSeconds(), pinky.getTargetPosition(pacman.GetPosition()));
    clyde.Move(elapsedTime.asSeconds(), clyde.getTargetPosition(pacman.GetPosition()));
    inky.Move(elapsedTime.asSeconds(), inky.getTargetPosition(pacman.GetPosition()));
    window.clear();
    map.DrawMap(0, 0, window);
    pellet.DrawPellets(window);
    energizer.DrawEnergizer(window);
    pacman.DrawPacman(window);
    blinky.Draw(window);
    pinky.Draw(window);
    inky.Draw(window);
    clyde.Draw(window);

    score.UpdateScore(window);
    lives.CheckCollision(window, pacman, blinky, pinky, inky, clyde);

    window.display();
}

void Game::Reset()
{
    if (lives.GetLives() == 0)
    {
        blinky.ResetGhost();
        inky.ResetGhost();
        pinky.ResetGhost();
        clyde.ResetGhost();

        pacman.Reset();
        score.Reset();
        lives.Reset();

        map.Reset();
    }
}