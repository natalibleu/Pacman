#pragma once
#include "SFML/Graphics.hpp"

//grid
inline int blockSize = 32;

inline int screenHeight = 672;
inline int screenWidth = 672;

static sf::Vector2f WrapCoords(const sf::Vector2f& p)
{
    float sw = static_cast<float>(screenWidth);
    float sh = static_cast<float>(screenHeight);

    return { std::fmod(p.x + sw, sw), std::fmod(p.y + sh, sh) };
}

static sf::Vector2i ConvertCoordinates(sf::Vector2f p)
{
    p = WrapCoords(p);

    int c = static_cast<int>(p.x) / blockSize;
    int r = static_cast<int>(p.y) / blockSize;

    return sf::Vector2i{ r,c };
}
