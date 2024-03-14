#pragma once
#include "Button.h"
#include "Global.h"
class ButtonWithImage : public Button
{
private:
friend void MoveView
(sf::View& view,sf::RenderWindow& window,const sf::Event& event,std::list<GUIObject*>&GUI);

public:
	ButtonWithImage();
	ButtonWithImage(int x,int y,int w,int h);
	ButtonWithImage(int x,int y,int w,int h,sf::Texture& texture);
	ButtonWithImage& operator=(const ButtonWithImage& other);
	
	~ButtonWithImage();
	
	
//Object interface
	void SetTexture(const sf::Texture& texture);
	void SetSprite(const sf::Sprite& sprite);
	const sf::Sprite& GetSprite()const;
	const sf::Texture& GetTexture()const;
	
//Button interface
	void Draw(sf::RenderWindow& window);
	
//Image and text settings
	void SetTextPos(const sf::Vector2f& pos);
	void SetImagePos(const sf::Vector2f& pos);
	const sf::Vector2f& GetTextPos()const;
	const sf::Vector2f& GetImagePos()const;
	
	
	void SetImageVisible(const bool is=true);
	void SetTextVisible(const bool is=true);
	bool ImageIsVisible()const;
	bool TextIsVisible()const;
	
	void Move(const sf::Vector2f& offset);
protected:
	
	sf::Texture texture;
	sf::Sprite sprite;
	
	void Set();
	bool ImageVisible;
	bool TextVisible;
};
