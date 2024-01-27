#ifndef STATE_BUTTON_H
#define STATE_BUTTON_H
#include "ButtonWithImage.h"
class StateButton : public Button
{
public:
//Button interface
	StateButton();
	StateButton(int x,int y,int w,int h);
	~StateButton();
	
	
	void SetCoordinates(const sf::Vector2f& pos);
	sf::Vector2f GetCoordinates()const;
	void SetSize(const sf::Vector2f& size);
	sf::Vector2f GetSize()const;
	
	
	void Draw(const sf::RenderWindow& window) override;
	
	
	bool IsPressed();
	bool IsReleased();
	
	void PollEvent(const sf::Event& event,const sf::RenderWindow& window,const sf::Vector2f& pos);
	
	
	void SetFont(const sf::Font& font);
	void SetText(const sf::Text& text);
	void SetTextString(const sf::String& string);
	void SetTextSize(const unsigned int size);
	const sf::String& GetTextString()const;
	const sf::Text& GetText()const;
	const sf::Font* GetFont()const;
	
	StateButton& operator=(const StateButton& other);
	
	void MakeUnclick();
	void Reset();
	bool IsClicked();
	
	
	
	friend std::istream& operator>>(std::istream& in,StateButton& ob);
	friend std::ostream& operator<<(std::ostream& out,const StateButton& ob);
//State button interface
	bool IsEnabled()const;
protected:
	bool enabled;	
};
#endif
