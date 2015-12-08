#ifndef Player_H_
#define Player_H_

#include "ResourceIdentifiers.h"

#include <PYRO/Text.h>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Player : public sf::Sprite
{
private:
	// Private Struct(s)
	struct Movement {
		bool UP, DOWN, LEFT, RIGHT;
	};
	struct Score {
		unsigned   score;
		pyro::Text text;
	};
private:
	// Private Member(s)
	float		mSpeed;
	Movement	mMovement;
	Score		mScore;

	sf::IntRect mWindowBounds;

private:
	// Private Method(s)
	void falsifyMovement();
	void updateScore();
	void setupScoreProperties(const sf::Font& font);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	// Constructor(s)
	Player(const sf::Texture& texture, const sf::Font& font, sf::IntRect winBounds);
	// Public Method(s)
	void handleEvent(const sf::Event& event);
	void update(sf::Time dt);
};
#endif