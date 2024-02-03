#pragma once

#include "GameFunctions.h"

void MoveGUIObjects(const sf::Vector2f& vector,std::list<GUIObject*>&GUI)
{
	for(auto i=GUI.begin();i!=GUI.end();++i)
	{
		if(ButtonWithImage* buttonWithImage=dynamic_cast<ButtonWithImage*>(*i))
		buttonWithImage->Move(vector);
		if(Button* button=dynamic_cast<Button*>(*i))
		button->Move(vector);
		if(OverlayPanel* overlayPanel=dynamic_cast<OverlayPanel*>(*i))
		overlayPanel->Move(vector);
	}
}
void MoveView(sf::View& view,sf::RenderWindow& window,const sf::Event& event,std::list<GUIObject*>&GUI)
{
	if(Global::ReleasedKeys::GetPressed(Global::ReleasedKeys::Left)or 
	Global::ReleasedKeys::GetPressed(Global::ReleasedKeys::A))
	{
		view.move(-Global::viewDelta*std::pow(Global::zoom,Global::scrolledUpTimes-Global::scrolledDownTimes),0);
	}
	if(Global::ReleasedKeys::GetPressed(Global::ReleasedKeys::Right)or 
	Global::ReleasedKeys::GetPressed(Global::ReleasedKeys::D))
	{
		view.move(Global::viewDelta*std::pow(Global::zoom,Global::scrolledUpTimes-Global::scrolledDownTimes),0);
	}
	if(Global::ReleasedKeys::GetPressed(Global::ReleasedKeys::Up)or 
	Global::ReleasedKeys::GetPressed(Global::ReleasedKeys::W))
	{
		view.move(0,-Global::viewDelta*std::pow(Global::zoom,Global::scrolledUpTimes-Global::scrolledDownTimes));
	}
	if(Global::ReleasedKeys::GetPressed(Global::ReleasedKeys::Down)or 
	Global::ReleasedKeys::GetPressed(Global::ReleasedKeys::S))
	{
		view.move(0,Global::viewDelta*std::pow(Global::zoom,Global::scrolledUpTimes-Global::scrolledDownTimes));
	}
	
	window.setView(view);
}
void ChangeViewScale(sf::Event& event,sf::View& view,sf::RenderWindow& window,const sf::Vector2f& mousePos)
{
	if(event.type==sf::Event::MouseWheelScrolled)
	{
		if((event.mouseWheelScroll.delta>0))//Прокрутка вверх
		{
			if(Global::scrolledUpTimes!=Global::maxScrolledTimes)
			{
				view.zoom(Global::zoom);
				(Global::scrolledDownTimes) ? --Global::scrolledDownTimes : ++Global::scrolledUpTimes;
				
				view.move(sf::Vector2f(mousePos-window.mapPixelToCoords(sf::Mouse::getPosition(window),view)));
			}
		}
		else if(Global::scrolledDownTimes!=Global::maxScrolledTimes)
		{
			view.zoom(1.f/Global::zoom);
			(Global::scrolledUpTimes) ? --Global::scrolledUpTimes : ++Global::scrolledDownTimes;
			
			view.move(sf::Vector2f(mousePos-window.mapPixelToCoords(sf::Mouse::getPosition(window),view)));
		}
	}
	
	window.setView(view);
}



