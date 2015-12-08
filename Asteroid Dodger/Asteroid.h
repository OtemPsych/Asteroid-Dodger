#ifndef Asteroid_H_
#define Asteroid_H_

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Asteroid : public sf::Sprite
{
private:
	// Private Member(s)
	float mSpeed;

private:
	// Private Method(s)
	void setupProperties(const sf::Texture& texture, sf::IntRect winBounds);
public:
	// Constructor(s)
	Asteroid(const sf::Texture& texture, sf::IntRect winBounds);
	// Public Method(s)
	void update(sf::Time dt);
};
#endif