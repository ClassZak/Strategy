#ifndef BUTTON_WITH_IMAGE_CPP
#define BUTTON_WITH_IMAGE_CPP
#include "ButtonWithImage.h"
void ButtonWithImage::SetSprite(const sf::Sprite& sprite)
{
	this->sprite=sprite;
	this->sprite.setOrigin(this->sprite.getGlobalBounds().width/2,this->sprite.getGlobalBounds().height/2);
}
void ButtonWithImage::SetTexture(const sf::Texture& texture)
{
	this->texture=texture;
	sprite.setTexture(this->texture,true);
	sprite.setOrigin(sprite.getGlobalBounds().width/2,sprite.getGlobalBounds().height/2);
}
const sf::Sprite& ButtonWithImage::GetSprite()const
{
	return this->sprite;
}
const sf::Texture& ButtonWithImage::GetTexture()const
{
	return this->texture;
}



void ButtonWithImage::Draw(sf::RenderWindow& window)
{
	DrawBackground(window);
	window.draw(this->sprite);
	DrawBorder(window);
	window.draw(text);
}




ButtonWithImage::ButtonWithImage()
{
	this->Set();
}
ButtonWithImage::ButtonWithImage(int x,int y,int w,int h):Button::Button(x,y,w,h)
{
	this->Set();
}
ButtonWithImage::ButtonWithImage(int x,int y,int w,int h,sf::Texture& texture):Button::Button(x,y,w,h)
{
	TextVisible = false;
	ImageVisible = true;
	this->texture=texture;
	sprite.setTexture(this->texture,true);
	sprite.setOrigin(sprite.getGlobalBounds().width/2,sprite.getGlobalBounds().height/2);
	sprite.setPosition(x,y);
}
ButtonWithImage& ButtonWithImage::operator=(const ButtonWithImage& other)
{
	this->x=other.x;
	this->y=other.y;
	this->w=other.w;
	this->h=other.h;
	this->text=other.text;
	this->sprite=other.sprite;
	this->texture=other.texture;
	this->pressed=other.pressed;
	this->released=other.released;
	this->clicked=other.clicked;
	this->ImageVisible=other.ImageVisible;
	
	return *this;
}
ButtonWithImage::~ButtonWithImage()
{
	
}


void ButtonWithImage::Set()
{
	ImageVisible=true;
	TextVisible=false;
}
void ButtonWithImage::SetTextVisible(const bool is)
{
	TextVisible=is;
}
void ButtonWithImage::SetImageVisible(const bool is)
{
	ImageVisible=is;
}
bool ButtonWithImage::TextIsVisible()const
{
	return TextVisible;
}
bool ButtonWithImage::ImageIsVisible()const
{
	return ImageVisible;
}



void ButtonWithImage::SetTextPos(const sf::Vector2f& pos)
{
	this->text.setPosition(pos);
}
void ButtonWithImage::SetImagePos(const sf::Vector2f& pos)
{
	this->sprite.setPosition(pos);
}
const sf::Vector2f& ButtonWithImage::GetTextPos()const
{
	return this->text.getPosition();
}
const sf::Vector2f& ButtonWithImage::GetImagePos()const
{
	return this->sprite.getPosition();
}
void ButtonWithImage::Move(const sf::Vector2f& offset)
{
	BaseButton::Move(offset);
	this->sprite.move(offset);
}
#endif
