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

    if (!SUCCEEDED(Global::ContentLoading()))
    {
        system("pause");
        return EXIT_FAILURE;
    }

    sf::RenderWindow window
    (sf::VideoMode(Global::WINDOW_WIDTH, Global::WINDOW_HEIGHT), L"Стратегия", sf::Style::Titlebar | sf::Style::Close);
    
    
        

    sf::RenderTexture textureRender;
    if (!textureRender.create(Global::WINDOW_WIDTH, Global::WINDOW_HEIGHT))
    {
        system("pause");
        return -1;
    }

    sf::Sprite currSprite;
    textureRender.clear(sf::Color::White);
    UINT currWidth = 0, currHeight = 0, maxHeight = 0;
    for
    (
        std::map<std::wstring, std::vector<sf::Texture>>::const_iterator 
        it = Global::TexturesContext::GetTextures().begin();
        it != Global::TexturesContext::GetTextures().end();
        ++it
    )
        for (std::vector<sf::Texture>::const_iterator it_ = it->second.begin(); it_ != it->second.end(); ++it_)
        {
            currSprite.setTexture(*it_,true);
            currSprite.setPosition((float)currWidth, (float)currHeight);
            currWidth += currSprite.getTextureRect().width;
            if (maxHeight > (UINT)currSprite.getTextureRect().height)
                maxHeight = currSprite.getTextureRect().height;
            if (currWidth > Global::WINDOW_WIDTH)
            {
                currWidth = 0;
                currHeight += maxHeight;
                maxHeight = 0;
            }
            textureRender.draw(currSprite);
            textureRender.display();
        }
    sf::Texture renderedTexture = textureRender.getTexture();
    sf::Sprite renderedSprite;
    renderedSprite.setTexture(renderedTexture);

    const std::map<std::wstring, std::vector<sf::Texture>>* textures = &Global::TexturesContext::GetTextures();

    sf::Clock loadingClock;
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                {
                    std::wcout << L"Выход из игры" << std::endl;
                    window.close();
                }
                    
        }

        window.clear();
        window.draw(renderedSprite);
        window.display();
    }

    system("pause");
    return 0;
}