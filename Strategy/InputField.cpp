#ifndef INPUT_FIELD_CPP
#define INPUT_FIELD_CPP
#include "InputField.h"
#include "Global.h"
#include "Functions.h"

//Public constructors
InputField::InputField(int x,int y,int w,int h) : PlacedGUIObject::PlacedGUIObject(x,y,w,h)
{
	this->inputs=false;
	this->bottomText.setPosition(x-w/2,y);
}

InputField::InputField(int x,int y,int w,int h,const sf::String& textString) :
InputField::InputField(x,y,w,h)
{
	this->bottomText.setString(textString);
	this->bottomText.setPosition(x-w/2,y);
}

InputField::~InputField()
{
}

//Settings methods
void InputField::setTextString(const sf::String& textString)
{
	this->bottomText.setString(textString);
}
void InputField::setText(const sf::Text& text)
{
	this->bottomText=text;
}
void InputField::setTextParametres(const sf::Font& font,unsigned int charSize)
{
	this->bottomText.setFont(font);
	this->text.setFont(font);
	this->bottomText.setCharacterSize(charSize);
	this->text.setCharacterSize(charSize);
}
void InputField::setTextParametres(const sf::String& textString,const sf::Font& font,unsigned int charSize)
{
	this->bottomText.setString(textString);
	this->setTextParametres(font,charSize);
}
//Gettings methods
const sf::Font* InputField::getFont()const
{
	return this->bottomText.getFont();
}
sf::Text InputField::getText()
{
	sf::Text result;
	result.setCharacterSize(this->bottomText.getCharacterSize());
	result.setFillColor(this->bottomText.getFillColor());
	result.setFont(*this->bottomText.getFont());
	result.setString(this->bottomText.getString()+this->bottomText.getString());
	return result;
}
sf::String InputField::getTextString()const
{
	std::wstring cuttedStr;
	cuttedStr=text.getString().toWideString();
	cuttedStr+=bottomText.getString().toWideString();
	
	return sf::String(getStringExceptSymbols(cuttedStr,L'\n'));
}
bool InputField::isInputing()const
{
	return this->inputs;
}

//Drawing and poll event
void InputField::Draw(sf::RenderWindow& window)
{
	sf::RectangleShape rect(sf::Vector2f(w,h));
	
	sf::VertexArray borders(sf::Lines,8);
	borders[0].position=(sf::Vector2f(x-w/2-1,y-h/2));
	borders[1].position=(sf::Vector2f(x+w/2,y-h/2));
	
	borders[2].position=(sf::Vector2f(x+w/2,y-h/2));
	borders[3].position=(sf::Vector2f(x+w/2,y+h/2));
	
	borders[4].position=(sf::Vector2f(x+w/2,y+h/2));
	borders[5].position=(sf::Vector2f(x-w/2,y+h/2));
	
	borders[6].position=(sf::Vector2f(x-w/2,y+h/2));
	borders[7].position=(sf::Vector2f(x-w/2,y-h/2));
	
	
	if(!this->inputs)
	{
		this->bottomText.setFillColor(sf::Color(128,128,128));
		this->text.setFillColor(sf::Color(128,128,128));
		borders[0].color=sf::Color(171,173,179);
		borders[1].color=sf::Color(171,173,179);
		
		for(unsigned int i=2;i<8;++i)
		borders[i].color=sf::Color(226,227,234);
	}
	else
	{
		this->bottomText.setFillColor(sf::Color::Black);
		this->text.setFillColor(sf::Color::Black);
		borders[0].color=sf::Color(61,123,173);
		borders[1].color=sf::Color(61,123,173);
		
		for(unsigned int i=2;i<8;++i)
		borders[i].color=sf::Color(181,207,231);
	}
	
	
	
	rect.setOrigin(w/2,h/2);
	rect.setFillColor(sf::Color(255,255,255));
	rect.setPosition(GetCoordinates());
	
	
	this->text.setOrigin(0,0);
	this->bottomText.setOrigin(0,0);
	this->text.setPosition(GetCoordinates().x-this->w/2,GetCoordinates().y-this->h/2);
	this->bottomText.setPosition
	(
		GetCoordinates().x-this->w/2,
		(this->text.getString().getSize()) ? 
		GetCoordinates().y-this->h/2+(long int)(Global::font.getLineSpacing(this->text.getCharacterSize())/2.f)
		+this->text.getGlobalBounds().height
		:
		GetCoordinates().y-this->h/2
	);
	
	window.draw(rect);
	window.draw(borders);
	window.draw(this->bottomText);
	window.draw(this->text);
	
	if(this->inputs)
	{
		sf::Text cursor;
		cursor.setString(sf::String("_"));
		cursor.setFont(*this->bottomText.getFont());
		cursor.setCharacterSize(this->text.getCharacterSize());
		cursor.setPosition
		(
			this->bottomText.getGlobalBounds().width+this->bottomText.getPosition().x+2.f,
			this->bottomText.getPosition().y
		);
		
		cursor.setOrigin(0,cursor.getGlobalBounds().height);
		
		cursor.setFillColor(this->bottomText.getFillColor());
		
		window.draw(cursor);
	}
}


