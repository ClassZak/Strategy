#ifndef BUTTON_WITH_IMAGE_CPP
#define BUTTON_WITH_IMAGE_CPP
#include "ButtonWithImage.h"
void ButtonWithImage::SetCoordinates(const sf::Vector2f& pos)
{
	this->x=pos.x;
	this->y=pos.y;
}
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
sf::Vector2f ButtonWithImage::GetCoordinates()const
{
	return PlacedGUIObject::GetCoordinates();
}
const sf::Sprite& ButtonWithImage::GetSprite()const
{
	return this->sprite;
}
const sf::Texture& ButtonWithImage::GetTexture()const
{
	return this->texture;
}
void ButtonWithImage::SetSize(const sf::Vector2f& size)
{
	PlacedGUIObject::SetSize(size);
}
sf::Vector2f ButtonWithImage::GetSize()const
{
	return PlacedGUIObject::GetSize();
}



void ButtonWithImage::Draw(sf::RenderWindow& window)
{
	DrawBackground(window);
	window.draw(this->sprite);
	DrawBorder(window);
	window.draw(text);
}
void ButtonWithImage::PollEvent(const sf::Event& event, const sf::RenderWindow& window,const sf::Vector2f& pos)
{
	Button::PollEvent(event,window,pos);
}


bool ButtonWithImage::IsPressed()
{
	return Button::IsPressed();
}
bool ButtonWithImage::IsReleased()
{
	return Button::IsReleased();
}
bool ButtonWithImage::IsClicked()
{
	return Button::IsClicked();
}


void ButtonWithImage::MakeUnclick()
{
	Button::MakeUnclick();
}
void ButtonWithImage::Reset()
{
	Button::Reset();
}







void ButtonWithImage::SetFont(const sf::Font& font)
{
	Button::SetFont(font);
}
void ButtonWithImage::SetText(const sf::Text& text)
{
	Button::SetText(text);
}
void ButtonWithImage::SetTextString(const sf::String& string)
{
	float tx=text.getPosition().x,ty=text.getPosition().y;
	Button::SetTextString(string);
	text.setPosition(tx,ty);
}
void ButtonWithImage::SetTextSize(const unsigned int size)
{
	Button::SetTextSize(size);
}
const sf::String& ButtonWithImage::GetTextString()const
{
	return Button::GetTextString();
}
const sf::Text& ButtonWithImage::GetText()const
{
	return Button::GetText();
}
const sf::Font* ButtonWithImage::GetFont()const
{
	return Button::GetFont();
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
	ImageVisible=true;
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
	this->text.move(offset);
	this->sprite.move(offset);
}
#endif
