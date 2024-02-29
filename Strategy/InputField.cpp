#include "InputField.h"
#include "Global.h"
#include "Functions.h"

//Public constructors
InputField::InputField(int x,int y,int w,int h) : PlacedGUIObject::PlacedGUIObject(x,y,w,h)
{
	this->inputs=false;
	this->text.setPosition(x-w/2,y-h/2);
	cursorPos = sf::Vector2i(0, 1);
}

InputField::InputField(int x,int y,int w,int h,const std::wstring& textString) :
InputField::InputField(x,y,w,h)
{
	this->textString = textString;
	this->text.setString(sf::String(textString));
	LineBreak(0);
	std::size_t symbolStringLenght = getStringExceptSymbols(this->textString, L'\n').length();
	cursorPos.y = (UINT)(symbolStringLenght / symbolBoxSize.x);
	cursorPos.x = (UINT)(symbolStringLenght % symbolBoxSize.x);
}

InputField::~InputField()
{
}

//Settings methods
void InputField::setTextString(const std::wstring& textString)
{
	this->text.setString(sf::String(textString));
}
void InputField::setText(const sf::Text& text)
{
	this->text=text;
}
void InputField::setTextParametres(const sf::Font& font,unsigned int charSize)
{
	this->text.setFont(font);
	this->text.setCharacterSize(charSize);
	symbolSize = sf::Vector2f
	(
		text.getCharacterSize() / 2 + text.getLetterSpacing(),
		text.getCharacterSize() + text.getLineSpacing() * 2
	);
	symbolBoxSize = sf::Vector2i
	(
		(INT)round((w - (text.getCharacterSize() / 2 + text.getLetterSpacing()) + 2) / symbolSize.x),
		(INT)round((h - this->text.getCharacterSize() / 2) / symbolSize.y)
	);
}
void InputField::setTextParametres(const std::wstring& textString,const sf::Font& font,unsigned int charSize)
{
	this->text.setString(sf::String(textString));
	this->setTextParametres(font,charSize);
}
//Gettings methods
const sf::Font* InputField::getFont()const
{
	return this->text.getFont();
}
sf::Text InputField::getText()
{
	return this->text;
}
std::wstring InputField::getTextString()const
{
	return (getStringExceptSymbols(this->textString,L'\n'));
}
bool InputField::isInputing()const
{
	return this->inputs;
}

