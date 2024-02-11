#include <SFML/Graphics.hpp>
#include <windows.h>
#include <iostream>
#include <thread>
#include <sstream>
#include <vector>
#include <list>
#include <iterator>
#include <string>
#include <malloc.h>
#include <cstdio>
#include <locale>


#include "Global.h" 
#include "Functions.h"
#include "GameFunctions.h"


#include <locale>
#include <codecvt>
#include <fstream>
#include <string>



int main()
{
    setlocale(LC_ALL, "Russian");
    std::list<Object*>* objects = new std::list<Object*>;


    if (!SUCCEEDED(Global::ContentLoading()))
    {
        system("pause");
        return EXIT_FAILURE;
    }
    Global::ObjectContext::LoadObjects(objects);


    sf::RenderWindow window
    (sf::VideoMode(Global::WINDOW_WIDTH, Global::WINDOW_HEIGHT), L"Стратегия", sf::Style::Titlebar | sf::Style::Close);
    sf::Clock loadingClock;
    
    while (window.isOpen() and Global::playing)
    {
        switch (Global::room)
        {
            case Global::MENU:
            {
                MainMenu(window);
                SetConsoleTextAttribute(Global::consoleOutHandle, FOREGROUND_BLUE);
                system("pause");
                SetConsoleTextAttribute(Global::consoleOutHandle, FOREGROUND_DEFAULT);
                break;
            }
            case Global::NEW_GAME:
            {

                break;
            }
            default:
                Global::playing = false;
                break;
        }
    }
    system("pause");
    return 0;
}

