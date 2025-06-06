#pragma once
#include "SFML/Graphics.hpp"

//grid
inline int blockSize = 32;

inline int screenHeight = 672;
inline int screenWidth = 672;

enum class MoveDirection
{
    None,
    Up,
    Down,
    Left,
    Right
};

static sf::Vector2f WrapCoords(const sf::Vector2f& p) //ensures the entity stays within the screen
{
    float sw = static_cast<float>(screenWidth);
    float sh = static_cast<float>(screenHeight);

    //modulus division between two numbers: the position after adding the sw/sh and sw/sh themselves
    return { std::fmod(p.x + sw, sw), std::fmod(p.y + sh, sh) }; //returns the pixel position of the entity
}

static sf::Vector2i ConvertCoordinates(sf::Vector2f p)
{
    p = WrapCoords(p);

    //gets the result from the WrapCoords and converts it in map blocks
    int c = static_cast<int>(p.x) / blockSize;
    int r = static_cast<int>(p.y) / blockSize;

    return sf::Vector2i{ r,c };
}

static sf::Vector2f GetNextTile(MoveDirection dir) //gives the offset for that direction the "dir" is set up to
{
    switch (dir)
    {
    case MoveDirection::None:
        return { 0, 0 };
    case MoveDirection::Up:
        return { 0, -32 };
    case MoveDirection::Down:
        return { 0, 32 };
    case MoveDirection::Left:
        return { -32, 0 };
    case MoveDirection::Right:
        return { 32, 0 };
    }

    return { 0, 0 };
}

static MoveDirection OppositeDirection(MoveDirection dir) //this returns the opposite of the last direction that I have been in
{
    switch (dir) {
    case MoveDirection::Up: return MoveDirection::Down;
    case MoveDirection::Down: return MoveDirection::Up;
    case MoveDirection::Left: return MoveDirection::Right;
    case MoveDirection::Right: return MoveDirection::Left;
    default: return MoveDirection::None;
    }
}