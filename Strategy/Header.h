#pragma once
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <locale>
#include <iostream>

// ���������� ����������
HWND hwnd; // ���������� ����
sf::RenderWindow* renderWindow; // ��������� �� SFML ����
sf::Clock clock_; // ������ ��� ������������ ������� ����������
sf::Font font; // ����� ��� ������
sf::Text text;

sf::Text arrowKeyText;
sf::Text fKeyText;

// ������� ��� ������������� ��������� ��������
void initializeTextObjects() {
    // ������������� ������ ��� ������ �������
    arrowKeyText.setFont(font);
    arrowKeyText.setCharacterSize(24);
    arrowKeyText.setFillColor(sf::Color::White);
    arrowKeyText.setPosition(10, 50); // ������� ���� ���� ��������� ������

    // ������������� ������ ��� ������� '�'
    fKeyText.setFont(font);
    fKeyText.setCharacterSize(24);
    fKeyText.setFillColor(sf::Color::White);
    fKeyText.setPosition(10, 80); // ������� ��� ����
}

// ���������� ��������� ��� ����
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CLOSE:
        PostQuitMessage(0);
        break;
    case WM_DESTROY:
        return 0;
    case WM_PAINT:
        ValidateRect(hwnd, NULL); // ��������� ���������� ������� ����
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    setlocale(LC_ALL, "Russian");
    // �������� ������� ��� ������
    if (AllocConsole()) {
        FILE* stream;
        freopen_s(&stream, "CONOUT$", "w", stdout);
        freopen_s(&stream, "CONOUT$", "w", stderr);
        // ������ std::cout � std::cerr ����� ���������� � �������
    }
    SetConsoleCP(5001);

    std::wcout << L"�����!" << std::endl;
    if (!font.loadFromFile("resources/Fonts/consola.ttf"))
        throw std::runtime_error("font not found");
    text.setFont(font);
    text.setCharacterSize(24); // ��������� ������� ������
    text.setFillColor(sf::Color::White);
    initializeTextObjects();


    WNDCLASS wc = {};// ����������� ������ ����
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"SFML App";
    RegisterClass(&wc);

    // �������� ����
    hwnd = CreateWindowEx(
        0,
        L"SFML App",
        L"SFML Integration",
        WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX, // ���� ��� ����������� ��������� �������
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        NULL, NULL, hInstance, NULL
    );

    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // �������� SFML ����
    sf::RenderWindow window(sf::VideoMode(800, 600), "", sf::Style::None);

    renderWindow = &window;
    window.setPosition(sf::Vector2i(0, 0)); // ������� ���� SFML
    window.setFramerateLimit(30);
    // ��������� SFML ���� � HWND
    HWND sfmlHandle = window.getSystemHandle();
    SetParent(sfmlHandle, hwnd); // ������ SFML ���� �������� �� ��������� � HWND

    // ���� ���������
    MSG msg = {};
    while (msg.message != WM_QUIT) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {

            if (window.hasFocus())
            {
                UINT arrowKeysPressed = 0;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                    arrowKeysPressed = sf::Keyboard::Left;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                    arrowKeysPressed = sf::Keyboard::Right;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                    arrowKeysPressed = sf::Keyboard::Up;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                    arrowKeysPressed = sf::Keyboard::Down;

                arrowKeyText.setString(L"������� ������� �������: " + std::to_wstring(arrowKeysPressed));

                // ��������� ������� '�'
                std::wstring fKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::F) ? L"��" : L"���";
                fKeyText.setString(L"������� '�' ������: " + fKeyPressed);
            }

            sf::Time elapsed = clock_.getElapsedTime();
            text.setString(L"����� ����������: " + std::to_wstring(elapsed.asSeconds()) + L" ������");
            // ���������� � ��������� SFML
            window.clear(sf::Color::Blue);
            window.draw(text);
            window.draw(arrowKeyText);
            window.draw(fKeyText);
            // ����� ����� �������� ��������� � ������� SFML
            window.display();
        }
    }

    return 0;
}
