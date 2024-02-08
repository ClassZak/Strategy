#ifndef FUNCTIONS_CPP
#define FUNCTIONS_CPP
#include "Functions.h"


std::wstring ReadUtf8File(const char* filename)
{
	// Открываем файл в бинарном режиме
	std::ifstream file(filename, std::ios::binary);
	if (!file.is_open())
		throw std::runtime_error("Failed to find file");
	// Читаем содержимое файла в строку
	std::string content(std::istreambuf_iterator<char>(file), {});
	// Получаем длину строки в символах Unicode
	int len = MultiByteToWideChar(CP_UTF8, 0, content.c_str(), (int)content.size(), NULL, 0);
	// Выделяем память под массив символов Unicode
	wchar_t* buffer = new wchar_t[len];
	// Преобразуем строку в UTF-8 в строку Unicode
	MultiByteToWideChar(CP_UTF8, 0, content.c_str(), (int)content.size(), buffer, len);
	// Получаем длину строки в символах(обрезаем строку)
	int len2 = WideCharToMultiByte(CP_ACP, 0, buffer, len, NULL, 0, NULL, NULL);

	std::wstring result(buffer, len2);
	delete[] buffer;
	return result;
}
std::wstring ClearFromRSymbols(std::wstring& string)
{
	std::wstring resStr;
	std::wstring currStr;
	std::size_t currentPos = 0, nextPos=0;
	while (nextPos != std::wstring::npos)
	{
		nextPos = string.find(L'\r', currentPos+1);
		currStr = string.substr(currentPos, nextPos-currentPos);
		resStr += currStr;
		currentPos = string.find(L'\r', nextPos)+1;
	}
	return resStr;
}
std::vector<std::wstring> WStringToVector(std::wstring& fullText)
{
	std::wstring cleanString = ClearFromRSymbols(fullText), currStr;
	std::vector<std::wstring> result;
	std::size_t currentPos = 0;
	while (currentPos != std::wstring::npos)
	{
		currStr = cleanString.substr(currentPos, cleanString.find(L'\n', currentPos) - currentPos);
		result.push_back(currStr);
		currentPos = cleanString.find(L'\n', currentPos+1);
		if (currentPos++ == std::wstring::npos)
			break;
	}
	return result;
}



long long StringToLongLong(const std::string& str, const bool continuously)
{
	bool negative = false;
	long long number = 0;
	for (std::size_t i = 0; i < str.size(); ++i)
	{
		if (str[i] >= '0' and str[i] <= '9')
		{
			number *= 10;
			number += int(str[i] - '0');
		}
		else
		{
			if (!negative and str[i] == '-')
				negative = true;
			else
				if (continuously)
					break;
		}
	}

	if (negative)
		number *= -1;

	return number;
}
long long StringToLongLong(const std::wstring& str, const bool continuously)
{
	bool negative = false;
	long long number = 0;
	for (std::size_t i = 0; i < str.size(); ++i)
	{
		if (str[i] >= '0' and str[i] <= '9')
		{
			number *= 10;
			number += int(str[i] - '0');
		}
		else
		{
			if (!negative and str[i] == '-')
				negative = true;
			else
				if (continuously)
					break;
		}
	}

	if (negative)
		number *= -1;

	return number;
}
unsigned long long PowerTen(const unsigned short n)
{
	if (n == 0)
		return 1;
	if (n == 1)
		return 10;
	else
		return PowerTen(n - 1) * 10;
}
std::vector<long long>StringVectorToLongLong
(const std::vector<std::string>& strings, const bool constinuosly)
{
	long long currNumber;
	std::vector<long long>numbers;
	numbers.reserve(strings.size());
	for (std::vector<std::string>::const_iterator i = strings.begin(); i != strings.end(); ++i)
	{
		currNumber = StringToLongLong(*i, constinuosly);
		numbers.push_back(currNumber);
	}
	return numbers;
}
std::vector<long long>StringVectorToLongLong
(const std::vector<std::wstring>& strings, const bool constinuosly)
{
	long long currNumber;
	std::vector<long long>numbers;
	numbers.reserve(strings.size());
	for (std::vector<std::wstring>::const_iterator i = strings.begin(); i != strings.end(); ++i)
	{
		currNumber = StringToLongLong(*i, constinuosly);
		numbers.push_back(currNumber);
	}
	return numbers;
}
std::wstring getStringExceptSymbols(std::wstring wString, wchar_t ch)
{
	std::size_t charId = 0, nextCharId;
	std::wstring result;

	while (charId < wString.length())
	{
		nextCharId = wString.find(ch, charId);
		if (nextCharId == std::wstring::npos)
		{
			result += wString.substr(charId);
			break;
		}
		else
		{
			result += wString.substr(charId, nextCharId - charId);
			charId = nextCharId;
			++charId;
		}
	}
	return result;
}
std::size_t getLastLinePos(const std::wstring& wString)
{
	std::size_t charId = 0, nextCharId = wString.find(L'\n', charId);

	while (nextCharId != std::wstring::npos)
	{
		charId = nextCharId;
		++charId;
		nextCharId = wString.find(L'\n', charId);
	}
	return charId;
}


