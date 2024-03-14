#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Object.h"
#include "IButton.h"
class BaseButton : public PlacedGUIObject, public IButton
{
	friend void MoveView
	(sf::View& view, sf::RenderWindow& window, const sf::Event& event, std::list<GUIObject*>& GUI);

public:
	BaseButton();
	BaseButton(int x, int y, int w, int h);


	bool IsPressed() override;
	bool IsReleased() override;

	void SetFont(const sf::Font& font) override;
	void SetText(const sf::Text& text) override;
	void SetTextString(const sf::String& string) override;
	void SetTextSize(const unsigned int size) override;
	const sf::String& GetTextString()const override;
	const sf::Text& GetText()const override;
	const sf::Font* GetFont()const override;

	BaseButton& operator=(const BaseButton& other);

	void MakeUnclick() override;
	void Reset() override;
	bool IsClicked() override;

	void Move(const sf::Vector2f& offset) override;
protected:
	void DrawBorder(sf::RenderWindow& window) const override;
	void DrawBackground(sf::RenderWindow& window) override;
};
