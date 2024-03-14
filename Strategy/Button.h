#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "BaseButton.h"
class Button : public BaseButton
{
friend void MoveView(sf::View& view,sf::RenderWindow& window,const sf::Event& event,std::list<GUIObject*>&GUI);

public:
	Button();
	Button(int x,int y,int w,int h);
	~Button()override;
	
	void Draw(sf::RenderWindow& window) override;

	void PollEvent(const sf::Event& event,const sf::RenderWindow& window,const sf::Vector2f& pos);
	
	Button& operator=(const Button& other);
};
