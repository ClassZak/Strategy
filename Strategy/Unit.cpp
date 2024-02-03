#ifndef UNIT_CPP
#define UNIT_CPP
#include "Unit.h"
Unit::Unit():GameObject::GameObject()
{
	Unit::Set();
}
Unit::Unit(int x,int y,int w,int h):GameObject::GameObject(x,y,w,h)
{
	Unit::Set();
}
Unit::Unit(int x,int y,int w,int h, sf::Texture* texture):GameObject::GameObject(x,y,w,h,texture)
{
	Unit::Set();
}
Unit::~Unit()
{
}






void Unit::SetCoordinates(const sf::Vector2f& pos)
{
	GameObject::SetCoordinates(pos);
}
void Unit::SetTexture(sf::Texture* texture)
{
	GameObject::SetTexture(texture);
}
void Unit::SetSprite(const sf::Sprite& sprite)
{
	GameObject::SetSprite(sprite);
}
void Unit::SetHp(const unsigned int hp)
{
	this->hp=hp;
}
void Unit::SetMaxHp(const unsigned int maxHp)
{
	this->maxHp=maxHp;
}
void Unit::SetSize(const sf::Vector2f& size)
{
	GameObject::SetSize(size);
}


sf::Vector2f Unit::GetCoordinates()const
{
	return GameObject::GetCoordinates();
}
const sf::Sprite& Unit::GetSprite()const
{
	return GameObject::GetSprite();
}
const sf::Texture* Unit::GetTexture()const
{
	return GameObject::GetTexture();
}
unsigned int Unit::GetHp()const
{
	return this->hp;
}
unsigned int Unit::GetMaxHp()const
{
	return this->maxHp;
}

bool Unit::IsAlive()const
{
	return this->live;
}


void Unit::AddHp(const unsigned int hp)
{
	if(hp>this->maxHp-this->hp)
	this->hp=maxHp;
	else
	this->hp+=hp;
}
void Unit::TakeHp(const unsigned int hp)
{
	if(this->hp<hp)
	this->hp=0;
	else
	this->hp-=hp;
}




sf::Vector2f Unit::GetSize()const
{
	return GameObject::GetSize();
}




void Unit::Update
(
	sf::RenderWindow& window,
	const sf::Event& event,
	const sf::Vector2f& mousePos,
	std::list<GameObject*>& objects
)
{
	Unit::CheckHp();
}
void Unit::Update
(
	sf::RenderWindow& window,
	const sf::Vector2f& mousePos,
	std::list<GameObject*>& objects
)
{
	Unit::CheckHp();
}
/*
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
													Protected
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/
void Unit::DrawHp(sf::RenderWindow& window)
{
	float health=static_cast<float>(this->hp)/static_cast<float>(this->maxHp);
	float healthWidth=w*health;
	sf::RectangleShape rect[2]=
	{
		sf::RectangleShape(sf::Vector2f(w,sqrt(h)+((h==0)*3))),
		sf::RectangleShape(sf::Vector2f((healthWidth-2)*(healthWidth>2),sqrt(h)-2*(h!=0)+(h==0)))
	};
	rect[0].setFillColor(sf::Color::Black);
	rect[1].setFillColor(sf::Color::Green);
	rect[0].setPosition(this->x-w/2,this->y-w/2-w/4);
	rect[1].setPosition(rect[0].getPosition());
	rect[1].move(1,1);
	
	window.draw(rect[0]);
	window.draw(rect[1]);
}

void Unit::Set()
{
	this->maxHp=this->hp=100;
	this->live=true;
}
void Unit::CheckHp()
{
	if(this->hp>this->maxHp)
	this->hp=this->maxHp;
	if(!this->hp)
	this->live=false;
}
/*
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
													Operators
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/
std::istream& operator>>(std::istream& in,Unit& ob)
{
	in>>ob.x>>ob.y>>ob.w>>ob.h>>ob.hp>>ob.maxHp;
	return in;
}
std::ostream& operator<<(std::ostream& out,const Unit& ob)
{
	out<<ob.x<<' '<<ob.y<<' '<<ob.w<<' '<<ob.h<<ob.hp<<' '<<ob.maxHp;
	return out;
}
#endif
