#include "Map.h"
#include "Energizer.h"
#include "Constants.h"

void Energizer::DrawEnergizer(sf::RenderWindow& window)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (maze[i][j] == 'o')
			{

				//depending on the j and i we calculate the pixel coordinates the sprite should be in
				float x = static_cast<float>(j * blockSize);
				float y = static_cast<float>(i * blockSize);

				energizerSprite.setPosition(sf::Vector2f(x, y));
				window.draw(energizerSprite);
			}
		}
	}
}

Energizer::Energizer() : energizerTexture("assets/energizer.png"), energizerSprite(energizerTexture)
{
}
