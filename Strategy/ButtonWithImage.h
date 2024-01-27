#ifndef B_H
#define B_H
#include "Button.h"
class ButtonWithImage : public Button
{
private:
friend void MoveView(sf::View& view,sf::RenderWindow& window,const sf::Event& event,std::list<GUIObject*>&GUI);
friend std::istream& operator>>(std::istream& in,ButtonWithImage& ob);
friend std::ostream& operator<<(std::ostream& out,const ButtonWithImage& ob);

public:
	ButtonWithImage();
	ButtonWithImage(int x,int y,int w,int h);
	ButtonWithImage(int x,int y,int w,int h,sf::Texture& texture);
	ButtonWithImage& operator=(const ButtonWithImage& other);
	
	~ButtonWithImage();
	
	
//Object interface
	void SetCoordinates(const sf::Vector2f& pos);
	void SetTexture(const sf::Texture& texture);
	void SetSprite(const sf::Sprite& sprite);
	sf::Vector2f GetCoordinates()const;
	const sf::Sprite& GetSprite()const;
	const sf::Texture& GetTexture()const;
	
	
	
//Button interface
	void Draw(const sf::RenderWindow& window);
	
	
	bool IsPressed();
	bool IsReleased();
	
	void PollEvent(const sf::Event& event, const sf::RenderWindow& window, const sf::Vector2f& pos);
	
	
	void SetFont(const sf::Font& font);
	void SetText(const sf::Text& text);
	void SetTextString(const sf::String& string);
	void SetTextSize(const unsigned int size);
	void SetSize(const sf::Vector2f& size);
	sf::Vector2f GetSize()const;
	const sf::String& GetTextString()const;
	const sf::Text& GetText()const;
	const sf::Font* GetFont()const;
	
	
	void MakeUnclick();
	void Reset();
	bool IsClicked();
	
//Image and text settings
	void SetTextPos(const sf::Vector2f& pos) const;
	void SetImagePos(const sf::Vector2f& pos)const;
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
#endif