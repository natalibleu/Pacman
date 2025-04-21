#include "Timers.h"

Timers::Timers()
{
}

void Timers::ScatterTimer(float seconds)
{
    duration = seconds;
    clock.restart();
    running = true;
}

void Timers::FrightenedTimer(float seconds)
{
    duration = seconds;
    clock.restart();
    running = true;
}

float Timers::ScatterTimeLeft() const {
    return std::max(0.f, duration - clock.getElapsedTime().asSeconds());
}

float Timers::FrightenedTimeLeft() const {
    return std::max(0.f, duration - clock.getElapsedTime().asSeconds());
}