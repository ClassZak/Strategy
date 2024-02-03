#ifndef OVERLAY_PANEL_CPP
#define OVERLAY_PANEL_CPP
#include "OverlayPanel.h"
#include <limits>
OverlayPanel::OverlayPanel()
{
	this->fields=nullptr;
	rectangles=0;
}
OverlayPanel::~OverlayPanel()
{
	if(this->fields!=nullptr)
	delete [] fields;
}



void OverlayPanel::Draw(sf::RenderWindow& window)
{
	for(unsigned int i=0;i<rectangles;++i)
	window.draw(fields[i]);
}


void OverlayPanel::PushFrontRectangle(const sf::Vector2f& pos,const sf::Vector2f& dimensions,const sf::Color& color)
{
    if((rectangles+1)==std::numeric_limits<unsigned int>::max())
	throw std::runtime_error("Array size limit exceeded");
	
	
    sf::RectangleShape newRectangle(dimensions);
    newRectangle.setPosition(pos);
    newRectangle.setFillColor(color);

    sf::RectangleShape* newFields=new sf::RectangleShape[rectangles+1];
    for(unsigned int i=0;i<rectangles;++i)
    newFields[i]=fields[i];
    newFields[rectangles]=newRectangle;
    
    if(fields!=nullptr)
    delete [] fields;
    
    fields=newFields;
    ++rectangles;
}
void OverlayPanel::AddRectangle
(
	const sf::Vector2f& pos,
	const sf::Vector2f& dimensions,
	const sf::Color& color,
	const unsigned int numberOfElement
)
{
	if((rectangles+1)==std::numeric_limits<unsigned int>::max())
	throw std::runtime_error("Array size limit exceeded");
	
	if(numberOfElement>rectangles)
	throw std::runtime_error("Invalid position specified");
	
	sf::RectangleShape newRectangle(dimensions);
	newRectangle.setPosition(pos);
	newRectangle.setFillColor(color);
	
	sf::RectangleShape* newFields=new sf::RectangleShape[rectangles+1];
	for(unsigned int i=0;i<numberOfElement;++i)
	newFields[i]=fields[i];
	newFields[numberOfElement]=newRectangle;
	
	for (unsigned int i=numberOfElement;i<rectangles;++i)
	newFields[i+1]=fields[i];
	
	
	if(fields!=nullptr)
	delete [] fields;
	
	fields=newFields;
	++rectangles;
}
void OverlayPanel::RemoveRectangle(const unsigned int pos)
{
	if(pos>rectangles)
	throw std::runtime_error("Invalid position specified");
	else
	{
		if(rectangles==1)
		{
			fields=nullptr;
			rectangles=0;
		}
		else if(!rectangles)
		throw std::runtime_error("Array size limit exceeded");
		else
		{
			unsigned int i;
			sf::RectangleShape* tempFields=new sf::RectangleShape[rectangles-1];
			for(i=0;i<pos;++i)
			tempFields[i]=fields[i];
			for(++i;i<rectangles;++i)
			tempFields[i]=fields[i];
			
			if(fields!=nullptr)
			delete [] fields;
			
			--rectangles;
			fields=tempFields;
		}
	}
}


void OverlayPanel::Move(const sf::Vector2f& offset)
{
	for(auto i=0;i<this->rectangles;++i)
	this->fields[i].move(offset);
}
#endif
