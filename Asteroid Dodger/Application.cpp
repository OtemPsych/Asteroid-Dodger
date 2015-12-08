#include "Application.h"

#include "GameState.h"

#include <SFML/Window/Event.hpp>

// Constructor(s)
	// Default
Application::Application()
	: mWindow(sf::VideoMode::getDesktopMode(), "Asteroid Dodger",
			  sf::Style::Close | sf::Style::Fullscreen, sf::ContextSettings(0, 0, 16))
	, mStateStack(mWindow)
{
	mWindow.setFramerateLimit(60);
	mWindow.setMouseCursorVisible(false);

	registerStates();

	mStateStack.pushState(pyro::StateID::Game);
}

// Private Method(s)
	// Process Input
void Application::processInput()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		mStateStack.handleEvent(event);

		if (mStateStack.isEmpty() || (event.type == sf::Event::KeyPressed 
									  && event.key.code == sf::Keyboard::Escape))
			mWindow.close();
	}
}
	// Update
void Application::update(sf::Time dt)
{
	mStateStack.update(dt);
}
	// Render
void Application::render()
{
	mWindow.clear();
	mStateStack.draw();
	mWindow.display();
}
	// Register States
void Application::registerStates()
{
	mStateStack.registerState<GameState>(pyro::StateID::Game);
}

// Public Method(s)
	// Run
void Application::run()
{
	const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
	sf::Clock clock;
	sf::Time TimeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		processInput();
		TimeSinceLastUpdate += clock.restart();
		while (TimeSinceLastUpdate > TimePerFrame)
		{
			TimeSinceLastUpdate -= TimePerFrame;
			processInput();
			update(TimePerFrame);
		}
		render();
	}
}