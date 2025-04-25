#pragma once
#include <SFML/Graphics.hpp>
#include "Ghosts.h"

enum class MoveDirection
{
    None,
    Up,
    Down,
    Left,
    Right
};

class Pacman
{
private:
    sf::Texture pacmanTexture;
    sf::Sprite pacmanSprite;

    // Pacman's current direction.
    MoveDirection currentMoveDirection = MoveDirection::None;
    // Pacman's desired direction.
    MoveDirection nextMoveDirection = MoveDirection::None;

    // The tile pacman is currently in; representing the beginning position
    sf::Vector2f currentTile;
    // The tile pacman is moving to; representing the target position
    sf::Vector2f nextTile;

    // How long it takes to move between tiles.
    float interpolationTime = 0.0f;
    float interpolationTimer = 0.0f;
    float moveSpeed = 180.0f;

    float animationTimer = 0.0f;
    float animationEndTime = 0.1f; // seconds per frame
    int currentFrame = 0;

    Ghosts* ghosts[4];

    void UpdateAnimation(float deltaTime);

    // Move pacman towards the next tile.
    // Return true if pacman reached the next tile.
    bool MoveTo(float deltaTime);

public:
    void SetGhosts(Ghosts& blinky, Ghosts& pinky, Ghosts& inky, Ghosts& clyde);
    void EatFruits(sf::Vector2f p);
    bool HasEatenFruit(sf::Vector2f p);
    Ghosts* HasEatenGhost(sf::Vector2f p);
    void EatEnergizer(sf::Vector2f p);
    bool HasEatenEnergizer(sf::Vector2f p);
    void EatGhost(Ghosts* ghost);
    bool Move(float deltaTime);
    sf::Vector2f GetPosition();
    void DrawPacman(sf::RenderWindow& window);
    void Reset();
    void Die();
    Pacman();
};