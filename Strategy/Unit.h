#ifndef UNIT_H
#define UNIT_H
#include "Object.h"
#include <cmath>
class Unit : public GameObject
{
public:
	Unit();
	Unit(int x,int y,int w,int h,const sf::Texture* texture);
	Unit(int x,int y,int w,int h);
	virtual~Unit();
	
	void SetCoordinates(const sf::Vector2f& pos);
	void SetTexture(const sf::Texture* texture);
	void SetSprite(const sf::Sprite& sprite);
	void SetHp(const unsigned int hp);
	void SetMaxHp(const unsigned int maxHp);
	void SetSize(const sf::Vector2f& size);
	
	sf::Vector2f GetCoordinates()const;
	const sf::Sprite& GetSprite()const;
	const sf::Texture* GetTexture()const;
	unsigned int GetHp()const;
	unsigned int GetMaxHp()const;
	void AddHp(const unsigned int hp);
	void TakeHp(const unsigned int hp);
	bool IsAlive()const;
	sf::Vector2f GetSize()const;
	
	
	
	virtual void Draw(const sf::RenderWindow& window)=0;
	void Update
	(
		sf::RenderWindow& window,
		const sf::Event& event,
		const sf::Vector2f& mousePos,
		std::list<GameObject*>& objects
	)override;
	void Update
	(
		sf::RenderWindow& window,
		const sf::Vector2f& mousePos,
		std::list<GameObject*>& objects
	);
	
	
	
	
	friend std::istream& operator>>(std::istream& in,Unit& ob);
	friend std::ostream& operator<<(std::ostream& out,const Unit& ob);
protected:
	void DrawHp(const sf::RenderWindow& window);
	unsigned int hp;
	unsigned int maxHp;
	bool live;
	void CheckHp();
	void Set();
};
#endif
