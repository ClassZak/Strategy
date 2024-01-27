#ifndef STANDART_SOLDIER_H
#define STANDART_SOLDIER_H
#include "Unit.h"
struct Loader;
class Saver;
class StandartSoldier : public Unit
{
friend Loader;
friend Saver;
public:
	StandartSoldier();
	StandartSoldier(int x,int y,int w,int h,const sf::Texture* texture);
	StandartSoldier(int x,int y,int w,int h);
	~StandartSoldier()override;
	
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
	sf::Vector2f GetSize()const;
	
	
	void Draw(const sf::RenderWindow& window)override;
	void Update
	(
		sf::RenderWindow& window,
		const sf::Event& event,
		const sf::Vector2f& mousePos,
		std::list<GameObject*>& objects
	);
	void Update
	(
		sf::RenderWindow& window,
		const sf::Vector2f& mousePos,
		std::list<GameObject*>& objects
	);
	
	
	
	friend std::istream& operator>>(std::istream& in,StandartSoldier& ob);
	friend std::ostream& operator<<(std::ostream& out,const StandartSoldier& ob);
	
	
protected:
	void DrawHp(const sf::RenderWindow& window);
};
#endif
