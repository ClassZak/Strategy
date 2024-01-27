#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Object.h"
class Button : public PlacedGUIObject
{
friend void MoveView(sf::View& view,sf::RenderWindow& window,const sf::Event& event,std::list<GUIObject*>&GUI);
friend std::istream& operator>>(std::istream& in,Button& ob);
friend std::ostream& operator<<(std::ostream& out,const Button& ob);

public:
	Button();
	Button(int x,int y,int w,int h);
	~Button()override;
	
	
	void SetCoordinates(const sf::Vector2f& pos);
	sf::Vector2f GetCoordinates()const;
	void SetSize(const sf::Vector2f& size);
	sf::Vector2f GetSize()const;
	
	
	void Draw(const sf::RenderWindow& window) override;
	
	
	bool IsPressed();
	bool IsReleased();
	
	void PollEvent(const sf::Event& event,const sf::RenderWindow& window,const sf::Vector2f& pos);
	
	
	void SetFont(const sf::Font& font);
	void SetText(const sf::Text& text);
	void SetTextString(const sf::String& string);
	void SetTextSize(const unsigned int size);
	const sf::String& GetTextString()const;
	const sf::Text& GetText()const;
	const sf::Font* GetFont()const;
	
	Button& operator=(const Button& other);
	
	void MakeUnclick();
	void Reset();
	bool IsClicked();
	
	void Move(const sf::Vector2f& offset);
protected:
	bool pressed;
	bool released;
	bool clicked;
	
	sf::Text text;
};
#endif