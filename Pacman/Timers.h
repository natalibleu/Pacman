#pragma once
#include <SFML/Graphics.hpp>

class Timers
{
private:
	sf::Clock clock;
	float duration = 0.f;
	float timeLeft = 0.f;
	bool running = false;

public:
	Timers(float _duration);
	void SetDuration(float _duration);
	void Start();
	void Update(float deltaTime);
	float Time();

};

