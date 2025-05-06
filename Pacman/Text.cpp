#include "Text.h"

Text::Text() : font("fonts/pacmanFont.ttf"), text(font)
{
}

sf::Vector2f round(const sf::Vector2f vector)
{
    return sf::Vector2f{ std::round(vector.x), std::round(vector.y) };
}

void Text::WinningText(sf::RenderWindow& window)
{
    std::string reset_text = "Press 'R' to reset the game.";
    std::string winning_text = "        ! YOU WON !\n";
    text.setString(winning_text + reset_text);
    text.setCharacterSize(18);
    auto center = text.getGlobalBounds().size / 2.f;
    auto localBounds = center + text.getLocalBounds().position;
    auto rounded = round(localBounds);
    text.setOrigin(rounded);
    text.setPosition(sf::Vector2f{ window.getSize() / 2u });
    window.draw(text);
}

void Text::LosingText(sf::RenderWindow& window)
{
    std::string reset_text = "Press 'R' to play again.";
    std::string losing_text = "      ! YOU LOST !\n";
    text.setString(losing_text + reset_text);
    text.setCharacterSize(18);
    auto center = text.getGlobalBounds().size / 2.f;
    auto localBounds = center + text.getLocalBounds().position;
    auto rounded = round(localBounds);
    text.setOrigin(rounded);
    text.setPosition(sf::Vector2f{ window.getSize() / 2u });
    window.draw(text);
}

void Text::StartGame(sf::RenderWindow& window)
{
    std::string start_text = "Press 'S' to start the game.";
    text.setString(start_text);
    text.setCharacterSize(20);
    auto center = text.getGlobalBounds().size / 2.f;
    auto localBounds = center + text.getLocalBounds().position;
    auto rounded = round(localBounds);
    text.setOrigin(rounded);
    text.setPosition(sf::Vector2f{ window.getSize() / 2u });
    window.draw(text);
}