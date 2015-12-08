#include "StarManager.h"

// Constructor(s)
	// Constructor 1
StarManager::StarManager(sf::IntRect winBounds)
	: VertexArray(sf::Triangles)
	, mWindowBounds(winBounds)
{
	spawnStars();
}

// Private Method(s)
	// Setup Star
void StarManager::setupStar(sf::Vertex& v1, sf::Vertex& v2, sf::Vertex& v3)
{
	// Position
	float maxSize = 1.5f,
		  minSize = 0.55f;

	float radius = (rand() / (RAND_MAX / (maxSize - minSize)) + minSize);

	sf::FloatRect positions(mWindowBounds.left,
							mWindowBounds.top - mWindowBounds.height,
							mWindowBounds.width - radius * 2,
							mWindowBounds.top - radius * 2);

	v1.position = sf::Vector2f(rand() / (RAND_MAX / (positions.width - positions.left)) + positions.left,
							   rand() / (RAND_MAX / (positions.height - positions.top)) + positions.top);

	v2.position = v1.position + sf::Vector2f(radius, 0.f);
	v3.position = v1.position + sf::Vector2f(radius / 2.f, radius);

	// Color
	v1.color = sf::Color(rand() % 255, rand() % 255, rand() % 255);
	v2.color =
	v3.color = sf::Color::White;
}
	// Spawn Stars
void StarManager::spawnStars()
{
	for (int i = 0; i < 500; i++) 
	{
		append(sf::Vertex());
		append(sf::Vertex());
		append(sf::Vertex());

		int j = getVertexCount();
		setupStar((*this)[j - 1], (*this)[j - 2], (*this)[j - 3]);
	}
}
	// Reposition Stars
void StarManager::repositionStars()
{
	for (unsigned i = 0; i < getVertexCount(); i += 3)
		if ((*this)[i].position.y > mWindowBounds.height)
			setupStar((*this)[i], (*this)[i + 1], (*this)[i + 2]);
}

// Public Method(s)
	// Update
void StarManager::update(sf::Time dt)
{
	for (unsigned i = 0; i < getVertexCount(); i += 3)
	{
		float speed = 50 * std::abs((*this)[i].position.x - (*this)[i + 1].position.x);
		for (int j = i; j < i + 3; j++)
			(*this)[j].position.y += speed * dt.asSeconds();
	}

	repositionStars();
}