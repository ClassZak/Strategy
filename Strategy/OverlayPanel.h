#ifndef OVERLAY_PANEL_H
#define OVERLAY_PANEL_H
#include "Object.h"
#include <SFML/Graphics.hpp>
#include <windows.h>
class OverlayPanel : public GUIObject
{
public:
	OverlayPanel();
	~OverlayPanel()override;
	
	void Draw(sf::RenderWindow& window)override;
	

	
	void PushFrontRectangle(const sf::Vector2f& pos,const sf::Vector2f& dimensions,const sf::Color& color);
	void AddRectangle
	(
		const sf::Vector2f& pos,
		const sf::Vector2f& dimensions,
		const sf::Color& color,
		const unsigned int numberOfElement=0
	);
	void RemoveRectangle(const unsigned int pos=0);
	void Move(const sf::Vector2f& offset);
	
	sf::RectangleShape* fields;
	unsigned int rectangles;
};
#endif
