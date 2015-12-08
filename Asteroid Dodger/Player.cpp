#include "Player.h"

#include <SFML/Graphics/RenderTarget.hpp>

// Constructor(s)
	// Constructor 1
Player::Player(const sf::Texture& texture, const sf::Font& font, sf::IntRect winBounds)
	: Sprite(texture)
	, mSpeed(350.f)
	, mWindowBounds(winBounds)
{
	mMovement.UP = mMovement.DOWN = mMovement.LEFT = mMovement.RIGHT = false;

	setupScoreProperties(font);
}

// Private Method(s)
	// Falsify Movement
void Player::falsifyMovement()
{
	sf::FloatRect bounds(getGlobalBounds());

	if (bounds.left <= mWindowBounds.left)
		mMovement.LEFT = false;
	else if (bounds.left + bounds.width >= mWindowBounds.left + mWindowBounds.width)
		mMovement.RIGHT = false;

	if (bounds.top <= mWindowBounds.top)
		mMovement.UP = false;
	else if (bounds.top + bounds.height >= mWindowBounds.top + mWindowBounds.height)
		mMovement.DOWN = false;
}
	// Update Score
void Player::updateScore()
{
	mScore.text.setString(std::to_string(mScore.score += 1));
}
	// Setup Score Properties
void Player::setupScoreProperties(const sf::Font& font)
{
	mScore.score = 0;
	mScore.text.setFont(font);
	mScore.text.setString(std::to_string(mScore.score));
	mScore.text.setColor(sf::Color::White);
	mScore.text.setCharacterSize(55);
	mScore.text.setOrigin(sf::Vector2f(0.f, 0.f));
	mScore.text.setPosition(mWindowBounds.left + 30.f,	
							mWindowBounds.height - mScore.text.getGlobalBounds().height - 30.f);
}
	// Draw
void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(static_cast<sf::Sprite>(*this), states);
	target.draw(mScore.text, states);
}

// Public Method(s)
	// Handle Event
void Player::handleEvent(const sf::Event& event)
{
	bool state;
	if (event.type == sf::Event::KeyPressed)
		state = true;
	else if (event.type == sf::Event::KeyReleased)
		state = false;
	else
		return;

	switch (event.key.code)
	{
	case sf::Keyboard::W:
		mMovement.UP = state;
		break;
	case sf::Keyboard::S:
		mMovement.DOWN = state;
		break;
	case sf::Keyboard::A:
		mMovement.LEFT = state;
		break;
	case sf::Keyboard::D:
		mMovement.RIGHT = state;
		break;
	}
}
	// Update
void Player::update(sf::Time dt)
{
	falsifyMovement();
	updateScore();

	sf::Vector2f movement(0.f, 0.f);

	if (mMovement.UP)
		movement.y -= mSpeed;
	if (mMovement.DOWN)
		movement.y += mSpeed;
	if (mMovement.LEFT)
		movement.x -= mSpeed;
	if (mMovement.RIGHT)
		movement.x += mSpeed;

	move(movement * dt.asSeconds());
}