#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

enum class LoadAudio
{
    Win,
    Death,
    EatFood,
    EatGhost,
    Start,
    BlueGhosts,
    ResetDie,
    Music
};

class Audio
{
private:
    sf::SoundBuffer winBuffer;
    sf::SoundBuffer deathBuffer;
    sf::SoundBuffer foodBuffer;
    sf::SoundBuffer ghostBuffer;
    sf::SoundBuffer startBuffer;
    sf::SoundBuffer blueGhostBuffer;
    sf::SoundBuffer resetDieBuffer;

    sf::Sound winSound;
    sf::Sound deathSound;
    sf::Sound foodSound;
    sf::Sound ghostSound;
    sf::Sound startSound;
    sf::Sound blueGhostSound;
    sf::Sound resetDieSound;

public:
    void UpdateSound(LoadAudio audio);
    void Reset();
    void StopBlueGhostSound();
    Audio();
};