void InputField::PollEvent(const sf::Event& event, const sf::RenderWindow& window,const sf::Vector2f& pos)
{
	if(!Global::focus)
	{
		this->inputs=false;
		return;
	}
	if(Global::ReleasedMouseButtons::lMouseReleased)
	{
		if( (((this->x-w/2)<pos.x) and (pos.x<(this->x+w/2)))
			and
			(((this->y-h/2)<pos.y) and (pos.y<(this->y+h/2))))
		this->inputs=!this->inputs;
		else
		this->inputs=false;
	}
	if(this->inputs)
	if(event.type==sf::Event::TextEntered)
	this->charInput(event);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//												Protected
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InputField::charInput(const sf::Event& event)
{
	sf::Uint32 keyCode=event.text.unicode;
	if(keyCode==8)
	{
		//Backspace
		if(this->bottomText.getString().getSize())
		{
			this->bottomText.setString
			(this->bottomText.getString().substring(0,this->bottomText.getString().getSize()-1));
		}
		if(!this->bottomText.getString().getSize())
		{
			if(!this->text.getString().getSize())
			return;
			
			std::size_t separatePos=getLastLinePos(this->text.getString().toWideString());
			this->bottomText.setString
			(
				this->text.getString().substring
				(separatePos,sf::String::InvalidPos)
			);
			if(this->text.getString().find(L'\n')==sf::String::InvalidPos)
			this->text.setString(sf::String(L""));
			else
			this->text.setString
			(
				this->text.getString().substring
				(0,separatePos-1)
			);
		}
		return;
	}
	if(keyCode==13 or keyCode==27)
	{
		this->inputs=false;
		return;
	}
	
	bool correctHeight,correctWidth;
	correctHeight=bool
	(
		this->bottomText.getGlobalBounds().height+
		this->text.getGlobalBounds().height+
		(long int)(Global::font.getLineSpacing(this->text.getCharacterSize()))*2
		>
		this->h
	);
	correctWidth=bool
	(
		this->bottomText.getGlobalBounds().width+
		(long int)(Global::font.getLineSpacing(this->text.getCharacterSize()))*1.2
		<=
		this->w
	);
	if(!correctHeight)
	{
		if
		(
			this->bottomText.getGlobalBounds().width
			<=
			this->w
		)
		this->bottomText.setString(this->bottomText.getString()+keyCode);	
	}
	else
	{
		if(correctWidth)
		this->bottomText.setString(this->bottomText.getString()+keyCode);
	}
	this->lineBreak();
}


void InputField::lineBreak()
{
	if
	(
		this->bottomText.getGlobalBounds().height+
		this->text.getGlobalBounds().height+
		(long int)(Global::font.getLineSpacing(this->text.getCharacterSize())*2)
		<
		this->h
	)
	if
	(
		this->bottomText.getGlobalBounds().width+
		(long int)(Global::font.getLineSpacing(this->text.getCharacterSize()))
		>
		this->w
	)
	{
		if(this->text.getString().getSize())
		this->text.setString(this->text.getString()+L'\n');
		this->text.setString
		(
			this->text.getString()+
			this->bottomText.getString().substring(0,this->bottomText.getString().getSize()-1)
		);
		this->text.setString(this->text.getString());
		this->bottomText.setString
		(sf::String(this->bottomText.getString()[this->bottomText.getString().getSize()-1]));
	}
}
#endif
