#ifndef GAME_FUNCTIONS_H
#define GAME_FUNCTIONS_H
#pragma once

#include <SFML/Graphics.hpp>
#include <windows.h>
#include <iostream>
#include <locale>
#include <thread>
#include <sstream>
#include <vector>
#include <list>
#include <iterator>
#include <string>
#include <memory>
#include <stdlib.h>

#include "Functions.h"

#include "ButtonWithImage.h"
#include "OverlayPanel.h"
#include "StandartSoldier.h"

#include "Loader.h"
#include "Saver.h"
#include "Global.h"

#include "Selector.h"
#include "InputField.h"


//#define MENU_BACKGROUND_COLOR sf::Color(170,170,170)
//#define BACKGROUND_COLOR sf::Color(230,230,230)
#define MENU_BACKGROUND_COLOR sf::Color(210,210,210)
#define BACKGROUND_COLOR sf::Color(210,210,210)
#define BACKGROUND_LINE_COLOR sf::Color(130,130,130)
//#define USE_SMART_POINTERS

#ifndef USE_SMART_POINTERS
std::list<GameObject*>ChooseGameObjects(const std::list<Object*>& objects);
std::list<GameObject*>ChooseGameObjects(const std::list<GUIObject*>& objects);
std::list<GameObject*>ChooseGameObjects(const std::list<GameObject*>& objects);
#else
std::list<std::auto_ptr<GameObject>>ChooseGameObjects(const std::list<std::auto_ptr<Object>>& objects);
std::list<std::auto_ptr<GameObject>>ChooseGameObjects(const std::list<std::auto_ptr<GUIObject>>& objects);
std::list<std::auto_ptr<GameObject>>ChooseGameObjects(const std::list<std::auto_ptr<GameObject>>& objects);
#endif
void ShowMousePosition
(sf::RenderWindow& window,const sf::Vector2f& mousePos,const sf::Vector2f& coordinates,sf::Font& font);
void DrawPoint(sf::RenderWindow& window, sf::Vector2f& mouse_pos);
void MoveView(sf::View& view,sf::RenderWindow& window,const sf::Event& event,std::list<GUIObject*>&GUI);
void ChangeViewScale(sf::Event& event,sf::View& view,sf::RenderWindow& window,const sf::Vector2f& mousePos);
void MoveGUIObjects(const sf::Vector2f& vector,std::list<GUIObject*>&GUI);
#ifndef USE_SMART_POINTERS
template<typename T>
void Drawing(sf::RenderWindow& window,std::list<T*,std::allocator<T*>> &objects)
{
	for (auto it=objects.begin();it!=objects.end();++it)
	{
		if(ButtonWithImage* buttonWithImage = dynamic_cast<ButtonWithImage*>(*it))
		buttonWithImage->Draw(window);
    	else if(Button* b=dynamic_cast<Button*>(*it))
		b->Draw(window);
        else if(StandartSoldier* s=dynamic_cast<StandartSoldier*>(*it))
        s->Draw(window);
        else if(OverlayPanel* p=dynamic_cast<OverlayPanel*>(*it))
        p->Draw(window);
        else if(InputField* iF=dynamic_cast<InputField*>(*it))
        iF->Draw(window);
    }
}
template<typename T>
void ObjectPollEvent(sf::RenderWindow& window,sf::Event& event,std::list<T*,std::allocator<T*>>* objects)
{
	sf::Vector2f mouse_pos=window.mapPixelToCoords(sf::Mouse::getPosition(window));
	std::list<GameObject*>GameObjects;
	if(typeid(T).name()!=typeid(GameObject).name())
	GameObjects=ChooseGameObjects(*objects);
	
	for(auto it=objects->begin();it!=objects->end();++it)
	{
		if(ButtonWithImage* buttonWithImage=dynamic_cast<ButtonWithImage*>(*it))
		buttonWithImage->PollEvent(event,window,mouse_pos);
		else
		if(Button* button=dynamic_cast<Button*>(*it))
		button->PollEvent(event,window,mouse_pos);
		else
		if(StandartSoldier* soldier=dynamic_cast<StandartSoldier*>(*it))
		{
			soldier->Update(window,event,mouse_pos,GameObjects);
			soldier->AddHp(1);
		}
		else
		if(InputField* field=dynamic_cast<InputField*>(*it))
		{
			field->PollEvent(event,window,mouse_pos);
		}
    }
}
void CheckSettingsButtons(std::list<Object*>& buttons);
void CheckSettingsButtons(std::list<Button*>& buttonsList);
#endif
void ObjectUpdate(sf::RenderWindow& window,std::list<GameObject*>& objects);
void CheckMainButtons(std::vector<Button>& MainButtons);
void CheckInGameButtons(std::list<GUIObject*>* GUIObjects);
int MainMenu(sf::RenderWindow& window);
int GameField(sf::RenderWindow& window,std::list<GameObject*>* objects);
int SettingsMenu(sf::RenderWindow& window);
template<typename T>
int SaveObjects(std::list<T*,std::allocator<T*>>& objects)
{
	sf::Clock savingTime;
	unsigned long long objectsCount=Saver::SaveObjects(objects);
	std::cout<<objectsCount<<" objects saved"<<std::endl<<
	"Saving time:"<<savingTime.getElapsedTime().asSeconds()<<" sec."<<std::endl;
}
int LoadObjects(std::list<Object*>* objects, const char* filename = SavedObjects);


