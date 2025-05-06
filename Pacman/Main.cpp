#include "Game.h"
#include <SFML/Graphics.hpp>

int main()
{
    //creating a window
    sf::RenderWindow window(sf::VideoMode({ 672,672 }), "Pacman");

    sf::Clock clock;
    sf::Music music;
    if (!music.openFromFile("audio/background_music.ogg")) {
        return -1;
    }

    music.play();

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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {

            game.isRunning = true;
            game.showText = false;
        }

        sf::Time elapsedTime = clock.restart();

        game.Update(window, elapsedTime);
    }
}