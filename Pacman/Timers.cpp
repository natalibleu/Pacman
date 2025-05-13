#include "Timers.h"

Timers::Timers(float duration)
{
	this->duration = duration;
}

void Timers::SetDuration(float duration)
{
	this->duration = duration;
}

// Resets the timer and starts it
void Timers::Start()
{
	timeLeft = duration;
	running = true;
}

// Updates the timer by passed time (deltaTime)
void Timers::Update(float deltaTime)
{
	timeLeft -= deltaTime;
}

// Returns the time left
float Timers::Time()
{
	return timeLeft;
}