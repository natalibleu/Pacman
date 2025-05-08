#pragma once
#include <SFML/Graphics.hpp>
#include "Timers.h"
#include "Audio.h"
#include "Constants.h"


enum class GhostMode
{
    Scatter,
    Chase,
    Frightened
};

class Ghosts
{
private:
    //sf::Texture frightenedTexture;
    //sf::Sprite frightenedSprite;

    // Ghost's current direction.
    MoveDirection currentMoveDirection = MoveDirection::None;
    // Ghost's desired direction.
    MoveDirection nextMoveDirection = MoveDirection::None;

    // The tile ghost is currently in.
    sf::Vector2f currentTile;
    // The tile ghost is moving to.
    sf::Vector2f nextTile;

    Audio audio;

    float interpolationTime = 0.0f;
    float interpolationTimer = 0.0f;
    float moveSpeed = 150.0f;

    float animationTimer = 0.0f;
    float animationEndTime = 0.1f; // Animation frame duration
    int currentFrame = 0;

    bool scatterMode = false;

protected:
    sf::Texture ghostTexture;
    sf::Sprite ghostSprite;

    char mapSymbol;

    sf::Texture frightenedTexture;

    GhostMode mode = GhostMode::Chase;
    Timers modeTimer;

    Ghosts(const std::string& texturePath, char a);

public:
    void Move(float deltaTime, const sf::Vector2f& pacmanPos, const sf::Vector2f& ghostPos = { 0.f, 0.f });
    bool MoveTo(float deltaTime);
    void MapSearch();
    void UpdateAnimation(float deltaTime);
    void Draw(sf::RenderWindow& window);
    virtual sf::Vector2f getTargetPosition(const sf::Vector2f& pacmanPos) = 0;
    sf::Vector2f GetPosition() const; // Returns ghost position in pixels
    GhostMode GetMode() { return mode; }
    sf::Sprite GetSprite() { return ghostSprite; }
    void setMode(GhostMode newMode);
    void ResetGhost();
};