#ifndef BUTTON_FUNCTIONS_CPP
#define BUTTON_FUNCTIONS_CPP

#include "GameFunctions.h"

void CheckMainButtons(std::vector<Button>& MainButtons)
{
	if (MainButtons[0].IsClicked())
	{
		Global::room = Global::NEW_GAME;
		Global::view = Global::standartView;
	}
	if (MainButtons[1].IsClicked())
	{
		if (Global::gameStarted)
			Global::room = Global::CONTINUE;
	}
	if (MainButtons[2].IsClicked())
	{
		Global::room = Global::LOADING;
		Global::view = Global::standartView;
		Global::scrolledDownTimes = 0;
		Global::scrolledUpTimes = 0;
	}
	if (MainButtons[3].IsClicked())
		Global::room = Global::SAVING;
	if (MainButtons[4].IsClicked())
		Global::room = Global::SETTINGS;
	if (MainButtons[5].IsClicked())
		Global::playing = false;
}



void CheckInGameButtons(std::list<GUIObject*>* GUIObjects)
{
	std::size_t number=0;
	for(std::list<GUIObject*>::iterator i=GUIObjects->begin();i!=GUIObjects->end();++i)
	{
		if(PlacedGUIObject* gui=dynamic_cast<PlacedGUIObject*>(*i))
		{
			if(Button* currButton=dynamic_cast<Button*>(*i))
			{
				if(currButton->IsClicked())
				switch(number)
				{
					case 0:
					{
						Global::room=Global::MENU;
						break;
					}
					case 1:
					{
						Global::fromMenu = bool(Global::room == Global::MENU);
						Global::room=Global::SETTINGS;
						break;
					}
					default:
					throw std::runtime_error("Uncorrect Button");
				}
			}
			++number;
		}
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CheckSettingsButtons(std::list<Object*>& buttons)
{
	std::size_t number=0;
	for(std::list<Object*>::iterator i=buttons.begin();i!=buttons.end();++i)
	{
		if(ButtonWithImage* buttonWithImage=dynamic_cast<ButtonWithImage*>(*i))
		{
			if(buttonWithImage->IsClicked())
			switch(number)
			{
				case 0:
				{
					Global::room=Global::MENU;
					break;
				}
				case 1:
				{
					Global::room=Global::CONTINUE;
					break;
				}
				default:
				throw std::runtime_error("Uncorrect Button");
			}
		}
		else
		if(Button* button=dynamic_cast<Button*>(*i))
		{
			
		}
		++number;
	}
}
#ifdef USE_SMART_POINTERS
void CheckSettingsButtons(std::list<std::auto_ptr<Button>>& buttonsList)
{
	std::size_t number=0;
	for(auto i=buttonsList.begin();i!=buttonsList.end();++i)
	{
		if(ButtonWithImage* buttonWithImage=dynamic_cast<ButtonWithImage*>(i->get()))
		{
			if(buttonWithImage->IsClicked())
			switch(number)
			{
				case 0:
				{
					Global::room=Global::MENU;
					break;
				}
				case 1:
				{
					(Global::fromMenu) ? Global::room=Global::MENU : Global::room=Global::GAME_FIELD;
					break;
				}
				default:
				throw std::runtime_error("Uncorrect Button");
			}
		}
		else
		if(Button* button=dynamic_cast<Button*>(i->get()))
		{
			
		}
		++number;
	}
}
#else
void CheckSettingsButtons(std::list<Button*>& buttonsList)
{
	std::size_t number=0;
	for(auto i=buttonsList.begin();i!=buttonsList.end();++i)
	{
		if(ButtonWithImage* buttonWithImage=dynamic_cast<ButtonWithImage*>(*i))
		{
			if(buttonWithImage->IsClicked())
			switch(number)
			{
				case 0:
				{
					Global::room=Global::MENU;
					break;
				}
				case 1:
				{
					Global::room = (Global::fromMenu) ? Global::MENU : Global::CONTINUE;
					break;
				}
				default:
				throw std::runtime_error("Uncorrect Button");
			}
		}
		else
		if(Button* button=dynamic_cast<Button*>(*i))
		{
			
		}
		++number;
	}
}
#endif
////////////////////////////////////////////////////////////////////////////////////////////////////////////////


std::vector<Button> CreateMainButtons
(
	sf::Font& font,
	sf::Vector2f& buttonDimensions,
	std::vector<sf::String>& buttonLabels,
	const unsigned short distance
)
{
	std::vector<Button> buttons;
	buttons.reserve(Global::MAIN_BUTTONS);
	
    for(short i=0;i<Global::MAIN_BUTTONS;++i)
    {
    	buttons.push_back
		(
			Button
			(
				Global::WINDOW_WIDTH/2,
				(unsigned int)
				(distance+buttonDimensions.y + i*(distance*2+buttonDimensions.y) 
				+ 
				(
					Global::WINDOW_HEIGHT-
					(distance+buttonDimensions.y + Global::MAIN_BUTTONS*(distance*2+buttonDimensions.y))
				)
				/2)
				,
				buttonDimensions.x,
				buttonDimensions.y
			)
		);
		buttons[i].SetTextSize(15);
	}
	for(std::size_t i=0;i<Global::MAIN_BUTTONS;++i)
	{
		buttons[i].SetFont(font);
		buttons[i].SetTextString(buttonLabels[i]);
	}
	
	return buttons;
}



std::vector<ButtonWithImage> CreateButtonsWithImage
(
	sf::Font& font,
	sf::Texture& texture,
	std::vector<sf::String>& buttonLabels,
	std::size_t count
)
{
	std::vector<ButtonWithImage> buttons;
	buttons.reserve(count);
	
    for(short i=0;i<count;++i)
    {
    	buttons.push_back
		(
			ButtonWithImage
			(
				0,
				0,
				texture.getSize().x,
				texture.getSize().y,
				texture
			)
		);
	}
	for(std::size_t i=0;i<count;++i)
	{
		buttons[i].SetFont(font);
		buttons[i].SetTextString(buttonLabels[i]);
	}
	
	return buttons;
}



std::vector<ButtonWithImage> CreateButtonsWithImage
(
	sf::Texture& texture,
	std::size_t count
)
{
	std::vector<ButtonWithImage> buttons;
	buttons.reserve(count);
	
    for(short i=0;i<count;++i)
    {
    	buttons.push_back
		(
			ButtonWithImage
			(
				0,
				0,
				texture.getSize().x,
				texture.getSize().y,
				texture
			)
		);
	}
	return buttons;
}



ButtonWithImage CreateButtonWithImage(sf::Texture& texture,const sf::Vector2f& pos,const sf::Vector2f& imPos)
{
	ButtonWithImage b(pos.x,pos.y,texture.getSize().x,texture.getSize().y,texture);
	b.SetImagePos(imPos);
	
	return b;
}



ButtonWithImage CreateButtonWithImage
(
	const sf::Vector2f& pos,
	sf::Texture& texture,
	const sf::String& label,
	const sf::Vector2f& imPos,
	const sf::Font& font,
	const sf::Vector2f& txPos,
	const unsigned int size=15
)
{
	ButtonWithImage b(pos.x,pos.y,texture.getSize().x,texture.getSize().y,texture);
	b.SetImagePos(imPos);
	b.SetFont(font);
	b.SetTextString(label);
	b.SetTextSize(size);
	b.SetTextPos(txPos);
	
	return b;
}
#endif