//Drawing and poll event
void InputField::Draw(sf::RenderWindow& window)
{
	sf::RectangleShape rect(sf::Vector2f(w,h));
	rect.setOrigin(w / 2, h / 2);
	rect.setFillColor(sf::Color(255, 255, 255));
	rect.setPosition(GetCoordinates());
	
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
		this->text.setFillColor(sf::Color(128,128,128));
		borders[0].color=sf::Color(171,173,179);
		borders[1].color=sf::Color(171,173,179);
		
		for(unsigned int i=2;i<8;++i)
		borders[i].color=sf::Color(226,227,234);
	}
	else
	{
		this->text.setFillColor(sf::Color::Black);
		borders[0].color=sf::Color(61,123,173);
		borders[1].color=sf::Color(61,123,173);
		
		for(unsigned int i=2;i<8;++i)
		borders[i].color=sf::Color(181,207,231);
	}


	this->text.setString(sf::String(this->textString));

	window.draw(rect);
	{
		UINT currCharRect = 1;
		sf::RectangleShape charRect
		(
			sf::Vector2f
			(text.getCharacterSize()/2 + text.getLetterSpacing(), text.getCharacterSize()+text.getLineSpacing()*2)
		);
		for
			(
				float y = this->y - h / 2;
				y < (this->y + h / 2) - (text.getCharacterSize() + text.getLineSpacing() * 2);
				y += text.getCharacterSize() + text.getLineSpacing() * 2
				)
		{
			for
			(
				float x = this->x - w / 2;
				x < (this->x + w / 2)-(text.getCharacterSize() / 2 + text.getLetterSpacing());
				x += text.getCharacterSize()/2 + text.getLetterSpacing()
			)
			{
				charRect.setPosition(x, y);
				charRect.setFillColor((currCharRect++ & 1) ? sf::Color(266,133,133) : sf::Color(137,219,119));
				window.draw(charRect);
			}
			if (!(symbolBoxSize.x & 1))
				++currCharRect;
		}
		
	}
	window.draw(borders);
	window.draw(this->text);

	if (inputs)
	{
		sf::RectangleShape cursor(sf::Vector2f(1, text.getCharacterSize() + text.getLineSpacing() * 2));
		cursor.setPosition(cursorPos.x*symbolSize.x+x-w/2, (cursorPos.y-1) * symbolSize.y+y-h/2);
		cursor.setFillColor(sf::Color::Black);
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
		this->inputs=true;
		else
		this->inputs=false;
	}
	if(this->inputs)
	if(event.type==sf::Event::TextEntered)
	this->charInput(event);
	else
	if (event.type == sf::Event::KeyPressed)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			--cursorPos.x;
		CorrectCursorPos();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			std::size_t s = textString.length();
			if(symbolBoxSize.x*(cursorPos.y-1)+cursorPos.x+cursorPos.y-1<s)
				++cursorPos.x;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			--cursorPos.y;
			
		CorrectCursorPos();
	}
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
			--cursorPos.x;
			if (textString.length() == 1)
			{
				textString.clear();
				this->text.setString(sf::String(textString));
			}
			else
			{
				textString.erase(textString.length() - 1);
				if (textString[textString.length() - 1] == L'\n')
				{
					textString.erase(textString.length() - 1);
					--cursorPos.x;
				}
				this->text.setString(sf::String(this->textString));
			}
			CorrectCursorPos();
			return;
		}
		return;
	}
	if (keyCode == 13 or keyCode == 27 or ((wchar_t)keyCode==L'\t'))
	{
		this->inputs = false;//Enter and Esc
		return;
	}
	textString += (wchar_t)keyCode;
	++cursorPos.x;
	CorrectCursorPos();
	float delta = text.getGlobalBounds().width;
	text.setString(sf::String(this->textString));
	delta -= text.getGlobalBounds().width;
	
	if(text.getGlobalBounds().width)
	
	
		LineBreak(delta);
	CorrectCursorPos();
	std::cout << std::endl;
}
void InputField::LineBreak(const float widthDelta)
{
	if (this->text.getGlobalBounds().width > this->w - this->text.getCharacterSize() / 2)
	{
		textString.insert(textString.length() - 1, L"\n");
		this->text.setString(sf::String(textString));
		++cursorPos.x;
		CorrectCursorPos();
	}
	if (this->text.getGlobalBounds().width >= this->w)
		throw std::runtime_error("input field width failed");
	if (textString.length()>symbolBoxSize.y*symbolBoxSize.x+ symbolBoxSize.y)
	{
		textString.erase(textString.length() - 1);
		textString.erase(textString.length() - 1);
		this->text.setString(sf::String(textString));
	}
	if (text.getGlobalBounds().height >= this->h)
		throw std::runtime_error("input field height failed");
}
void InputField::CorrectCursorPos()
{
	SetConsoleTextAttribute(Global::consoleOutHandle, FOREGROUND_INTENSITY);
	std::cout << "cPos:\tx:\t" << cursorPos.x << "\ty:\t" << cursorPos.y << std::endl;
	SetConsoleTextAttribute(Global::consoleOutHandle, FOREGROUND_DEFAULT);
	if (cursorPos.x < 0)
	{
		if (cursorPos.y > 1)
		{
			--cursorPos.y;
			cursorPos.x = symbolBoxSize.x;
		}
		else
			cursorPos.x = 0;
	}
	if (cursorPos.x > symbolBoxSize.x)
	{
		if (cursorPos.y < symbolBoxSize.y)
		{
			++cursorPos.y;
			cursorPos.x = 0;
		}
		else
			cursorPos.x = symbolBoxSize.x;
	}


	if (cursorPos.y < 1)
	{
		cursorPos.y = 1;
		cursorPos.x = 0;
	}
	if (cursorPos.y > symbolBoxSize.y)
	{
		cursorPos.y = symbolBoxSize.y;
		cursorPos.x = symbolBoxSize.x;
	}
}
