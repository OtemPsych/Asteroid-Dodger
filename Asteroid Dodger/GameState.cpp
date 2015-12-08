#include "GameState.h"

// Constructor(s)
	// Constructor 1
GameState::GameState(pyro::StateStack& stack, sf::RenderWindow& window)
	: State(stack, window)
	, mWindow(window)
	, mWindowBounds(window.getPosition().x, window.getPosition().y, window.getSize().x, window.getSize().y)
	, mPlayer(nullptr)
	, mStarManager(sf::IntRect(mWindowBounds.left, mWindowBounds.top + mWindowBounds.height,
							   mWindowBounds.width, mWindowBounds.height))
{
	setupResources();
	mStarManager.setWindowBounds(mWindowBounds);

	mPlayer = std::unique_ptr<Player>(new Player(mTextures.get(Texture::Player), mFonts.get(Font::GameFont), 
												 mWindowBounds));
	mPlayer->setPosition(window.getSize().x / 2.f - mPlayer->getGlobalBounds().width / 2.f,
						 window.getSize().y - mPlayer->getGlobalBounds().height / 2.f - 150.f);
	mPlayer->scale(0.65f, 0.65f);

	mMusicPlayer.play(Music::GameTheme);
}

// Private Method(s)
	// Handle Asteroids
void GameState::handleAsteroids()
{
	if (mAsteroids.size() < 35)
		mAsteroids.push_back(Asteroid(mTextures.get(Texture::AsteroidMap), mWindowBounds));

	for (unsigned i = 0; i < mAsteroids.size(); i++)
		if (mAsteroids[i].getPosition().y - mAsteroids[i].getGlobalBounds().width > mWindowBounds.height)
			mAsteroids.erase(mAsteroids.begin() + i);
}
	// Setup Resources
void GameState::setupResources()
{
	mTextures.load(Texture::Player, "Assets/Textures/SpaceshipO.png");
	mTextures.load(Texture::AsteroidMap, "Assets/Textures/AsteroidMap.png");

	mFonts.load(Font::GameFont, "Assets/Fonts/Xrebron.ttf");

	mMusicPlayer.loadTheme(Music::GameTheme, "Assets/Music/SpaceTheme1.wav");
}

// Public Method(s)
	// Handle Event
bool GameState::handleEvent(const sf::Event& event)
{
	mPlayer->handleEvent(event);
	return true;
}
	// Update
bool GameState::update(sf::Time dt)
{
	mStarManager.update(dt);

	for (auto& asteroid : mAsteroids)
		asteroid.update(dt);
	handleAsteroids();

	mPlayer->update(dt);

	for (auto& asteroid : mAsteroids)
		if (mCollisionHandler.checkCollision(*mPlayer, asteroid, true))
			mWindow.close();

	return true;
}
	// Draw
void GameState::draw()
{
	mWindow.draw(mStarManager);

	for (const auto& asteroid : mAsteroids)
		mWindow.draw(asteroid);

	mWindow.draw(*mPlayer);
}