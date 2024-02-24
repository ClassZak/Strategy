#ifndef INPUT_FIELD_CPP
#define INPUT_FIELD_CPP
#include "InputField.h"
#include "Global.h"
#include "Functions.h"

//Public constructors
InputField::InputField(int x,int y,int w,int h) : PlacedGUIObject::PlacedGUIObject(x,y,w,h)
{
	this->inputs=false;
	this->text.setPosition(x-w/2,y-h/2);
}

InputField::InputField(int x,int y,int w,int h,const std::wstring& textString) :
InputField::InputField(x,y,w,h)
{
	this->textString = textString;
	this->text.setString(sf::String(textString));
	cursorPos = textString.length();
}

InputField::~InputField()
{
}

//Settings methods
void InputField::setTextString(const std::wstring& textString)
{
	this->bottomText.setString(sf::String(textString));
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
void InputField::setTextParametres(const std::wstring& textString,const sf::Font& font,unsigned int charSize)
{
	this->bottomText.setString(sf::String(textString));
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
std::wstring InputField::getTextString()const
{
	std::wstring cuttedStr;
	cuttedStr=text.getString().toWideString();
	cuttedStr+=bottomText.getString().toWideString();
	
	return (getStringExceptSymbols(cuttedStr,L'\n'));
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
	this->text.setString(sf::String(this->textString));

	window.draw(rect);
	window.draw(borders);
	window.draw(this->text);
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
	sf::Uint32 keyCode = event.text.unicode;
	if (keyCode == 8)
	{
		//Backspace
		if (textString.length())
		{
			textString.erase(textString.length() - 1);
			if(textString[textString.length()-1]==L'\n')
				textString.erase(textString.length() - 1);

			this->text.setString(sf::String(this->textString));
		}
		return;
	}
	if (keyCode == 13 or keyCode == 27)
	{
		this->inputs = false;//Enter and Esc
		return;
	}
	textString += (wchar_t)keyCode;
	
	this->text.setString(sf::String(this->textString));
	lineBreak();
}
void InputField::lineBreak()
{
	if (this->text.getGlobalBounds().width > this->w - this->text.getCharacterSize()/2)
	{
		textString.insert(textString.length() - 1, L"\n");
		this->text.setString(sf::String(textString));
		++cursorPos;
	}
	if (this->text.getGlobalBounds().height > this->h - this->text.getCharacterSize() / 2)
	{
		textString.erase(textString.length() - 1);
		textString.erase(textString.length() - 1);
		this->text.setString(sf::String(textString));
	}
}
#endif