std::vector<Button> CreateMainButtons
(
	sf::Font& font,
	sf::Vector2f& buttonDimensions,
	std::vector<sf::String>& buttonLabels,
	const unsigned short distance=10
);
std::vector<ButtonWithImage> CreateButtonsWithImage
(
	sf::Font& font,
	sf::Texture& texture,
	std::vector<sf::String>& buttonLabels,
	std::size_t count=1
);
std::vector<ButtonWithImage> CreateButtonsWithImage
(
	sf::Texture& texture,
	std::size_t count=1
);
ButtonWithImage CreateButtonWithImage(sf::Texture& texture,const sf::Vector2f& pos,const sf::Vector2f& imPos);
ButtonWithImage CreateButtonWithImage
(
	sf::Texture& texture,
	const sf::Vector2f& pos,
	const sf::Vector2f& imPos,
	const sf::String& label,
	sf::Font& font,
	const sf::Vector2f& txPos,
	unsigned int size=15
);





//Smart pointers
#ifdef USE_SMART_POINTERS
void CheckSettingsButtons(std::list<std::auto_ptr<Button>>& buttonsList);
template<typename T>
void ObjectPollEvent
(
	sf::RenderWindow& window,
	sf::Event& event,
	std::list<std::auto_ptr<T>,std::allocator<std::auto_ptr<T>>> &objects
)
{
	sf::Vector2f mouse_pos=window.mapPixelToCoords(sf::Mouse::getPosition(window));
	std::list<std::auto_ptr<GameObject>>GameObjects;
	if(typeid(T).name()!=typeid(GameObject).name())
	GameObjects=ChooseGameObjects(objects);
	
	for(auto it=objects.begin();it!=objects.end();++it)
	{
		if(ButtonWithImage* buttonWithImage=dynamic_cast<ButtonWithImage*>(it->get()))
		buttonWithImage->PollEvent(event,window,mouse_pos);
		else
		if(Button* button=dynamic_cast<Button*>(it->get()))
		button->PollEvent(event,window,mouse_pos);
		else
		if(StandartSoldier* soldier=dynamic_cast<StandartSoldier*>(it->get()))
		{
			soldier->Update(window,event,mouse_pos,GameObjects);
			soldier->AddHp(1);
		}
		else
		if(InputField* field=dynamic_cast<InputField*>(it->get()))
		{
			field->PollEvent(event,window,mouse_pos);
		}
    }
}

template<typename T>
void Drawing(sf::RenderWindow& window,std::list<std::auto_ptr<T>,std::allocator<std::auto_ptr<T>>> &objects)
{
	for (auto it=objects.begin();it!=objects.end();++it)
	{
		if(ButtonWithImage* buttonWithImage = dynamic_cast<ButtonWithImage*>(it->get()))
		buttonWithImage->Draw(window);
    	else if(Button* b=dynamic_cast<Button*>(it->get()))
		b->Draw(window);
        else if(StandartSoldier* s=dynamic_cast<StandartSoldier*>(it->get()))
        s->Draw(window);
        else if(OverlayPanel* p=dynamic_cast<OverlayPanel*>(it->get()))
        p->Draw(window);
        else if(InputField* iF=dynamic_cast<InputField*>(it->get()))
        iF->Draw(window);
    }
}
#endif








#endif
