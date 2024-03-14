#pragma once
#include <SFML/Graphics.hpp>
class IButton
{
public:
	virtual void SetCoordinates(const sf::Vector2f& pos)=0;
	virtual sf::Vector2f GetCoordinates()const=0;
	virtual void SetSize(const sf::Vector2f& size)=0;
	virtual sf::Vector2f GetSize()const=0;


	virtual bool IsPressed()=0;
	virtual bool IsReleased()=0;

	virtual void SetFont(const sf::Font& font)=0;
	virtual void SetText(const sf::Text& text)=0;
	virtual void SetTextString(const sf::String& string)=0;
	virtual void SetTextSize(const unsigned int size)=0;
	virtual const sf::String& GetTextString()const=0;
	virtual const sf::Text& GetText()const=0;
	virtual const sf::Font* GetFont()const=0;


	virtual void MakeUnclick()=0;
	virtual void Reset()=0;
	virtual bool IsClicked()=0;

	virtual void Move(const sf::Vector2f& offset)=0;
protected:
	virtual void DrawBorder(sf::RenderWindow& window) const=0;
	virtual void DrawBackground(sf::RenderWindow& window)=0;
	bool pressed;
	bool released;
	bool clicked;

	sf::Text text;
};

