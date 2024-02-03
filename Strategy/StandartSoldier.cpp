#ifndef STANDART_SOLDIER
#define STANDART_SOLDIER
#include "StandartSoldier.h"
StandartSoldier::StandartSoldier():Unit::Unit()
{
}
StandartSoldier::StandartSoldier(int x,int y,int w,int h):Unit::Unit(x,y,w,h)
{
}
StandartSoldier::StandartSoldier(int x,int y,int w,int h,sf::Texture* texture):Unit::Unit(x,y,w,h,texture)
{
}
StandartSoldier::~StandartSoldier()
{
}




void StandartSoldier::SetCoordinates(const sf::Vector2f& pos)
{
	Unit::SetCoordinates(pos);
}
void StandartSoldier::SetTexture(sf::Texture* texture)
{
	Unit::SetTexture(texture);
}
void StandartSoldier::SetSprite(const sf::Sprite& sprite)
{
	Unit::SetSprite(sprite);
}
void StandartSoldier::SetHp(const unsigned int hp)
{
	Unit::SetHp(hp);
}
void StandartSoldier::SetMaxHp(const unsigned int maxHp)
{
	Unit::SetMaxHp(maxHp);
}
void StandartSoldier::SetSize(const sf::Vector2f& size)
{
	Unit::SetSize(size);
}


sf::Vector2f StandartSoldier::GetCoordinates()const
{
	return Unit::GetCoordinates();
}
const sf::Sprite& StandartSoldier::GetSprite()const
{
	return Unit::GetSprite();
}
const sf::Texture* StandartSoldier::GetTexture()const
{
	return Unit::GetTexture();
}
unsigned int StandartSoldier::GetHp()const
{
	return Unit::GetHp();
}
unsigned int StandartSoldier::GetMaxHp()const
{
	return Unit::GetMaxHp();
}
sf::Vector2f StandartSoldier::GetSize()const
{
	return Unit::GetSize();
}



void StandartSoldier::DrawHp(sf::RenderWindow& window)
{
	Unit::DrawHp(window);
}
void StandartSoldier::Draw(sf::RenderWindow& window)
{
	window.draw(this->sprite);
	this->DrawHp(window);
}
void StandartSoldier::Update
(
	sf::RenderWindow& window,
	const sf::Event& event,
	const sf::Vector2f& mousePos,
	std::list<GameObject*>& objects
)
{
	Unit::Update(window,event,mousePos,objects);
}
void StandartSoldier::Update
(
	sf::RenderWindow& window,
	const sf::Vector2f& mousePos,
	std::list<GameObject*>& objects
)
{
	Unit::Update(window,mousePos,objects);
}
#endif
