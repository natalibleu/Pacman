#include "Game.h"
#include <SFML/Graphics.hpp>

int main()
{
    //creating a window
    sf::RenderWindow window(sf::VideoMode({ 672,672 }), "Pacman");

    sf::Clock clock;

    Game game;

    //keeping the window on
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
            game.Reset();

        sf::Time elapsedTime = clock.restart();

        game.Update(window, elapsedTime);
    }
}