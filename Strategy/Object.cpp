#pragma once
#include "Object.h"
//Object
Object::Object()
{
}
Object::~Object()
{
}
//GUI object
GUIObject::GUIObject()
{
}
GUIObject::~GUIObject()
{
}
//Placed object
PlacedGUIObject::PlacedGUIObject()
{
	x = y = w = h = 0;
}
PlacedGUIObject::PlacedGUIObject(int x, int y, int w, int h)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}
PlacedGUIObject::~PlacedGUIObject()
{
}

sf::Vector2f PlacedGUIObject::GetCoordinates()const
{
	sf::Vector2f v((float)x, (float)y);
	return v;
}
void PlacedGUIObject::SetCoordinates(const sf::Vector2f& pos)
{
	this->x = (int)pos.x;
	this->y = (int)pos.y;
}

void PlacedGUIObject::SetSize(const sf::Vector2f& size)
{
	this->w = (int)size.x;
	this->h = (int)size.y;
}
sf::Vector2f PlacedGUIObject::GetSize()const
{
	sf::Vector2f s((float)w, (float)h);
	return s;
}


//Game object
GameObject::GameObject()
{
	x = y = w = h = 0;
	selected = false;
	texture = nullptr;
}
GameObject::~GameObject()
{
}
GameObject::GameObject(int x, int y, int w, int h) : GameObject()
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}
GameObject::GameObject(int x, int y, int w, int h, sf::Texture* texture) : GameObject::GameObject(x, y, w, h)
{
	this->texture = texture;
	this->sprite.setTexture(*this->texture, true);
	this->sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
	this->sprite.setPosition((float)x, (float)y);
}


void GameObject::SetCoordinates(const sf::Vector2f& pos)
{
	this->x = (int)pos.x;
	this->y = (int)pos.y;
	this->sprite.setPosition((float)x, (float)y);
}
void GameObject::SetSprite(const sf::Sprite& sprite)
{
	this->sprite = sprite;
	this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);
	this->sprite.setPosition((float)x, (float)y);
}
void GameObject::SetTexture(sf::Texture* texture)
{
	this->texture = texture;
	this->sprite.setTexture(*this->texture, true);
	this->sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
	this->sprite.setPosition((float)x, (float)y);
}
void GameObject::SetSize(const sf::Vector2f& size)
{
	this->w = (int)size.x;
	this->h = (int)size.y;
}
sf::Vector2f GameObject::GetCoordinates()const
{
	sf::Vector2f v((float)x, (float)y);
	return v;
}
const sf::Sprite& GameObject::GetSprite()const
{
	return this->sprite;
}
const sf::Texture* GameObject::GetTexture()const
{
	return this->texture;
}
sf::Vector2f GameObject::GetSize()const
{
	sf::Vector2f s((float)w, (float)h);
	return s;
}


