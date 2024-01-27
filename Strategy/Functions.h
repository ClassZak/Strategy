#pragma once
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <SFML/System/String.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <stdlib.h>
#ifndef MAX_UNSIGNED_INT
#define MAX_UNSIGNED_INT 4294967295
#endif

#include <iostream>
////////////////////

long long StringToLongLong(const std::string& str, const bool continuously = false);
long long StringToLongLong(const std::wstring& str, const bool continuously = false);
unsigned long long PowerTen(const unsigned short n = 1);
std::vector<long long>StringVectorToLongLong
(const std::vector<std::string>& strings, const bool constinuosly = false);
std::vector<long long>StringVectorToLongLong
(const std::vector<std::wstring>& strings, const bool constinuosly = false);
std::wstring getStringExceptSymbols(std::wstring wString, wchar_t ch);
std::size_t getLastLinePos(const std::wstring& wString);

bool STLStringIsEmpty(const std::string& string);
bool STLStringIsEmpty(const std::wstring& string);
std::vector<std::string> FindWords(const std::string& currInputString);
std::vector<std::wstring> FindWords(const std::wstring& currInputString);
std::vector<std::string> LoadSTLStringsInVector(const char* filename);
std::vector<std::wstring> LoadWideSTLStringsInVector(const char* filename);


sf::Texture* GetFullBackground
(const sf::Texture& base, sf::Sprite& backgroundSprite, const unsigned HOR_REPEATS, const unsigned VERT_REPEATS);

