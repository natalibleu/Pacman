#include <SFML/Graphics.hpp>
#include "Game.h"
#include <iostream>


Game::Game()
{
    pacman.SetGhosts(blinky, pinky, inky, clyde);

}

void Game::Update(sf::RenderWindow& window, sf::Time& elapsedTime)
{
    window.clear();
    map.DrawMap(0, 0, window);
    pellet.DrawPellets(window);
    energizer.DrawEnergizer(window);
    blinky.Draw(window);
    pinky.Draw(window);
    inky.Draw(window);
    clyde.Draw(window);

    if (isRunning)
    {
        //Only updating movement if game is running
        pacman.Move(elapsedTime.asSeconds());
        blinky.Move(elapsedTime.asSeconds(), blinky.getTargetPosition(pacman.GetPosition()));
        pinky.Move(elapsedTime.asSeconds(), pinky.getTargetPosition(pacman.GetPosition()));
        clyde.Move(elapsedTime.asSeconds(), clyde.getTargetPosition(pacman.GetPosition()));
        inky.Move(elapsedTime.asSeconds(), inky.getTargetPosition(pacman.GetPosition()));

        score.UpdateScore(window);
        lives.CheckCollision(window, pacman, blinky, pinky, inky, clyde);
        CheckLives();
        CheckWin(elapsedTime);
    }
    else
    {
        //just load the ending animation and freeze all game updates
        pacman.EndingAnimation(elapsedTime.asSeconds());
    }

    pacman.DrawPacman(window);
    window.display();
}

void Game::Reset()
{
    blinky.ResetGhost();
    inky.ResetGhost();
    pinky.ResetGhost();
    clyde.ResetGhost();

    pacman.Reset();
    score.Reset();
    lives.Reset();

    isRunning = true;

    pacman.eatenPellets = 0;
    pacman.eatenEnergizers = 0;

    map.Reset();
}

void Game::CheckLives()
{
    if (lives.GetLives() <= 0)
    {
        Reset();
    }
}

void Game::CheckWin(sf::Time& elapsedTime)
{
    if (pacman.eatenPellets + pacman.eatenEnergizers >= 150)
    {
        isRunning = false;
        std::cout << "You won" << std::endl;
    }
}