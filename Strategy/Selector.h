#ifndef SELECTOR_H
#define SELECTOR_H
#include "Object.h"
#include "Global.h"
#include <list>
#include <algorithm>
#include <windows.h>

class Selector
{
public:
	Selector();
	~Selector();
	
	enum State
	{
		ALL,
		SOLDIERS
	};
	
	void draw(const sf::RenderWindow& window);
	void pollEvent
	(
		sf::Event& event,
		const sf::RenderWindow& window,
		const sf::Vector2f& pos,
		const sf::Vector2f& GUIPos,
		const std::list<GameObject*>& objects
	);
	
	bool getVisible()const;
	bool getDoSelection()const;
	State getState()const;
private:
	void checkCorners();
	
	sf::Vector2f* cornerCoordinates;
	bool visible;
	bool doSelection;
	bool selectionStarted;
	bool selected;
	bool selectionFailed;
	State state;
};
#endif
