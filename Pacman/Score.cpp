#include "Score.h"


int currentScore = 0;


Score::Score() : font("fonts/pacmanFont.ttf"), text(font)
{
}

void Score::UpdateScore(sf::RenderWindow& window)
{
	std::string score_text = "Score:" + std::to_string(currentScore);
	text.setString(score_text);
	text.setCharacterSize(24);
	window.draw(text);
}

void Score::Reset()
{
	currentScore = 0;
}