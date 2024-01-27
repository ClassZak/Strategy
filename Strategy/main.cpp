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


#include <locale>
#include <codecvt>
#include <fstream>
#include <string>

std::wstring read_utf8_file(const std::string& filename) {
    // ��������� ���� � �������� ������
    std::ifstream file(filename, std::ios::binary);
    // ������ ���������� ����� � ������
    std::string content(std::istreambuf_iterator<char>(file), {});
    // �������� ����� ������ � �������� Unicode
    int len = MultiByteToWideChar(CP_UTF8, 0, content.c_str(), content.size(), NULL, 0);
    // �������� ������ ��� ������ �������� Unicode
    wchar_t* buffer = new wchar_t[len];
    // ����������� ������ � UTF-8 � ������ Unicode
    MultiByteToWideChar(CP_UTF8, 0, content.c_str(), content.size(), buffer, len);
    // �������� ����� ������ � �������� ANSI
    int len2 = WideCharToMultiByte(CP_ACP, 0, buffer, len, NULL, 0, NULL, NULL);

    std::wstring result(buffer,len2);
    delete[] buffer;
    return result;
}


int main()
{
    setlocale(LC_ALL, "Russian");
    sf::RenderWindow window(sf::VideoMode(Global::WINDOW_WIDTH, Global::WINDOW_HEIGHT), L"���������", sf::Style::Default);

    sf::Clock loadingClock;
    sf::Text t;
    t.setFont(Global::font);
    std::wstring wstr = read_utf8_file(OBJECTS_PATH);
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