#pragma once
#include "Global.h"
#include "BaseButton.h"
BaseButton::BaseButton() : PlacedGUIObject::PlacedGUIObject()
{
	pressed = released = clicked = false;
}
BaseButton::BaseButton(int x, int y, int w, int h) : PlacedGUIObject::PlacedGUIObject(x, y, w, h)
{
	pressed = released = clicked = false;
}


BaseButton& BaseButton::operator=(const BaseButton& other)
{
	this->x = other.x;
	this->y = other.y;
	this->w = other.w;
	this->h = other.h;
	this->text = other.text;
	this->pressed = other.pressed;
	this->released = other.released;
	this->clicked = other.clicked;

	return *this;
}


void BaseButton::DrawBorder(sf::RenderWindow& window) const
{
	sf::VertexArray line(sf::Lines, 16);
	//line[0].texCoords
	if (!pressed)
	{
		line[0].position = sf::Vector2f(x - w / 2, y + h / 2);
		line[1].position = sf::Vector2f(x + w / 2, y + h / 2);
		line[0].color = sf::Color::Color(103, 103, 103);
		line[1].color = sf::Color::Color(103, 103, 103);

		line[2].position = sf::Vector2f(x - w / 2 + Global::PSizes.x, y + h / 2 - Global::PSizes.y);
		line[3].position = sf::Vector2f(x + w / 2 - Global::PSizes.x, y + h / 2 - Global::PSizes.y);
		line[2].color = sf::Color::Color(159, 159, 159);
		line[3].color = sf::Color::Color(159, 159, 159);


		line[4].position = sf::Vector2f(x + w / 2, y - h / 2);
		line[5].position = sf::Vector2f(x + w / 2, y + h / 2 - Global::PSizes.y);
		line[4].color = sf::Color::Color(103, 103, 103);
		line[5].color = sf::Color::Color(103, 103, 103);

		line[6].position = sf::Vector2f(x + w / 2 - Global::PSizes.x, y - h / 2 + Global::PSizes.y);
		line[7].position = sf::Vector2f(x + w / 2 - Global::PSizes.x, y + h / 2 - Global::PSizes.y * 2);
		line[6].color = sf::Color::Color(159, 159, 159);
		line[7].color = sf::Color::Color(159, 159, 159);



		line[8].position = sf::Vector2f(x - w / 2, y - h / 2 + Global::PSizes.y);
		line[9].position = sf::Vector2f(x + w / 2 - Global::PSizes.x, y - h / 2 + Global::PSizes.y);
		line[8].color = sf::Color::Color(254, 254, 254);
		line[9].color = sf::Color::Color(254, 254, 254);

		line[10].position = sf::Vector2f(x - w / 2 + Global::PSizes.x, y - h / 2 + Global::PSizes.y);
		line[11].position = sf::Vector2f(x - w / 2 + Global::PSizes.x, y + h / 2 - Global::PSizes.y);
		line[10].color = sf::Color::Color(254, 254, 254);
		line[11].color = sf::Color::Color(254, 254, 254);



		line[12].position = sf::Vector2f(x - w / 2 + Global::PSizes.x * 2, y - h / 2 + Global::PSizes.y);
		line[13].position = sf::Vector2f(x - w / 2 + Global::PSizes.x * 2, y + h / 2 - Global::PSizes.y * 2);
		line[12].color = sf::Color::Color(225, 225, 225);
		line[13].color = sf::Color::Color(225, 225, 225);

		line[14].position = sf::Vector2f(x - w / 2, y - h / 2 + Global::PSizes.y);
		line[15].position = sf::Vector2f(x + w / 2 - Global::PSizes.x, y - h / 2 + Global::PSizes.y);
		line[14].color = sf::Color::Color(255, 255, 255);
		line[15].color = sf::Color::Color(255, 255, 255);
	}
	else
	if (pressed)
	{
		line[0].position = sf::Vector2f(x - w / 2, y + h / 2);
		line[1].position = sf::Vector2f(x + w / 2, y + h / 2);
		line[0].color = sf::Color::Color(254, 254, 254);
		line[1].color = sf::Color::Color(254, 254, 254);

		line[2].position = sf::Vector2f(x - w / 2 + Global::PSizes.x, y + h / 2 - Global::PSizes.y);
		line[3].position = sf::Vector2f(x + w / 2 - Global::PSizes.x, y + h / 2 - Global::PSizes.y);
		line[2].color = sf::Color::Color(225, 225, 225);
		line[3].color = sf::Color::Color(225, 225, 225);


		line[4].position = sf::Vector2f(x + w / 2, y - h / 2);
		line[5].position = sf::Vector2f(x + w / 2, y + h / 2 - Global::PSizes.y);
		line[4].color = sf::Color::Color(254, 254, 254);
		line[5].color = sf::Color::Color(254, 254, 254);

		line[6].position = sf::Vector2f(x + w / 2 - Global::PSizes.x, y - h / 2 + Global::PSizes.y);
		line[7].position = sf::Vector2f(x + w / 2 - Global::PSizes.x, y + h / 2 - Global::PSizes.y * 2);
		line[6].color = sf::Color::Color(225, 225, 225);
		line[7].color = sf::Color::Color(225, 225, 225);



		line[8].position = sf::Vector2f(x - w / 2, y - h / 2 + Global::PSizes.y);
		line[9].position = sf::Vector2f(x + w / 2 - Global::PSizes.x, y - h / 2 + Global::PSizes.y);
		line[8].color = sf::Color::Color(103, 103, 103);
		line[9].color = sf::Color::Color(103, 103, 103);

		line[8].position = sf::Vector2f(x - w / 2 + Global::PSizes.x, y - h / 2 + Global::PSizes.y * 2);
		line[9].position = sf::Vector2f(x + w / 2 - Global::PSizes.x * 2, y - h / 2 + Global::PSizes.y * 2);
		line[8].color = sf::Color::Color(159, 159, 159);
		line[9].color = sf::Color::Color(159, 159, 159);


		line[10].position = sf::Vector2f(x - w / 2 + Global::PSizes.x, y - h / 2 + Global::PSizes.y);
		line[11].position = sf::Vector2f(x - w / 2 + Global::PSizes.x, y + h / 2 - Global::PSizes.y);
		line[10].color = sf::Color::Color(103, 103, 103);
		line[11].color = sf::Color::Color(103, 103, 103);

		line[10].position = sf::Vector2f(x - w / 2 + Global::PSizes.x * 2, y - h / 2 + Global::PSizes.y);
		line[11].position = sf::Vector2f(x - w / 2 + Global::PSizes.x * 2, y + h / 2 - Global::PSizes.y * 2);
		line[10].color = sf::Color::Color(159, 159, 159);
		line[11].color = sf::Color::Color(159, 159, 159);



		line[12].position = sf::Vector2f(x - w / 2, y - h / 2 + Global::PSizes.y);
		line[13].position = sf::Vector2f(x + w / 2 - Global::PSizes.x, y - h / 2 + Global::PSizes.y);
		line[12].color = sf::Color::Color(255, 255, 255);
		line[13].color = sf::Color::Color(255, 255, 255);

		line[14].position = sf::Vector2f(x - w / 2 + Global::PSizes.x, y - h / 2 + Global::PSizes.y);
		line[15].position = sf::Vector2f(x - w / 2 + Global::PSizes.x, y + h / 2);
		line[14].color = sf::Color::Color(255, 255, 255);
		line[15].color = sf::Color::Color(255, 255, 255);
	}
	window.draw(line);
}
void BaseButton::DrawBackground(sf::RenderWindow& window)
{
	sf::RectangleShape rect(sf::Vector2f(w, h));
	rect.setOrigin(w / 2, h / 2);
	rect.setFillColor(sf::Color::Color(241, 241, 241));
	rect.setPosition(GetCoordinates());


	window.draw(rect);
}

