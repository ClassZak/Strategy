#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/System/String.hpp>
#include <Windows.h>
#include <exception>
#include <iostream>
#include <string>
#include <fstream>
#include <strstream>
#include <string>
#include <windows.h>
#include <vector>
#include <iterator>
#include <map>
#include <algorithm>
#include <list>
#include <locale.h>
#include <codecvt>


#define DEFAULT_SETTINGS_PATH "data/DefaultSettings.txt"
#define SETTINGS_PATH "data/Settings.txt"
#define OBJECTS_PATH "data/Objects.txt"
#define TEXTURES_PATH "data/Textures.txt"
#define SAVED_OBJECTS_PATH "data/SavedObjects.txt"
#define LOCALIZATION_PATH "data/Localization.txt"
#ifndef MAX_UNSIGNED_LONG_LONG
#define MAX_UNSIGNED_LONG_LONG 18446744073709551615
#endif
#ifndef MAX_UNSIGNED_INT
#define MAX_UNSIGNED_INT 4294967295
#endif

#ifndef FOREGROUND_DEFAULT
#define FOREGROUND_DEFAULT FOREGROUND_INTENSITY-1
#endif
#ifndef FOREGROUND_YELLOW
#define FOREGROUND_YELLOW 0xE
#endif


#include "ButtonWithImage.h"
#include "OverlayPanel.h"
#include "StandartSoldier.h"

#include "Functions.h"
#include "Object.h"
struct Global
{
	//Objects
	struct ObjectContext
	{
		enum ObjectType
		{
			UNKNOWN,
			BUTTON,
			BUTTONWITHIMAGE,
			OVERLAYPANEL,
			STANDARTSOLDIER,
			Count
		};

		static ObjectType FindTypeIndex(const std::wstring& str);
		static void LoadObjects(std::list<Object*>* objectList, const char* filename = OBJECTS_PATH);
		static void SaveObjects(std::list<Object*>* objectList, const char* filename = OBJECTS_PATH);
		static const std::wstring ObjectClasses[ObjectContext::ObjectType::Count];
	};
	//Settings
	struct SettinsContext
	{
		static void LoadGlobalVariables(const char* filename = DEFAULT_SETTINGS_PATH);
		static void SaveSettings(const char* filename = SETTINGS_PATH);
		static const std::map<std::wstring, double>& GetGlobalVariables();
	private:
		static std::map<std::wstring, double> Settings;
	};
	//Textures
	struct TexturesContext
	{
		static void LoadImages(const char* filename = TEXTURES_PATH);
		static void InitTextures();
		static std::map<std::wstring, std::vector<sf::Texture>>& GetTextures();
		static const std::map<std::wstring, std::vector<sf::Image>>& GetImages();
	private:
		static std::map<std::wstring, std::vector<sf::Texture>>textures;
		static std::map<std::wstring, std::vector<sf::Image>>images;
	};
	//Localization
	struct Localizator
	{
	public:
		static void LoadLocaledText(const char* filename = LOCALIZATION_PATH);
		static const std::map<std::wstring, std::vector<sf::String>>& GetLocalization();
		static std::map<std::wstring, std::vector<sf::String>> Localization;
	private:
		static std::vector<sf::String> STLStringsToSF(const std::vector<std::wstring>& lines);
		static std::vector<std::wstring> FindLocaledVectors_Names(std::vector<std::wstring>& lines);
	};


	//static ReleasedKeys keys;
	struct ReleasedKeys
	{
		static void ResetKeys()
		{
			for (int i = 0; i < Global::ReleasedKeys::KeyCount; ++i)
			{
				Global::ReleasedKeys::Released[i] = false;
				Global::ReleasedKeys::Pressed[i] = false;
			}
		}

		static void CheckKeys()
		{
			for (int i = 0; i < Global::ReleasedKeys::KeyCount; ++i)
				Global::ReleasedKeys::Released[i] = false;
			for (int i = 0; i < Global::ReleasedKeys::KeyCount; ++i)
				if (Global::ReleasedKeys::Pressed[i] and !sf::Keyboard::isKeyPressed((sf::Keyboard::Key)(i)))
					Global::ReleasedKeys::Released[i] = true;


			for (int i = 0; i < Global::ReleasedKeys::KeyCount; ++i)
				Global::ReleasedKeys::Pressed[i] = sf::Keyboard::isKeyPressed((sf::Keyboard::Key)(i));
		}
		static void SetPressed(const int key, const bool press)
		{
			if (key > -1 and key < Global::ReleasedKeys::KeyCount)
				Global::ReleasedKeys::Pressed[key] = press;
			else
				throw std::exception();
		}
		static void SetReleased(const int key, const bool releas)
		{
			if (key > -1 and key < Global::ReleasedKeys::KeyCount)
				Global::ReleasedKeys::Released[key] = releas;
			else
				throw std::exception();
		}

		static bool GetPressed(const int key)
		{
			if (key > -1 and key < Global::ReleasedKeys::KeyCount)
				return Global::ReleasedKeys::Pressed[key];
			else
				throw std::exception();
		}
		static bool GetReleased(const int key)
		{
			if (key > -1 and key < Global::ReleasedKeys::KeyCount)
				return Global::ReleasedKeys::Released[key];
			else
				throw std::exception();
		}


