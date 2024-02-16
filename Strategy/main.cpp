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
    try
    {
        setlocale(LC_ALL, "Russian");
        std::list<Object*>* objects = new std::list<Object*>;


        if (!SUCCEEDED(Global::ContentLoading()))
        {
            system("pause");
            return EXIT_FAILURE;
        }
    


        sf::RenderWindow window
        (
            sf::VideoMode(Global::WINDOW_WIDTH, Global::WINDOW_HEIGHT),
            L"Стратегия",
            sf::Style::Titlebar | sf::Style::Close
        );
        sf::Clock loadingClock;
    
        
        while (window.isOpen() and Global::playing)
        {
            switch (Global::room)
            {
                case Global::MENU:
                {
                    MainMenu(window);
                    break;
                }
                case Global::NEW_GAME:
                {
                    Global::ObjectContext::LoadObjects(objects);
                    Global::playing = false;
                    break;
                }
                default:
                    Global::playing = false;
                    break;
            }
        }
        return 0;
    }
    catch (const std::exception& ex)
    {
        SetConsoleTextAttribute(Global::consoleOutHandle, FOREGROUND_RED);
        std::cout << "Unhandled exception in main function!" << std::endl;
        std::cout << "Exception massege:" << std::endl;
        std::cerr << ex.what() << std::endl;
        SetConsoleTextAttribute(Global::consoleOutHandle, FOREGROUND_INTENSITY);
        std::cout << "Write console log in file data/Console log.txt" << std::endl;
        std::ofstream errLog("data/Console log.txt");




        CONSOLE_SCREEN_BUFFER_INFO csbi{};
        if (!GetConsoleScreenBufferInfo(Global::consoleOutHandle, &csbi))
        {
            std::cerr << "Error during loading console buffer info" << std::endl;
            SetConsoleTextAttribute(Global::consoleOutHandle, FOREGROUND_DEFAULT);
            system("pause");
            return 2;
        }
        short int width = csbi.dwSize.X;
        short int height = csbi.dwSize.Y;
        CHAR_INFO* buffer = new CHAR_INFO[width * height];

        // Копируем данные из буфера экрана консоли в буфер назначения
        COORD bufferSize = { width, height };
        COORD bufferCoord = { 0, 0 };
        SMALL_RECT readRegion{ 0,0,width,height };
        if (!ReadConsoleOutput(Global::consoleOutHandle, buffer, bufferSize, bufferCoord, &readRegion))
        {
            std::cerr << "Error during loading console buffer" << std::endl;
            SetConsoleTextAttribute(Global::consoleOutHandle, FOREGROUND_DEFAULT);
            delete[] buffer;
            system("pause");
            return 2;
        }

        // Выводим текст консоли на экран
        for (int i = 0; i < width * height; i++)
        {
            errLog << buffer[i].Char.AsciiChar;
            if (errLog.bad())
                errLog.clear();
            if ((i + 1) % width == 0)
                errLog << std::endl;
        }
        SetConsoleTextAttribute(Global::consoleOutHandle, FOREGROUND_DEFAULT);
        errLog.close();

        // Освобождаем память
        delete[] buffer;
        system("pause");
        return -1;
    }
}

