#include <SFML/Graphics.hpp>
#include "Game.h"

Game::Game()
{
    pacman.SetGhosts(blinky, pinky, inky, clyde);
}

void Game::Draw(sf::RenderWindow& window)
{
    window.clear();

    map.DrawMap(0, 0, window);
    score.Draw(window);
    lives.Draw(window);
    pellet.DrawPellets(window);
    energizer.DrawEnergizer(window);
    blinky.Draw(window);
    pinky.Draw(window);
    inky.Draw(window);
    clyde.Draw(window);

    if (showText)
    {
        text.StartGame(window);
    }
    else if (gameWon)
    {
        text.WinningText(window);
    }
    else if (killed)
    {
        text.LosingText(window);
    }

    pacman.DrawPacman(window);
    window.display();
}

void Game::Update(sf::Time& elapsedTime)
{

    if (isRunning)
    {
        //Only updating movement if game is running
        pacman.Move(elapsedTime.asSeconds());
        blinky.Move(elapsedTime.asSeconds(), blinky.getTargetPosition(pacman.GetPosition()));
        pinky.Move(elapsedTime.asSeconds(), pinky.getTargetPosition(pacman.GetPosition()));
        clyde.Move(elapsedTime.asSeconds(), clyde.getTargetPosition(pacman.GetPosition()));
        inky.Move(elapsedTime.asSeconds(), inky.getTargetPosition(pacman.GetPosition()));

        score.UpdateScore();

        lives.CheckCollision(pacman, audio, blinky, pinky, inky, clyde);

        CheckLives();

        CheckWin();
    }
    else if (gameWon)
    {
        //just load the ending animation and freeze all game updates
        pacman.EndingAnimation(elapsedTime.asSeconds());
    }
    else if (killed)
    {
        pacman.EndingAnimation(elapsedTime.asSeconds());
    }
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

    audio.Reset();

    isRunning = true;
    killed = false;
    gameWon = false;
    showText = false;

    map.Reset();
}

void Game::CheckLives()
{
    if (lives.GetLives() <= 0)
    {
        isRunning = false;
        killed = true;
        audio.UpdateSound(LoadAudio::ResetDie);
    }
}

void Game::CheckWin()
{
    if (pacman.eatenPellets + pacman.eatenEnergizers >= 150)
    {
        isRunning = false;
        gameWon = true;
        audio.StopBlueGhostSound();
        audio.UpdateSound(LoadAudio::Win);
    }
}