		enum Key
		{
			Unknown = -1, ///< Unhandled key
			A = 0,        ///< The A key
			B,            ///< The B key
			C,            ///< The C key
			D,            ///< The D key
			E,            ///< The E key
			F,            ///< The F key
			G,            ///< The G key
			H,            ///< The H key
			I,            ///< The I key
			J,            ///< The J key
			K,            ///< The K key
			L,            ///< The L key
			M,            ///< The M key
			N,            ///< The N key
			O,            ///< The O key
			P,            ///< The P key
			Q,            ///< The Q key
			R,            ///< The R key
			S,            ///< The S key
			T,            ///< The T key
			U,            ///< The U key
			V,            ///< The V key
			W,            ///< The W key
			X,            ///< The X key
			Y,            ///< The Y key
			Z,            ///< The Z key
			Num0,         ///< The 0 key
			Num1,         ///< The 1 key
			Num2,         ///< The 2 key
			Num3,         ///< The 3 key
			Num4,         ///< The 4 key
			Num5,         ///< The 5 key
			Num6,         ///< The 6 key
			Num7,         ///< The 7 key
			Num8,         ///< The 8 key
			Num9,         ///< The 9 key
			Escape,       ///< The Escape key
			LControl,     ///< The left Control key
			LShift,       ///< The left Shift key
			LAlt,         ///< The left Alt key
			LSystem,      ///< The left OS specific key: window (Windows and Linux), apple (MacOS X), ...
			RControl,     ///< The right Control key
			RShift,       ///< The right Shift key
			RAlt,         ///< The right Alt key
			RSystem,      ///< The right OS specific key: window (Windows and Linux), apple (MacOS X), ...
			Menu,         ///< The Menu key
			LBracket,     ///< The [ key
			RBracket,     ///< The ] key
			SemiColon,    ///< The ; key
			Comma,        ///< The , key
			Period,       ///< The . key
			Quote,        ///< The ' key
			Slash,        ///< The / key
			BackSlash,    ///< The \ key
			Tilde,        ///< The ~ key
			Equal,        ///< The = key
			Dash,         ///< The - key
			Space,        ///< The Space key
			Return,       ///< The Return key
			BackSpace,    ///< The Backspace key
			Tab,          ///< The Tabulation key
			PageUp,       ///< The Page up key
			PageDown,     ///< The Page down key
			End,          ///< The End key
			Home,         ///< The Home key
			Insert,       ///< The Insert key
			Delete,       ///< The Delete key
			Add,          ///< The + key
			Subtract,     ///< The - key
			Multiply,     ///< The * key
			Divide,       ///< The / key
			Left,         ///< Left arrow
			Right,        ///< Right arrow
			Up,           ///< Up arrow
			Down,         ///< Down arrow
			Numpad0,      ///< The numpad 0 key
			Numpad1,      ///< The numpad 1 key
			Numpad2,      ///< The numpad 2 key
			Numpad3,      ///< The numpad 3 key
			Numpad4,      ///< The numpad 4 key
			Numpad5,      ///< The numpad 5 key
			Numpad6,      ///< The numpad 6 key
			Numpad7,      ///< The numpad 7 key
			Numpad8,      ///< The numpad 8 key
			Numpad9,      ///< The numpad 9 key
			F1,           ///< The F1 key
			F2,           ///< The F2 key
			F3,           ///< The F3 key
			F4,           ///< The F4 key
			F5,           ///< The F5 key
			F6,           ///< The F6 key
			F7,           ///< The F7 key
			F8,           ///< The F8 key
			F9,           ///< The F9 key
			F10,          ///< The F10 key
			F11,          ///< The F11 key
			F12,          ///< The F12 key
			F13,          ///< The F13 key
			F14,          ///< The F14 key
			F15,          ///< The F15 key
			Pause,        ///< The Pause key

			KeyCount      ///< Keep last -- the total number of keyboard keys
		};
		static bool Released[ReleasedKeys::KeyCount];
		static bool Pressed[ReleasedKeys::KeyCount];
	};
	//Static released mouse buttons
	struct ReleasedMouseButtons
	{
		static bool lMousePressed;
		static bool rMousePressed;
		static bool lMouseReleased;
		static bool rMouseReleased;
		static void checkMouse()
		{
			lMouseReleased = false;
			rMouseReleased = false;

			rMouseReleased = !sf::Mouse::isButtonPressed(sf::Mouse::Right) and rMousePressed;
			lMouseReleased = !sf::Mouse::isButtonPressed(sf::Mouse::Left) and lMousePressed;

			rMousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Right);
			lMousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
		}
	};
	static INT ContentLoading();



	enum Room
	{
		NEW_GAME,
		CONTINUE,
		MENU,
		SETTINGS,
		GAME_FIELD,
		SAVING,
		LOADING
	};

	static UINT16 WINDOW_WIDTH;
	static UINT16 WINDOW_HEIGHT;
	static UINT16 MAX_FRAME;
	static const unsigned short MAIN_BUTTONS;

	static const unsigned short LEFT_EDGE_LENGTH;
	static const unsigned short DOWN_EDGE_LENGTH;


	static bool playing;
	static bool gameStarted;
	static bool focus;
	static bool focusLost;
	static bool fromMenu;
	static Room room;

	static sf::View view;
	static sf::View standartView;

	static const unsigned short maxScrolledTimes;
	static unsigned short scrolledUpTimes;
	static unsigned short scrolledDownTimes;

	static double zoom;
	static double viewDelta;

	static sf::Font font;
	static HANDLE consoleOutHandle;
};
