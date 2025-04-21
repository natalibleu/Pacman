#pragma once
#include <SFML/Graphics.hpp>

class Timers
{
private:
	sf::Clock clock;
	float duration = 0.f;
	bool running = false;

public:
	Timers();
	void ScatterTimer(float seconds);
	void FrightenedTimer(float seconds);
	bool IsScatterOn() const { return running; } 
	bool IsFrightenedOn() const { return running; }
	float ScatterTimeLeft() const;
	float FrightenedTimeLeft() const;
};

