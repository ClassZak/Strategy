#pragma once
#ifndef OBJECT_H
#define OBJECT_H
#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>
#include <memory>

//Friiend functions' declaration
class GUIObject;
void MoveView(sf::View& view, sf::RenderWindow& window, const sf::Event& event, std::list<GUIObject*>& GUI);

class Object
{
public:
	Object();
	~Object();
	virtual void Draw(const sf::RenderWindow& window) = 0;
};



class GUIObject : public Object
{
public:
	GUIObject();
	virtual ~GUIObject();
	virtual void Draw(const sf::RenderWindow& window) = 0;
};
class PlacedGUIObject : public GUIObject
{
public:
	PlacedGUIObject();
	virtual~PlacedGUIObject();
	PlacedGUIObject(int x, int y, int w, int h);

	virtual void Draw(const sf::RenderWindow& window) = 0;
	void SetCoordinates(const sf::Vector2f& pos);
	sf::Vector2f GetCoordinates()const;
	void SetSize(const sf::Vector2f& size);
	sf::Vector2f GetSize()const;
protected:
	int x, y, w, h;
};

class Selector;
class GameObject : public Object
{
public:
	GameObject();
	GameObject(int x, int y, int w, int h, const sf::Texture* texture);
	GameObject(int x, int y, int w, int h);
	virtual~GameObject();

	void SetCoordinates(const sf::Vector2f& pos);
	void SetTexture(const sf::Texture* texture);
	void SetSprite(const sf::Sprite& sprite);
	void SetSize(const sf::Vector2f& size);

	sf::Vector2f GetCoordinates()const;
	const sf::Sprite& GetSprite()const;
	const sf::Texture* GetTexture()const;
	sf::Vector2f GetSize()const;

	virtual void Update
	(
		sf::RenderWindow& window,
		const sf::Event& event,
		const sf::Vector2f& mousePos,
		std::list<GameObject*>& objects
	) = 0;
	virtual void Update
	(
		sf::RenderWindow& window,
		const sf::Vector2f& mousePos,
		std::list<GameObject*>& objects
	) = 0;
protected:
	friend Selector;
	int x, y, w, h;
	sf::Texture* texture;
	sf::Sprite sprite;
	bool selected;
};
#endif