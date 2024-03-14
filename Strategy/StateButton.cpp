#ifndef STATE_BUTTON_CPP
#define STATE_BUTTON_CPP
#include "StateButton.h"
StateButton::StateButton() : Button::Button()
{
	StateButton::Reset();
}
StateButton::StateButton(int x,int y,int w,int h) : Button::Button(x,y,w,h)
{
	StateButton::Reset();
}
StateButton::~StateButton()
{
	
}
//Other
void StateButton::Reset()
{
	this->enabled=false;
	Button::Reset();
}
bool StateButton::IsEnabled()const
{
	return this->enabled;
}




StateButton& StateButton::operator=(const StateButton& other)
{
	this->x=other.x;
	this->y=other.y;
	this->w=other.w;
	this->h=other.h;
	this->clicked=other.clicked;
	this->enabled=other.enabled;
	this->pressed=other.pressed;
	this->released=other.released;
	this->text=other.text;
	
	return *this;
}
//Unucal drawing and poll event
void StateButton::Draw(sf::RenderWindow& window)
{
	Button::Draw(window);
}
void StateButton::PollEvent(const sf::Event& event,const sf::RenderWindow& window,const sf::Vector2f& pos)
{
	Button::PollEvent(event,window,pos);
	if(this->clicked)
	this->enabled=!this->enabled;
}






#endif
