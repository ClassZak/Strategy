#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <locale>
#include <iostream>

// Глобальные переменные
HWND hwnd; // Дескриптор окна
sf::RenderWindow* renderWindow; // Указатель на SFML окно
sf::Clock clock_; // Таймер для отслеживания времени выполнения
sf::Font font; // Шрифт для текста
sf::Text text;

sf::Text arrowKeyText;
sf::Text fKeyText;

// Функция для инициализации текстовых объектов
void initializeTextObjects() {
    // Инициализация текста для клавиш стрелок
    arrowKeyText.setFont(font);
    arrowKeyText.setCharacterSize(24);
    arrowKeyText.setFillColor(sf::Color::White);
    arrowKeyText.setPosition(10, 50); // Позиция чуть ниже основного текста

    // Инициализация текста для клавиши 'Ф'
    fKeyText.setFont(font);
    fKeyText.setCharacterSize(24);
    fKeyText.setFillColor(sf::Color::White);
    fKeyText.setPosition(10, 80); // Позиция еще ниже
}

// Обработчик сообщений для окна
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CLOSE:
        PostQuitMessage(0);
        break;
    case WM_DESTROY:
        return 0;
    case WM_PAINT:
        ValidateRect(hwnd, NULL); // Обновляем клиентскую область окна
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    
    setlocale(LC_ALL, "Russian");
    // Создание консоли для вывода
    if (AllocConsole()) {
        FILE* stream;
        freopen_s(&stream, "CONOUT$", "w", stdout);
        freopen_s(&stream, "CONOUT$", "w", stderr);
        // Теперь std::cout и std::cerr будут выводиться в консоль
    }
    SetConsoleCP(5001);

    std::wcout << L"Засос!" << std::endl;
    if (!font.loadFromFile("resources/Fonts/consola.ttf"))
        throw std::runtime_error("font not found");
    text.setFont(font);
    text.setCharacterSize(24); // Установка размера шрифта
    text.setFillColor(sf::Color::White);
    initializeTextObjects();


    WNDCLASS wc = {};// Регистрация класса окна
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"SFML App";
    RegisterClass(&wc);

    // Создание окна
    hwnd = CreateWindowEx(
        0,
        L"SFML App",
        L"SFML Integration",
        WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX, // Окно без возможности изменения размера
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        NULL, NULL, hInstance, NULL
    );

    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Создание SFML окна
    sf::RenderWindow window(sf::VideoMode(800, 600), "", sf::Style::None);

    renderWindow = &window;
    window.setPosition(sf::Vector2i(0, 0)); // Позиция окна SFML
    window.setFramerateLimit(30);
    // Связываем SFML окно с HWND
    HWND sfmlHandle = window.getSystemHandle();
    SetParent(sfmlHandle, hwnd); // Делаем SFML окно дочерним по отношению к HWND

    // Цикл сообщений
    MSG msg = {};
    while (msg.message != WM_QUIT) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {

            if (window.hasFocus())
            {
                UINT arrowKeysPressed=0;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                    arrowKeysPressed = sf::Keyboard::Left;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                    arrowKeysPressed = sf::Keyboard::Right;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                    arrowKeysPressed = sf::Keyboard::Up;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                    arrowKeysPressed = sf::Keyboard::Down;
                
                arrowKeyText.setString(L"Нажатые клавиши стрелок: " + std::to_wstring(arrowKeysPressed));

                // Обработка клавиши 'Ф'
                std::wstring fKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::F) ? L"Да" : L"Нет";
                fKeyText.setString(L"Клавиша 'Ф' нажата: " + fKeyPressed);
            }

            sf::Time elapsed = clock_.getElapsedTime();
            text.setString(L"Время выполнения: " + std::to_wstring(elapsed.asSeconds()) + L" секунд");
            // Обновление и рендеринг SFML
            window.clear(sf::Color::Blue);
            window.draw(text);
            window.draw(arrowKeyText);
            window.draw(fKeyText);
            // Здесь можно добавить рисование с помощью SFML
            window.display();
        }
    }

    return 0;
}
