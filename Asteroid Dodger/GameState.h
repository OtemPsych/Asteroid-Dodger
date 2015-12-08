#ifndef GameState_H_
#define GameState_H_

#include "ResourceIdentifiers.h"
#include "Player.h"
#include "StarManager.h"
#include "Asteroid.h"

#include <PYRO/State.h>
#include <PYRO/ResourceTypedefs.h>
#include <PYRO/CollisionHandler.h>
#include <PYRO/MusicPlayer.h>

class GameState : public pyro::State
{
private:
	// Private Member(s)
	pyro::TextureHolder<Texture::ID> mTextures;
	pyro::FontHolder<Font::ID>	     mFonts;

	sf::RenderWindow&				 mWindow;
	sf::IntRect						 mWindowBounds;

	std::unique_ptr<Player>			 mPlayer;
	std::vector<Asteroid>			 mAsteroids;
	StarManager						 mStarManager;

	pyro::CollisionHandler			 mCollisionHandler;

	pyro::MusicPlayer<Music::ID>	 mMusicPlayer;

private:
	// Private Method(s)
	void handleAsteroids();
	void setupResources();
public:
	// Constructor(s)
	GameState(pyro::StateStack& stack, sf::RenderWindow& window);
	// Public Method(s)
	virtual bool handleEvent(const sf::Event& event);
	virtual bool update(sf::Time dt);
	virtual void draw();
};
#endif