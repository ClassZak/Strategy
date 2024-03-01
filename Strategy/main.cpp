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
        std::list<GameObject*>* objects = new std::list<GameObject*>;
        


        if (!SUCCEEDED(Global::ContentLoading()))
        {
            system("pause");
            return EXIT_FAILURE;
        }

    


        sf::RenderWindow window
        (
            sf::VideoMode(Global::WINDOW_WIDTH, Global::WINDOW_HEIGHT),
            L"���������",
            sf::Style::Titlebar | sf::Style::Close
        );
        Global::DPI = GetDpiForWindow(window.getSystemHandle());
        Global::PSizes =
        sf::Vector2f
        (
            ((Global::DPI * Global::PixelSizes.x) / 96.) / 96.,
            ((Global::DPI * Global::PixelSizes.y) / 96.) / 96.
        );





        window.setFramerateLimit(Global::FPS);
        sf::Clock loadingClock;
    
        
        while (window.isOpen() and Global::playing)
        {
            switch (Global::room)
            {
                case Global::MENU:
                {
                    MainMenu(window);
                    Global::fromMenu = true;
                    break;
                }
                case Global::SETTINGS:
                {
                    SettingsMenu(window);
                    break;
                }
                case Global::SAVING:
                {
                    Global::ObjectContext::SaveObjects(objects, SAVED_OBJECTS_PATH);
                    Global::room = Global::MENU;
                    break;
                }
                case Global::NEW_GAME:
                {
                    objects->clear();
                    Global::ObjectContext::LoadObjects(objects, OBJECTS_PATH);
                    Global::scrolledDownTimes = 0;
                    Global::scrolledUpTimes = 0;
                    Global::view = Global::standartView;
                    Global::view.move(sf::Vector2f(-Global::LEFT_EDGE_LENGTH, 0));
                    GameField(window, objects);
                    Global::fromMenu = false;
                    Global::gameStarted = true;
                    break;
                }
                case Global::CONTINUE:
                {
                    if (Global::gameStarted)
                    {
                        GameField(window, objects);
                        Global::fromMenu = false;
                    }
                    else
                        Global::room = Global::MENU;
                    break;
                }
                case Global::LOADING :
                {
                    objects->clear();
                    Global::ObjectContext::LoadObjects(objects, SAVED_OBJECTS_PATH);
                    Global::scrolledDownTimes = 0;
                    Global::scrolledUpTimes = 0;
                    Global::view = Global::standartView;
                    Global::view.move(sf::Vector2f(-Global::LEFT_EDGE_LENGTH, 0));
                    GameField(window, objects);
                    Global::fromMenu = false;
                    break;
                }
                default:
                    Global::playing = false;
                    break;
            }
        }
        delete objects;
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

        // �������� ������ �� ������ ������ ������� � ����� ����������
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

        // ������� ����� ������� �� �����
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

        // ����������� ������
        delete[] buffer;
        system("pause");
        return -1;
    }
}

