#include "Asteroid.h"

#include <SFML/Graphics/Texture.hpp>

// Constructor(s)
	// Constructor 1
Asteroid::Asteroid(const sf::Texture& texture, sf::IntRect winBounds)
{
	setupProperties(texture, winBounds);
}

// Private Method(s)
	// Setup Properties
void Asteroid::setupProperties(const sf::Texture& texture, sf::IntRect winBounds)
{
	sf::Vector2f textureSize(texture.getSize());
	sf::Vector2f asteroidTextureSize(textureSize.x / 8, textureSize.y / 8);

	int randX, randY;
	do {
		randX = rand() % 8;
		randY = rand() % 8;
	} while ((randX == 6 || randX == 7) && randY == 7);

	setTextureRect(sf::IntRect(randX* asteroidTextureSize.x, randY * asteroidTextureSize.y,
							   asteroidTextureSize.x, asteroidTextureSize.y));
	setTexture(texture);

	float maxScale = 1.8f,
		  minScale = 0.5f;
	float scaleFactor = rand() / (RAND_MAX / (maxScale - minScale)) + minScale;
	scale(scaleFactor, scaleFactor);

	float maxSpeed = 350.f,
		  minSpeed = 150.f;
	mSpeed = rand() / (RAND_MAX / (maxSpeed - minSpeed)) + minSpeed;
	
	sf::FloatRect positions(winBounds.left + asteroidTextureSize.x / 2,
							winBounds.top - winBounds.height / 2.f,
							winBounds.width - asteroidTextureSize.x / 2,
							winBounds.top - asteroidTextureSize.y);
	setPosition(rand() / (RAND_MAX / (positions.width - positions.left)) + positions.left,
				rand() / (RAND_MAX / (positions.height - positions.top)) + positions.top);

	auto bounds = getLocalBounds();
	setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

// Public Method(s)
	// Update
void Asteroid::update(sf::Time dt)
{
	move(0.f, mSpeed * dt.asSeconds());
}