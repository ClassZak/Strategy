#ifndef INPUT_FIELD_H
#define INPUT_FIELD_H

#include "Object.h"
#include <basetsd.h>

class InputField : public PlacedGUIObject
{
private:
	InputField();
public:
	InputField(int x,int y,int w,int h,const std::wstring& textString);
	InputField(int x,int y,int w,int h);
	~InputField()override;
	void Draw(sf::RenderWindow& window)override;
	
	
	void PollEvent(const sf::Event& event,const sf::RenderWindow& window,const sf::Vector2f& pos);
	
	void setTextString(const std::wstring& textString);
	void setText(const sf::Text& text);
	void setTextParametres(const sf::Font& font,unsigned int charSize=16u);
	void setTextParametres(const std::wstring& textString,const sf::Font& font,unsigned int charSize=16u);
	
	sf::Text getText();
	std::wstring getTextString()const;
	const sf::Font* getFont()const;
	
	bool isInputing()const;
protected:
	sf::Text text,bottomText;
	std::wstring textString;
	UINT64 cursorPos=1;
	bool inputs;
	
	virtual void charInput(const sf::Event& event);
	void lineBreak();
	
	
	/*friend template<typename T>
	void ObjectPollEvent(sf::RenderWindow& window,sf::Event& event,std::list<T*,std::allocator<T*>> &objects);*/
};
#endif
