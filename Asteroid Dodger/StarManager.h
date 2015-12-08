#ifndef StarManager_H_
#define StarManager_H_

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/VertexArray.hpp>

class StarManager : public sf::VertexArray, private sf::NonCopyable
{
private:
	// Private Member(s)
	sf::IntRect		mWindowBounds;

private:
	// Private Method(s)
	void setupStar(sf::Vertex& v1, sf::Vertex& v2, sf::Vertex& v3);
	void spawnStars();
	void repositionStars();
public:
	// Constructor(s)
	StarManager(sf::IntRect winBounds);
	// Public Method(s)
	void update(sf::Time dt);
	
	inline void setWindowBounds(sf::IntRect winBounds) { mWindowBounds = winBounds; }
};
#endif