bool STLStringIsEmpty(const std::wstring& string)
{
	if (string.empty())
		return true;

	bool isempty = true;

	for (unsigned long long i = 0; i < string.length(); ++i)
		if (!((string[i] == L' ') or (string[i] == L'\t') or (string[i] == L'\n') or (string[i]==L'\r')))
		{
			isempty = false;
			break;
		}
	return isempty;
}
std::vector<std::wstring> FindWords(const std::wstring& currInputString)
{
	std::vector <std::wstring> inputWords;
	std::wstring currWord;

	if (STLStringIsEmpty(currInputString))
		return inputWords;

	std::size_t fPos = 0, sPos;

	std::size_t spacepos = currInputString.find(' ', 0);
	std::size_t tabpos = currInputString.find('\t', 0);

	if (spacepos == MAX_UNSIGNED_INT)
		sPos = tabpos;
	else
		sPos = spacepos;

	while ((sPos != std::string::npos) and (sPos != -1))
	{
		currWord = currInputString.substr(fPos, sPos - fPos);
		inputWords.push_back(currWord);
		fPos = sPos + 1;

		while
			(
				((currInputString[fPos] == ' ') or (currInputString[fPos] == '\t')) and
				((fPos) < currInputString.size() - 1)
				)
			fPos++;
		if (fPos >= currInputString.size() - 1)
			break;


		spacepos = currInputString.find(' ', fPos);
		tabpos = currInputString.find('\t', fPos);


		if (spacepos == MAX_UNSIGNED_INT)
			sPos = tabpos;
		else
			sPos = spacepos;
	}

	sPos = currInputString.size() - 1;
	if (fPos <= currInputString.size() - 1)
	{
		currWord = currInputString.substr(fPos, sPos - fPos + 1);
		inputWords.push_back(currWord);
	}

	return inputWords;
}

sf::Texture* GetFullBackground
(const sf::Texture& base, sf::Sprite& backgroundSprite, const unsigned HOR_REPEATS, const unsigned VERT_REPEATS)
{
	sf::Sprite title(base);
	sf::RenderTexture renderTexture;
	if
		(
			!renderTexture.create
			(HOR_REPEATS * title.getTextureRect().width, VERT_REPEATS * title.getTextureRect().height)
			)
		throw std::runtime_error("failed to create background texture render");

	renderTexture.clear(sf::Color::White);
	for (unsigned y = 0; y < VERT_REPEATS; ++y)
	{
		for (unsigned x = 0; x < HOR_REPEATS; ++x)
		{
			title.setPosition(float(x * title.getTextureRect().width), float(y * title.getTextureRect().height));
			renderTexture.draw(title);
			renderTexture.display();
		}
	}
	sf::Texture* resultTexture = new sf::Texture;
	*resultTexture = renderTexture.getTexture();
	backgroundSprite.setTexture(*resultTexture, true);
	return resultTexture;
}


std::vector<std::string> LoadSTLStringsInVector(const char* filename)
{
	std::vector<std::string> lines;
	std::ifstream file(filename);
	if (!file.is_open())
		std::cout << "Failed to open file" << std::endl;
	else
	{
		std::string currline;
		while (!file.eof())
		{
			std::getline(file, currline);
			lines.push_back(currline);
		}
	}
	file.close();
	return lines;
}
#endif
