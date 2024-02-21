#ifndef GAME_FUNCTIONS_CPP
#define GAME_FUNCTIONS_CPP

#include "GameFunctions.h"

void ShowMousePosition
(sf::RenderWindow& window,const sf::Vector2f& mousePos,const sf::Vector2f& coordinates,sf::Font& font)
{
	sf::String stext[2]={"x=","y="};
	stext[0]+=std::to_string((INT32)coordinates.x);
	stext[1]+=std::to_string((INT32)coordinates.y);
	
	sf::Text position[2]={sf::Text(stext[0],font),sf::Text(stext[1],font)};
	for(unsigned short i=0;i<2;++i)
	{
		
		position[i].setPosition(mousePos);
		if(i==0)
		position[i].move(20,-14);
		else if(i==1)
		position[i].move(20,2);
		position[i].setCharacterSize(15);
		position[i].setFillColor(sf::Color::Black);
	}
	
	for(unsigned short i=0;i<2;++i)
	window.draw(position[i]);
}


void DrawPoint(sf::RenderWindow& window, sf::Vector2f& mousePos)
{
	sf::CircleShape point(2,30);
	point.setFillColor(sf::Color::Black);
	point.setOrigin(2,2);
	point.setPosition(mousePos);
	
	window.draw(point);
}



void ObjectUpdate(sf::RenderWindow& window,std::list<GameObject*>& objects)
{
	sf::Vector2f mouse_pos=window.mapPixelToCoords(sf::Mouse::getPosition(window));
	
	for(auto it=objects.begin();it!=objects.end();++it)
	{
		if(StandartSoldier* soldier=dynamic_cast<StandartSoldier*>(*it))
		soldier->Update(window,mouse_pos,objects);
    }
}


/*
int LoadObjects(std::list<Object*>& objects,const char* filename)
{
	sf::Clock loadingTime;
	objects=Loader::LoadObjects(filename);
	unsigned long long objectsCount=objects.size();
	std::cout<<objectsCount<<" objects loaded"<<std::endl<<
	"Loading time:"<<loadingTime.getElapsedTime().asSeconds()<<" sec."<<std::endl;

	return EXIT_SUCCESS;
}*/



#ifndef USE_SMART_POINTERS
std::list<GameObject*>ChooseGameObjects(const std::list<Object*>& objects)
{
	std::list<GameObject*>gameObjects;
	for (auto it = objects.begin(); it != objects.end(); ++it)
		if (dynamic_cast<GameObject*>((*it)) != nullptr)
			gameObjects.push_back(dynamic_cast<GameObject*>(*it));
	
	return gameObjects;
}
std::list<GameObject*>ChooseGameObjects(const std::list<GUIObject*>& objects)
{
	return std::list<GameObject*>();
}
std::list<GameObject*>ChooseGameObjects(const std::list<GameObject*>& objects)
{
	return objects;
}
#else
std::list<std::auto_ptr<GameObject>>ChooseGameObjects(const std::list<std::auto_ptr<Object>>& objects)
{
	std::list<std::auto_ptr<GameObject>> gameObjects;
	for(std::list<std::auto_ptr<Object>>::const_iterator it=objects.begin();it!=objects.end();++it)
	{
		if(GameObject* gameObject=dynamic_cast<GameObject*>(it->get()))
		gameObjects.push_back(std::auto_ptr<GameObject>(gameObject));
	}
	return gameObjects;
}
std::list<std::auto_ptr<GameObject>>ChooseGameObjects(const std::list<std::auto_ptr<GUIObject>>& objects)
{
	return std::list<std::auto_ptr<GameObject>>();
}
std::list<std::auto_ptr<GameObject>>ChooseGameObjects(const std::list<std::auto_ptr<GameObject>>& objects)
{
	return objects;
}
#endif
#endif