void BaseButton::SetFont(const sf::Font& font)
{
	text.setFont(font);
}
void BaseButton::SetText(const sf::Text& text)
{
	this->text = text;
	this->text.setPosition(text.getPosition());
	this->text.setOrigin((unsigned int)text.getGlobalBounds().width / 2, (unsigned int)text.getGlobalBounds().height);
	this->text.setFillColor(sf::Color::Black);
}
void BaseButton::SetTextString(const sf::String& string)
{
	text.setString(string);
	text.setPosition(x, y);
	text.setOrigin((unsigned int)text.getGlobalBounds().width / 2, (unsigned int)text.getGlobalBounds().height);
	text.setFillColor(sf::Color::Black);
}
void BaseButton::SetTextSize(const unsigned int size)
{
	text.setCharacterSize(size);
}


const sf::String& BaseButton::GetTextString()const
{
	return text.getString();
}
const sf::Text& BaseButton::GetText()const
{
	return text;
}
const sf::Font* BaseButton::GetFont()const
{
	return text.getFont();
}


bool BaseButton::IsPressed()
{
	return pressed;
}
bool BaseButton::IsReleased()
{
	return released;
}


void BaseButton::MakeUnclick()
{
	clicked = false;
}
void BaseButton::Reset()
{
	clicked = false;
	pressed = false;
	released = false;
}
bool BaseButton::IsClicked()
{
	return clicked;
}


void BaseButton::SetCoordinates(const sf::Vector2f& pos)
{
	PlacedGUIObject::SetCoordinates(pos);
}
sf::Vector2f BaseButton::GetCoordinates()const
{
	return PlacedGUIObject::GetCoordinates();
}
void BaseButton::SetSize(const sf::Vector2f& size)
{
	PlacedGUIObject::SetSize(size);
}
sf::Vector2f BaseButton::GetSize()const
{
	return PlacedGUIObject::GetSize();
}
void BaseButton::Move(const sf::Vector2f& offset)
{
	this->x += offset.x;
	this->y += offset.y;

	this->text.setPosition(x, y);
}
