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


#include <locale>
#include <codecvt>
#include <fstream>
#include <string>



int main()
{
    setlocale(LC_ALL, "Russian");
    sf::RenderWindow window(sf::VideoMode(Global::WINDOW_WIDTH, Global::WINDOW_HEIGHT), L"Стратегия", sf::Style::Default);

    sf::Clock loadingClock;
    sf::Text t;
    t.setFont(Global::font);

    std::wstring wstr = ReadUtf8File(OBJECTS_PATH);
    std::vector<std::wstring> lines = WStringToVector(wstr);
    for (std::vector<std::wstring>::iterator it = lines.begin(); it != lines.end(); ++it)
        std::wcout << L'\t' << *it << std::endl;

    t.setString(sf::String(wstr));
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(t);
        window.display();
    }

    return 0;
}