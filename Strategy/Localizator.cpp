#pragma once
#include "Global.h"

std::map<std::wstring, std::vector<sf::String>>
Global::Localizator::Localization = std::map<std::wstring, std::vector<sf::String>>();

const std::map<std::wstring, std::vector<sf::String>>& Global::Localizator::GetLocalization()
{
	return Global::Localizator::Localization;
}
void Global::Localizator::LoadLocaledText(const char* filename)
{
	std::wcout << "Load localization:" << std::endl;

	std::map<std::wstring, std::vector<std::wstring>>LocaledText;
	std::vector<std::wstring> lines;
	{
		std::wstring fullText = ReadUtf8File(filename);
		lines = WStringToVector(fullText);
	}
	std::vector<std::wstring> LocaledVectors_Names =
		Global::Localizator::FindLocaledVectors_Names(lines);

	std::vector<std::wstring> LocaledStrings;

	bool LeftParenthesisFound = false;
	std::size_t currname = 0;

	for (std::vector<std::wstring>::iterator it = lines.begin(); it != lines.end(); ++it)
	{
		if (STLStringIsEmpty(*it))
			continue;

		if (!LeftParenthesisFound)
		{
			std::vector<std::wstring> words = FindWords(*it);
			if (words.size() == 1)
			{
				if ((words[0][words[0].length() - 1] == '='))
				{
					if
						(std::find
						(
							LocaledVectors_Names.begin(),
							LocaledVectors_Names.end(),
							[&words]() -> std::wstring
							{
								std::wstring substring = words[0].substr(0, words[0].length() - 1);
								return substring;
							}()
								)
							!= LocaledVectors_Names.end()
								)
					{
						std::vector<std::wstring>::iterator it_ = it;
						++it_;


						while (!LeftParenthesisFound)
						{
							if (it_ == lines.end())
							{
								std::cout << "Error during reading localisation" << std::endl;
								throw std::exception();
							}

							std::vector<std::wstring> CurrWords = FindWords(*it_);
							if ((CurrWords[0] == L"{") and (CurrWords.size() == 1))
							{
								LeftParenthesisFound = true;
								break;
							}


							++it_;
						}
						it = it_;
					}
				}
			}
			else
				if (words.size() == 2)
				{
					if (words[1] == L"=")
						if
							(std::find
							(
								LocaledVectors_Names.begin(),
								LocaledVectors_Names.end(),
								words[0]
							)
								!= LocaledVectors_Names.end()
								)
						{
							std::vector<std::wstring>::iterator it_ = it;
							++it_;


							while (!LeftParenthesisFound)
							{
								if (it_ == lines.end())
								{
									std::cout << "Error during reading localisation" << std::endl;
									throw std::exception();
								}

								std::vector<std::wstring> CurrWords = FindWords(*it_);
								if ((CurrWords[0] == L"{") and (CurrWords.size() == 1))
								{
									LeftParenthesisFound = true;
									break;
								}

								++it_;
							}
							it = it_;
						}
				}
		}
		else
		{
			std::vector<std::wstring> CurrWords = FindWords(*it);
			if ((CurrWords[0] == L"}") and (CurrWords.size() == 1))
			{
				LeftParenthesisFound = false;
				LocaledText[LocaledVectors_Names[currname]] = LocaledStrings;
				LocaledStrings.clear();
				++currname;
				continue;
			}
			else
				LocaledStrings.push_back(*it);
		}
	}

	for (std::map<std::wstring, std::vector<std::wstring>>::iterator i = LocaledText.begin(); i != LocaledText.end(); ++i)
	{
		std::wcout << i->first << ':' << std::endl;
		for (std::vector<std::wstring>::iterator j = i->second.begin(); j != i->second.end(); ++j)
		{
			std::wcout << "\t" << *j << std::endl;
		}
	}
	//////////////////////////////////////////////
	std::map<std::wstring, std::vector<sf::String>> FinalLocaledText;
	for (std::map<std::wstring,std::vector<std::wstring>>::iterator it = LocaledText.begin(); it != LocaledText.end(); ++it)
	{
		FinalLocaledText[it->first] = Global::Localizator::STLStringsToSF(it->second);
	}
	Global::Localizator::Localization = FinalLocaledText;
}

std::vector<sf::String> Global::Localizator::STLStringsToSF(const std::vector<std::wstring>& lines)
{
	std::vector<sf::String> sflines;
	sf::String currline;
	for (std::vector<std::wstring>::const_iterator i = lines.begin(); i != lines.end(); ++i)
	{
		currline = *i;
		sflines.push_back(currline);
	}
	return sflines;
}


std::vector<std::wstring> Global::Localizator::FindLocaledVectors_Names(std::vector<std::wstring>& lines)
{
	std::vector<std::wstring> words;
	std::vector<std::wstring> LocaledVectors_Names;
	for
		(
			std::vector<std::wstring>::iterator it = lines.begin();
			it != lines.end();
			++it
			)
	{
		if (STLStringIsEmpty(*it))
			continue;
		words = FindWords(*it);
		//Vector name adds if it have the '='
		if (words.size() == 1)
		{
			if ((words[0][words[0].length() - 1] == '='))
			{
				std::wstring substring = words[0].substr(0, words[0].length() - 1);
				LocaledVectors_Names.push_back(substring);
			}
		}
		else
			if (words.size() == 2)
			{
				if (words[1] == L"=")
					LocaledVectors_Names.push_back(words[0]);
			}
	}
	return LocaledVectors_Names;
}

