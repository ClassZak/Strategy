#ifndef STATE_BUTTON_H
#define STATE_BUTTON_H
#include "Button.h"
class StateButton : public Button
{
public:
//Button interface
	StateButton();
	StateButton(int x,int y,int w,int h);
	~StateButton();
	
	void Draw(sf::RenderWindow& window) override;
	void PollEvent(const sf::Event& event,const sf::RenderWindow& window,const sf::Vector2f& pos);
	StateButton& operator=(const StateButton& other);

	void Reset();
//State button interface
	bool IsEnabled()const;
protected:
	bool enabled;	
};
#endif
