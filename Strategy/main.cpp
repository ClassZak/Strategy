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



LRESULT CALLBACK onEvent(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case WM_CLOSE:
        PostQuitMessage(0);
        break;
    case WM_DESTROY:
        return 0;
/*   case WM_SETCURSOR:
        SetCursor(HCURSOR(ICM_ON));
        break;*/
    case WM_PAINT:
        ValidateRect(handle, NULL); // Обновляем клиентскую область окна
        break;
    default:
        ValidateRect(handle, NULL);
        return DefWindowProc(handle, message, wParam, lParam);
    }
    return 0;
}


int main()
{
    try
    {
        setlocale(LC_ALL, "Russian");
        if (!SUCCEEDED(Global::ContentLoading()))
        {
            system("pause");
            return EXIT_FAILURE;
        }
        HINSTANCE instance = GetModuleHandle(NULL);

        // Define a class for our main window
        WNDCLASS windowClass;
        windowClass.style = 0;
        windowClass.lpfnWndProc = &onEvent;
        windowClass.cbClsExtra = 0;
        windowClass.cbWndExtra = 0;
        windowClass.hInstance = instance;
        windowClass.hIcon = NULL;
        windowClass.hCursor = 0;
        windowClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_BACKGROUND);
        windowClass.lpszMenuName = NULL;
        windowClass.lpszClassName = TEXT("SFML App");
        RegisterClass(&windowClass);

        // Let's create the main window
        HWND windowMain =
            CreateWindowExW
            (
                0L,
                TEXT("SFML App"),
                TEXT("Стратегия"),
                WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE,
            CW_USEDEFAULT, CW_USEDEFAULT, 
            Global::WINDOW_WIDTH, Global::WINDOW_HEIGHT, 
            NULL, NULL, instance, NULL
        );

        Global::windowClass = &windowClass;
        HWND view1 =
        CreateWindowExW
        (
            0L,
            TEXT("STATIC"),
            NULL,
            WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS,
            0, 0, 
            Global::WINDOW_WIDTH, Global::WINDOW_HEIGHT,
            windowMain, NULL, instance, NULL
        );
        Global::window = &windowMain;
        
        sf::RenderWindow window2(view1);
        window2.setFramerateLimit(Global::FPS);

        sf::Clock clock;
        MSG message;
        message.message = static_cast<UINT>(~WM_QUIT);
        sf::Text timeText;
        timeText.setFont(Global::font);
        
        timeText.setPosition(sf::Vector2f((300 - 20) / 2, (400 - 20) / 2));
        
        sf::Text aPressed;
        aPressed.setFont(Global::font);
        aPressed.setPosition(sf::Vector2f(Global::WINDOW_WIDTH/2, Global::WINDOW_HEIGHT/2));
        aPressed.setString(sf::String(L"sss"));
        
        while (message.message != WM_QUIT)
        {
            if (PeekMessageW(&message, NULL, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&message);
                DispatchMessage(&message);
            }
            else
            {
                
                aPressed.setString(sf::String(std::to_wstring((INT)sf::Keyboard::isKeyPressed(sf::Keyboard::A))));
                aPressed.setOrigin(aPressed.getGlobalBounds().width / 2, aPressed.getGlobalBounds().height / 2);
                    
                    

                timeText.setString
                (sf::String(std::wstring(L"Time:") + std::to_wstring((UINT)clock.getElapsedTime().asSeconds())));
                timeText.setOrigin(timeText.getGlobalBounds().width / 2, timeText.getGlobalBounds().height / 2);



                window2.clear();
                window2.draw(timeText);
                window2.draw(aPressed);
                window2.display();
            }
        }

        /*


        std::list<GameObject*>* objects = new std::list<GameObject*>;


        sf::RenderWindow window
        (
            sf::VideoMode(Global::WINDOW_WIDTH, Global::WINDOW_HEIGHT),
            L"Стратегия",
            sf::Style::Titlebar | sf::Style::Close
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
        secondWindowRendering.join();
        return 0;*/
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

