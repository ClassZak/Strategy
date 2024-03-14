#ifndef BUTTON_CPP
#define BUTTON_CPP
#include "Button.h"
Button::Button() : BaseButton::BaseButton()
{
	pressed=released=clicked=false;
}
Button::Button(int x,int y,int w,int h) : BaseButton::BaseButton(x,y,w,h)
{
	pressed=released=clicked=false;
}
Button::~Button()
{
	
}


Button& Button::operator=(const Button& other)
{
	this->x=other.x;
	this->y=other.y;
	this->w=other.w;
	this->h=other.h;
	this->text=other.text;
	this->pressed=other.pressed;
	this->released=other.released;
	this->clicked=other.clicked;
	
	return *this;
}


void Button::PollEvent(const sf::Event& event, const sf::RenderWindow& window, const sf::Vector2f& pos)
{
	if(clicked)
	clicked=false;
	
	if(event.type==sf::Event::MouseButtonPressed and event.key.code==sf::Mouse::Left)
	{
		if(((pos.x>=x-w/2)and(pos.x<=x+w/2)) and ((pos.y>=y-h/2)and(pos.y<=y+h/2)))
		pressed=true;
	}
	if(event.type==sf::Event::MouseButtonReleased and event.key.code==sf::Mouse::Left)
	{
		if((((pos.x>=x-w/2)and(pos.x<=x+w/2)) and ((pos.y>=y-h/2)and(pos.y<=y+h/2)))and(pressed))
		released=true;
		else
		released=false;
		
		pressed=false;
	}
	if(released)
	{
		released=false;
		clicked=true;
	}
}


void Button::Draw(sf::RenderWindow& window)
{
	DrawBackground(window);
	DrawBorder(window);
	window.draw(text);
}
#endif
