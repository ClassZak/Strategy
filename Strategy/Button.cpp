#ifndef BUTTON_CPP
#define BUTTON_CPP
#include "Button.h"
Button::Button() : PlacedGUIObject::PlacedGUIObject()
{
	pressed=released=clicked=false;
}
Button::Button(int x,int y,int w,int h) : PlacedGUIObject::PlacedGUIObject(x,y,w,h)
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
	sf::VertexArray line(sf::Lines,16);
	
	if(!pressed)
	{
		line[0].position=sf::Vector2f(x-w/2, y+h/2);
		line[1].position=sf::Vector2f(x+w/2, y+h/2);
		line[0].color=sf::Color::Color(103,103,103);
		line[1].color=sf::Color::Color(103,103,103);
		
		line[2].position=sf::Vector2f(x-w/2+1, y+h/2-1);
		line[3].position=sf::Vector2f(x+w/2-1, y+h/2-1);
		line[2].color=sf::Color::Color(159,159,159);
		line[3].color=sf::Color::Color(159,159,159);
		
		
		line[4].position=sf::Vector2f(x+w/2, y-h/2);
		line[5].position=sf::Vector2f(x+w/2, y+h/2-1);
		line[4].color=sf::Color::Color(103,103,103);
		line[5].color=sf::Color::Color(103,103,103);
		
		line[6].position=sf::Vector2f(x+w/2-1, y-h/2+1);
		line[7].position=sf::Vector2f(x+w/2-1, y+h/2-2);
		line[6].color=sf::Color::Color(159,159,159);
		line[7].color=sf::Color::Color(159,159,159);
		
		
		
		line[8].position=sf::Vector2f(x-w/2,  y-h/2+1);
		line[9].position=sf::Vector2f(x+w/2-1,y-h/2+1);
		line[8].color=sf::Color::Color(254,254,254);
		line[9].color=sf::Color::Color(254,254,254);
		
		line[8].position=sf::Vector2f(x-w/2+1,y-h/2+2);
		line[9].position=sf::Vector2f(x+w/2-2,y-h/2+2);
		line[8].color=sf::Color::Color(225,225,225);
		line[9].color=sf::Color::Color(225,225,225);
		
		
		line[10].position=sf::Vector2f(x-w/2+1,y-h/2+1);
		line[11].position=sf::Vector2f(x-w/2+1,y+h/2-1);
		line[10].color=sf::Color::Color(254,254,254);
		line[11].color=sf::Color::Color(254,254,254);
		
		line[12].position=sf::Vector2f(x-w/2+2,y-h/2+1);
		line[13].position=sf::Vector2f(x-w/2+2,y+h/2-2);
		line[12].color=sf::Color::Color(225,225,225);
		line[13].color=sf::Color::Color(225,225,225);
	}
	else
	{
		line[0].position=sf::Vector2f(x-w/2, y+h/2);
		line[1].position=sf::Vector2f(x+w/2, y+h/2);
		line[0].color=sf::Color::Color(254,254,254);
		line[1].color=sf::Color::Color(254,254,254);
		
		line[2].position=sf::Vector2f(x-w/2+1, y+h/2-1);
		line[3].position=sf::Vector2f(x+w/2-1, y+h/2-1);
		line[2].color=sf::Color::Color(225,225,225);
		line[3].color=sf::Color::Color(225,225,225);
		
		
		line[4].position=sf::Vector2f(x+w/2, y-h/2);
		line[5].position=sf::Vector2f(x+w/2, y+h/2-1);
		line[4].color=sf::Color::Color(254,254,254);
		line[5].color=sf::Color::Color(254,254,254);
		
		line[6].position=sf::Vector2f(x+w/2-1, y-h/2+1);
		line[7].position=sf::Vector2f(x+w/2-1, y+h/2-2);
		line[6].color=sf::Color::Color(225,225,225);
		line[7].color=sf::Color::Color(225,225,225);
		
		
		
		line[8].position=sf::Vector2f(x-w/2,  y-h/2+1);
		line[9].position=sf::Vector2f(x+w/2-1,y-h/2+1);
		line[8].color=sf::Color::Color(103,103,103);
		line[9].color=sf::Color::Color(103,103,103);
		
		line[8].position=sf::Vector2f(x-w/2+1,y-h/2+2);
		line[9].position=sf::Vector2f(x+w/2-2,y-h/2+2);
		line[8].color=sf::Color::Color(159,159,159);
		line[9].color=sf::Color::Color(159,159,159);
		
		
		line[10].position=sf::Vector2f(x-w/2+1,y-h/2+1);
		line[11].position=sf::Vector2f(x-w/2+1,y+h/2-1);
		line[10].color=sf::Color::Color(103,103,103);
		line[11].color=sf::Color::Color(103,103,103);
		
		line[10].position=sf::Vector2f(x-w/2+2,y-h/2+1);
		line[11].position=sf::Vector2f(x-w/2+2,y+h/2-2);
		line[10].color=sf::Color::Color(159,159,159);
		line[11].color=sf::Color::Color(159,159,159);
	}

	
	
	sf::RectangleShape rect(sf::Vector2f(w,h));
	rect.setOrigin(w/2,h/2);
	rect.setFillColor(sf::Color::Color(241,241,241));
	rect.setPosition(GetCoordinates());
	
	
	window.draw(rect);
	window.draw(line);
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


std::istream& operator>>(std::istream& in,Button& ob)
{
	std::string stext;
	in>>ob.x>>ob.y>>ob.w>>ob.h>>stext;
	ob.text.setString(sf::String(stext));
	return in;
}
std::ostream& operator<<(std::ostream& out,const Button& ob)
{
	std::string stext=ob.text.getString().toAnsiString();
	out<<ob.x<<' '<<ob.y<<' '<<ob.w<<' '<<ob.h<<' '<<stext;
	return out;
}
#endif
