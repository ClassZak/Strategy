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

    Global::Localizator::LoadLocaledText();

    sf::Clock loadingClock;
    sf::Text t;
    t.setFont(Global::font);

    std::wstring wstr;
    for
    (
        std::map<std::wstring, std::vector<sf::String>>::iterator it = Global::Localizator::Localization.begin();
        it != Global::Localizator::Localization.end();
        ++it
    )
    {
        wstr += it->first + L'\n';
        for (std::vector<sf::String>::iterator it_ = it->second.begin(); it_ != it->second.end(); ++it_)
            wstr += L'\t'+it_->toWideString() + L'\n';
            
    }

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