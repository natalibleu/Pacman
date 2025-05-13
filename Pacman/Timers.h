#pragma once
#include <SFML/Graphics.hpp>

class Timers
{
public:
	Timers(float duration);
	void SetDuration(float duration);
	void Start();
	void Update(float deltaTime);
	float Time();

private:
	sf::Clock clock;
	float duration = 0.f;
	float timeLeft = 0.f;
	bool running = false;
};

