#include "Ghosts.h"
#include "Map.h"

bool CanMoveTo(sf::Vector2f p)
{
    sf::Vector2i indexes = ConvertCoordinates(p);

    // Grid cells with a # are walls.
    return maze[indexes.x][indexes.y] != '#';
}

void Ghosts::setMode(GhostMode newMode)
{
    // Change the mode of the ghost
    mode = newMode;
    // Reset the timer
    modeTimer.Start();
    // if we are in frightened mode, change the sprite
    if (mode == GhostMode::Frightened) {
        ghostSprite.setTexture(frightenedTexture);
        audio.UpdateSound(LoadAudio::BlueGhosts);
    }
    // else, we set it to default
    else {
        audio.StopBlueGhostSound();
        ghostSprite.setTexture(ghostTexture);
    }
}

void Ghosts::ResetGhost()
{
    setMode(GhostMode::Chase);
    MapSearch();
}


bool Ghosts::MoveTo(float deltaTime)
{
    interpolationTimer += deltaTime;

    if (interpolationTime > 0.0f)
    {
        float t = std::min(1.0f, interpolationTimer / interpolationTime);
        sf::Vector2f newPosition = currentTile + t * (nextTile - currentTile);
        ghostSprite.setPosition(WrapCoords(newPosition));
    }
    return interpolationTimer >= interpolationTime;
}

void Ghosts::UpdateAnimation(float deltaTime)
{
    int currentAnimationPosition = 0; //current section

    switch (currentMoveDirection)
    {
    case MoveDirection::Up:
        currentAnimationPosition = 0;
        break;
    case MoveDirection::Down:
        currentAnimationPosition = 2;
        break;
    case MoveDirection::Left:
        currentAnimationPosition = 4;
        break;
    case MoveDirection::Right:
        currentAnimationPosition = 0;
        break;
    default:
        currentAnimationPosition = 0;
        return;
    }

    if (mode != GhostMode::Frightened) {
        animationTimer += deltaTime;
        if (animationTimer > animationEndTime)
        {
            animationTimer = 0.0f;
            currentFrame = (currentFrame + 1) % 2;
        }
    }
    else {
        //forcing to only one single frame for the frightened
        currentFrame = 0;
        currentAnimationPosition = 0;
    }

    int animationIndex = currentFrame + currentAnimationPosition;
    ghostSprite.setTextureRect(sf::IntRect{ {animationIndex * 36, 0}, {32, 32} });
}

void Ghosts::Move(float deltaTime, const sf::Vector2f& pacmanPos, const sf::Vector2f& ghostPos)
{
    // update the timer of the ghost
    modeTimer.Update(deltaTime);
    // Check the mode timer and adjust the mode if necessary
    // When the timer runs out, the mode changes depending on the setMode()
    if (modeTimer.Time() < 0.f) {
        switch (mode)
        {
        case GhostMode::Scatter:
            setMode(GhostMode::Chase);
            break;
        case GhostMode::Chase:
            setMode(GhostMode::Scatter);
            break;
        case GhostMode::Frightened:
            setMode(GhostMode::Chase);
            break;
        default:
            setMode(GhostMode::Chase);
            break;
        }
    }

    // Gets the specific position that each ghost should target. It's overritten by every type of ghost
    sf::Vector2f targetPosition = getTargetPosition(pacmanPos);

    if (MoveTo(deltaTime)) {
        currentTile = WrapCoords(nextTile);

        //choosing direction toward Pacman
        float bestDist = 0.f;

        if (mode == GhostMode::Chase || mode == GhostMode::Scatter) {
            // We are searching for the Minimum element, thats why we set the current best distance to +infinity
            bestDist = std::numeric_limits<float>::max();
        }
        else {
            // We are searching for the Maximum element, thats why we set the current best distance to -infinity
            bestDist = std::numeric_limits<float>::min();
        }
        MoveDirection bestDir = MoveDirection::None;

        // We loop through each directions to decide which one is best
        for (auto dir : { MoveDirection::Up, MoveDirection::Down, MoveDirection::Left, MoveDirection::Right }) {
            // Gets the next tile based on the chosen direction
            sf::Vector2f next = currentTile + GetNextTile(dir);

            if (CanMoveTo(next) && dir != OppositeDirection(currentMoveDirection)) {

                // Manhattan distance
                float dist = std::abs(next.x - targetPosition.x) + std::abs(next.y - targetPosition.y);

                //// Euclidean distance
                //float x_pow = std::powf(next.x - targetPosition.x, 2);
                //float y_pow = std::powf(next.y - targetPosition.y, 2);
                //float dist = std::sqrtf(x_pow + y_pow);

                if (mode == GhostMode::Chase || mode == GhostMode::Scatter) {
                    if (dist < bestDist) {
                        bestDist = dist;
                        bestDir = dir;
                    }
                }
                else {
                    if (dist > bestDist) {
                        bestDist = dist;
                        bestDir = dir;
                    }
                }
            }

        }

        if (bestDir != MoveDirection::None) {
            nextTile = currentTile + GetNextTile(bestDir);
            currentMoveDirection = bestDir;
        }
        else {
            nextTile = currentTile; // Stay put
            currentMoveDirection = MoveDirection::None;
        }

        if (std::abs(nextTile.x - currentTile.x) + std::abs(nextTile.y - currentTile.y) > 0)
        {
            interpolationTime = blockSize / moveSpeed;
        }
        else
        {
            interpolationTime = 0.0f;
        }

        //we reset it after the loop again
        interpolationTimer = 0.0f;
    }

    UpdateAnimation(deltaTime);
}

void Ghosts::MapSearch()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (maze[i][j] == mapSymbol)
            {
                //we calculate the x and y corresponding to the map position
                float x = static_cast<float>(j * blockSize);
                float y = static_cast<float>(i * blockSize);

                //at first we set the equal as default
                currentTile = nextTile = sf::Vector2f{ x, y };

                ghostSprite.setPosition(currentTile);
            }
        }
    }
}

void Ghosts::Draw(sf::RenderWindow& window)
{
    window.draw(ghostSprite);
}

sf::Vector2f Ghosts::GetPosition() const
{
    return ghostSprite.getPosition();
}

Ghosts::Ghosts(const std::string& texturePath, char a)
    : ghostTexture(texturePath), modeTimer(5.f), frightenedTexture("assets/frightened.png"),
    ghostSprite(ghostTexture, sf::IntRect{ { 0,0, },{ 32, 32} })
{
    modeTimer.Start();
    mapSymbol = a;
    MapSearch();
}