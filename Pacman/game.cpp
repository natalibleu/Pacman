#include "Map.h"
#include "Pacman.h"
#include "Pellets.h"
#include "Energizer.h"
#include "Score.h"
#include "Blinky.h"
#include "Pinky.h"
#include "Inky.h"
#include "Clyde.h"
#include "Ghosts.h"

#include <SFML/Graphics.hpp>

int main()
{
    //creating a window
    sf::RenderWindow window(sf::VideoMode({ 672,672 }), "Pacman");

    sf::Clock clock;

    //speed of pacman
    //window.setFramerateLimit(200);

    //making the objects
    Map map;
    Score score;
    Pacman pacman;
    Pellets pellet;
    Energizer energizer;
    Blinky blinky;
    Pinky pinky;
    Inky inky;
    Clyde clyde;

    pacman.SetGhosts(blinky, pinky, inky, clyde);

    //keeping the window on
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        sf::Time elapsedTime = clock.restart();

        //implementing functions
        pacman.Move(elapsedTime.asSeconds());
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

        window.display();
    }
}