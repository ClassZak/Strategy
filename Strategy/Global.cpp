#pragma once
#include "Global.h"

HANDLE Global::consoleOutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
sf::Vector2f Global::PixelSizes = []() -> sf::Vector2f
{
	SetProcessDPIAware();
	HDC screen = GetDC(NULL);
	int dpiX = GetDeviceCaps(screen, LOGPIXELSX);
	int dpiY = GetDeviceCaps(screen, LOGPIXELSY);
	ReleaseDC(NULL, screen);

	std::cout << "DPI sizes:" << std::endl << "w:" << dpiX << "\th:" << dpiY << std::endl;
	return sf::Vector2f(dpiX, dpiY);
}();
sf::Vector2f Global::PSizes = sf::Vector2f();
INT Global::DPI = 0;

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

sf::View Global::view = sf::View();
sf::View Global::standartView = sf::View();


sf::Font Global::font =
[]()->sf::Font {sf::Font font; font.loadFromFile("resources/Fonts/ARIALUNI.TTF"); return font; }();
sf::Font Global::monoFont = 
[]()->sf::Font {sf::Font font; font.loadFromFile("resources/Fonts/consola.TTF"); return font; }();


UINT16 Global::WINDOW_WIDTH=600;
UINT16 Global::WINDOW_HEIGHT=480;

UINT16 Global::FPS = 60;
double Global::zoom = 0.7;
double Global::viewDelta = 1.2;

INT Global::ContentLoading()
{
	try
	{
		Global::Localizator::LoadLocaledText();
		Global::TexturesContext::LoadImages();
		Global::TexturesContext::InitTextures();
		Global::SettinsContext::LoadGlobalVariables();
	


		Global::WINDOW_WIDTH = (UINT16)Global::SettinsContext::GetGlobalVariables().find(L"WINDOW_WIDTH")->second;
		Global::WINDOW_HEIGHT = (UINT16)Global::SettinsContext::GetGlobalVariables().find(L"WINDOW_HEIGHT")->second;

		Global::FPS = (UINT16)Global::SettinsContext::GetGlobalVariables().find(L"FPS")->second;
		Global::zoom = Global::SettinsContext::GetGlobalVariables().find(L"zoom")->second;
		Global::viewDelta = Global::SettinsContext::GetGlobalVariables().find(L"viewDelta")->second;



		Global::view = sf::View
		(
			sf::Vector2f(Global::WINDOW_WIDTH / 2, Global::WINDOW_HEIGHT / 2),
			sf::Vector2f(Global::WINDOW_WIDTH, Global::WINDOW_HEIGHT)
		);
		Global::standartView = sf::View
		(
			sf::Vector2f(Global::WINDOW_WIDTH / 2, Global::WINDOW_HEIGHT / 2),
			sf::Vector2f(Global::WINDOW_WIDTH, Global::WINDOW_HEIGHT)
		);

		return EXIT_SUCCESS;
	}
	catch (const std::exception& ex)
	{
		HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		std::wcout << L"Исключение в главной функции!" << std::endl;
		SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
		std::cerr << ex.what() << std::endl;
		SetConsoleTextAttribute(consoleHandle, FOREGROUND_INTENSITY - 1);
		system("pause");
		return EXIT_FAILURE;
	}
}
