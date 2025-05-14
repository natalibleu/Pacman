#include "Audio.h"

Audio::Audio() 
    :winBuffer("audio/pacman_win.ogg"), deathBuffer("audio/pacman_death.wav"),
    foodBuffer("audio/pacman_chomp.wav"), ghostBuffer("audio/pacman_eatghost.wav"),
    startBuffer("audio/pacman_beginning.wav"), blueGhostBuffer("audio/ghosts_turning_blue.ogg"),
    resetDieBuffer("audio/reset_after_death.flac"), winSound(winBuffer), deathSound(deathBuffer), foodSound(foodBuffer),
    ghostSound(ghostBuffer), startSound(startBuffer), blueGhostSound(blueGhostBuffer), resetDieSound(resetDieBuffer)
{
}

void Audio::UpdateSound(LoadAudio audio)
{
    switch (audio)
    {
    case LoadAudio::Win:
        winSound.play();
        break;
    case LoadAudio::Death:
        deathSound.play();
        break;
    case LoadAudio::EatFood:
        foodSound.play();
        break;
    case LoadAudio::EatGhost:
        ghostSound.play();
        break;
    case LoadAudio::Start:
        startSound.play();
        break;
    case LoadAudio::BlueGhosts:
        blueGhostSound.play();
        break;
    case LoadAudio::ResetDie:
        resetDieSound.play();
        break;
    }
}

void Audio::Reset()
{
    winSound.stop();
    deathSound.stop();
    foodSound.stop();
    ghostSound.stop();
    startSound.stop();
    blueGhostSound.stop();
    resetDieSound.stop();
}

void Audio::StopBlueGhostSound()
{
    blueGhostSound.stop();
}