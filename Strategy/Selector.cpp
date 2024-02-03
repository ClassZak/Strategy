#ifndef SELECTOR_CPP
#define SELECTOR_CPP
#include "Selector.h"
Selector::Selector()
{
	this->visible=this->doSelection=this->selectionStarted=this->selected=this->selectionFailed=false;
	this->state=this->ALL;
	
	this->cornerCoordinates=new sf::Vector2f[2];
	this->cornerCoordinates[0]=sf::Vector2f(0,0);
	this->cornerCoordinates[1]=sf::Vector2f(0,0);
}
Selector::~Selector()
{
	delete [] this->cornerCoordinates;
}




bool Selector::getVisible()const
{
	return this->visible;
}
bool Selector::getDoSelection()const
{
	return this->doSelection;
}
Selector::State Selector::getState()const
{
	return this->state;
}


void Selector::checkCorners()
{
	if(cornerCoordinates[0].x>cornerCoordinates[1].x)
	{
		float x=cornerCoordinates[0].x;
		cornerCoordinates[0].x=cornerCoordinates[1].x;
		cornerCoordinates[1].x=x;
	}
	if(cornerCoordinates[0].y>cornerCoordinates[1].y)
	{
		float y=cornerCoordinates[0].y;
		cornerCoordinates[0].y=cornerCoordinates[1].y;
		cornerCoordinates[1].y=y;
	}
}


void Selector::pollEvent
(
	sf::Event& event,
	const sf::RenderWindow& window,
	const sf::Vector2f& pos,
	const sf::Vector2f& GUIPos,
	const std::list<GameObject*>& objects
)
{
	if
	(
		!((GUIPos.x>Global::LEFT_EDGE_LENGTH and GUIPos.y<Global::WINDOW_HEIGHT-Global::DOWN_EDGE_LENGTH) and
		(GUIPos.x<Global::WINDOW_WIDTH and GUIPos.y>0.f))
		and !doSelection
	)
	{
		selectionFailed=true;
		return;
	}
	else
	selectionFailed=false;
	
	if(Global::ReleasedMouseButtons::lMouseReleased)
	{
		doSelection=false;
		if(cornerCoordinates[0]==cornerCoordinates[1])
		selected=false;
	}
	
	
	if(Global::ReleasedMouseButtons::lMousePressed and !selectionFailed)
	{
		if(!doSelection)
		{
			doSelection=true;
			cornerCoordinates[0]=cornerCoordinates[1]=pos;
		}
		else
		{
			cornerCoordinates[1]=pos;
			selected=true;
		}
	}
	
	if(Global::ReleasedMouseButtons::rMouseReleased)
	{
		if(!doSelection)
		cornerCoordinates[0]=cornerCoordinates[1]=pos;
	}
}


void Selector::draw(sf::RenderWindow& window)
{
	if(!doSelection)
	this->checkCorners();
	sf::VertexArray line(sf::Lines,8);
	line[0].position=sf::Vector2f(cornerCoordinates[0].x,cornerCoordinates[0].y);
	line[1].position=sf::Vector2f(cornerCoordinates[1].x,cornerCoordinates[0].y);
	
	line[2].position=sf::Vector2f(cornerCoordinates[1].x,cornerCoordinates[0].y);
	line[3].position=sf::Vector2f(cornerCoordinates[1].x,cornerCoordinates[1].y);
	
	line[4].position=sf::Vector2f(cornerCoordinates[1].x,cornerCoordinates[1].y);
	line[5].position=sf::Vector2f(cornerCoordinates[0].x,cornerCoordinates[1].y);
	
	line[6].position=sf::Vector2f(cornerCoordinates[0].x,cornerCoordinates[1].y);
	line[7].position=sf::Vector2f(cornerCoordinates[0].x,cornerCoordinates[0].y);
	for(short i=0;i<8;++i)
	line[i].color=sf::Color::Black;
	
	
	window.draw(line);
}
#endif
