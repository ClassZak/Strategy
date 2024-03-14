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


void Button::SetFont(const sf::Font& font)
{
	text.setFont(font);
}
void Button::SetText(const sf::Text& text)
{
	this->text=text;
	this->text.setPosition(text.getPosition());
	this->text.setOrigin((unsigned int)text.getGlobalBounds().width/2,(unsigned int)text.getGlobalBounds().height);
	this->text.setFillColor(sf::Color::Black);
}
void Button::SetTextString(const sf::String& string)
{
	text.setString(string);
	text.setPosition(x,y);
	text.setOrigin((unsigned int)text.getGlobalBounds().width/2,(unsigned int)text.getGlobalBounds().height);
	text.setFillColor(sf::Color::Black);
}
void Button::SetTextSize(const unsigned int size)
{
	text.setCharacterSize(size);
}


const sf::String& Button::GetTextString()const
{
	return text.getString();
}
const sf::Text& Button::GetText()const
{
	return text;
}
const sf::Font* Button::GetFont()const
{
	return text.getFont();
}


bool Button::IsPressed()
{
	return pressed;
}
bool Button::IsReleased()
{
	return released;
}


void Button::MakeUnclick()
{
	clicked=false;
}
void Button::Reset()
{
	clicked=false;
	pressed=false;
	released=false;
}
bool Button::IsClicked()
{
	return clicked;
}


void Button::SetCoordinates(const sf::Vector2f& pos)
{
	PlacedGUIObject::SetCoordinates(pos);
}
sf::Vector2f Button::GetCoordinates()const
{
	return PlacedGUIObject::GetCoordinates();
}
void Button::SetSize(const sf::Vector2f& size)
{
	PlacedGUIObject::SetSize(size);
}
sf::Vector2f Button::GetSize()const
{
	return PlacedGUIObject::GetSize();
}
void Button::Move(const sf::Vector2f& offset)
{
	this->x+=offset.x;
	this->y+=offset.y;
	
	this->text.setPosition(x,y);
}
#endif
