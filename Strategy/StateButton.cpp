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
//Button realization
//Getters and setters
sf::Vector2f StateButton::GetCoordinates()const
{
	return Button::GetCoordinates();
}
void StateButton::SetCoordinates(const sf::Vector2f& pos)
{
	Button::SetCoordinates(pos);
}

const sf::Font* StateButton::GetFont()const
{
	return Button::GetFont();
}
void StateButton::SetFont(const sf::Font& font)
{
	Button::SetFont(font);
}

const sf::Text& StateButton::GetText()const
{
	return Button::GetText();
}
void StateButton::SetText(const sf::Text& text)
{
	Button::SetText(text);
}

sf::Vector2f StateButton::GetSize()const
{
	return Button::GetSize();
}
void StateButton::SetSize(const sf::Vector2f& size)
{
	Button::SetSize(size);
}

const sf::String& StateButton::GetTextString()const
{
	return Button::GetTextString();
}
//Other
void StateButton::Reset()
{
	this->enabled=false;
	Button::Reset();
}
bool StateButton::IsClicked()
{
	return Button::IsClicked();
}
bool StateButton::IsEnabled()const
{
	return this->enabled;
}
bool StateButton::IsPressed()
{
	return Button::IsPressed();
}
bool StateButton::IsReleased()
{
	return Button::IsReleased();
}
void StateButton::MakeUnclick()
{
	Button::MakeUnclick();
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
