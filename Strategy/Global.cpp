#pragma once
#include "Global.h"


bool Global::focus = true;
bool Global::focusLost = false;
bool Global::playing = true;
bool Global::gameStarted = false;
bool Global::fromMenu = true;
Global::Room Global::room = Global::MENU;


const unsigned short Global::maxScrolledTimes = 10;
unsigned short Global::scrolledUpTimes = 0;
unsigned short Global::scrolledDownTimes = 0;

bool Global::ReleasedMouseButtons::lMousePressed = false;
bool Global::ReleasedMouseButtons::rMousePressed = false;
bool Global::ReleasedMouseButtons::lMouseReleased = false;
bool Global::ReleasedMouseButtons::rMouseReleased = false;


const unsigned short Global::MAIN_BUTTONS = 6;

const unsigned short Global::LEFT_EDGE_LENGTH = 88;
const unsigned short Global::DOWN_EDGE_LENGTH = 32;


bool Global::ReleasedKeys::Pressed[Global::ReleasedKeys::KeyCount] =
{
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0
};
bool Global::ReleasedKeys::Released[Global::ReleasedKeys::KeyCount] =
{
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0
};

sf::View Global::view = sf::View
(
	sf::Vector2f(Global::WINDOW_WIDTH / 2, Global::WINDOW_HEIGHT / 2),
	sf::Vector2f(Global::WINDOW_WIDTH, Global::WINDOW_HEIGHT)
);

const sf::View Global::standartView = sf::View
(
	sf::Vector2f(Global::WINDOW_WIDTH / 2, Global::WINDOW_HEIGHT / 2),
	sf::Vector2f(Global::WINDOW_WIDTH, Global::WINDOW_HEIGHT)
);


sf::Font Global::font = []()->sf::Font {sf::Font font; font.loadFromFile("resources/Fonts/ARIALUNI.TTF"); return font; }();
