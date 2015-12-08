#ifndef Application_H_
#define Application_H_

#include <PYRO/StateStack.h>

class Application : private sf::NonCopyable
{
private:
	// Private Member(s)
	sf::RenderWindow mWindow;
	pyro::StateStack mStateStack;

private:
	// Private Method(s)
	void processInput();
	void update(sf::Time dt);
	void render();

	void registerStates();
public:
	// Constructor(s)
	Application();
	// Public Method(s)
	void run();
};
#endif