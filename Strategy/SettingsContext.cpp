#pragma once
#include "Global.h"
std::map<std::wstring, double> Global::SettinsContext::Settings = std::map<std::wstring, double>();
void Global::SettinsContext::LoadGlobalVariables(const char* filename)
{
	SetConsoleTextAttribute(Global::consoleOutHandle, FOREGROUND_YELLOW);
	std::wcout << L"Loading settings" << std::endl;

	try
	{
		Global::SettinsContext::Settings.clear();
		std::vector<std::wstring> lines;
		{
			std::wstring fullText = ReadUtf8File(filename);
			lines = WStringToVector(fullText);
		}
		
	
		std::vector<std::wstring>::iterator it = lines.begin();

		std::size_t i = 0;
		std::size_t SeparationPos = 0, preSeparationPos = 0;

		bool negative = false;
		bool ReadFloatingPart = false;
		unsigned short FloaingPartsRead = 0;
		double currnumber = 0;
		std::wstring currName;

		bool WasWarning = false;

		std::size_t spacepos = it->find(L' '), equalspos = it->find(L'='), tabpos = it->find(L'\t');

		for (; it != lines.end(); ++it)
		{
			if (STLStringIsEmpty(*it))
				continue;


			spacepos = it->find(L' '); equalspos = it->find(L'='); tabpos = it->find(L'\t');

			SeparationPos = equalspos;
			if (SeparationPos == std::wstring::npos)
				SeparationPos = tabpos;
			if (SeparationPos == std::wstring::npos)
				SeparationPos = spacepos;

			if (SeparationPos == std::wstring::npos)
			{
				throw std::runtime_error("Error at the time loading data");
				break;
			}


			preSeparationPos =
				((spacepos <= equalspos) ?
					((spacepos <= tabpos) ? spacepos : tabpos) :
					((equalspos <= tabpos) ? equalspos : tabpos));
			currName = it->substr(0,preSeparationPos);
		


			for (std::size_t j = SeparationPos + 1; j < it->length(); ++j)
			{
				if (currnumber == 0 and (((*it)[j] == L' ') or (((*it)[j] == L'\t'))))
					continue;
				else if (((*it)[j] == L' ') or (((*it)[j] == L'\t')))
				{
					SetConsoleTextAttribute(Global::consoleOutHandle, FOREGROUND_YELLOW);
					std::wcout << L"Warning! Uncorrect separation of spaces or separation of tab characters" << std::endl;
					SetConsoleTextAttribute(Global::consoleOutHandle, FOREGROUND_DEFAULT);
					break;
				}

				if ((*it)[j] == L'-')
				{
					if (currnumber == 0 and !negative)
					{
						negative = true;
						continue;
					}
					else
						break;
				}

				if ((*it)[j] >= L'0' and (*it)[j] <= L'9')
				{
					if (!ReadFloatingPart)
					{
						currnumber *= 10;
						currnumber += short((*it)[j]) - short(L'0');
					}
					else
					{
						++FloaingPartsRead;
						currnumber += double(short((*it)[j]) - short(L'0')) / double(PowerTen(FloaingPartsRead));
					}
				}
				else if (!(((*it)[j] == L'.') or ((*it)[j] == L',')))
					break;
				else if (!ReadFloatingPart)
					ReadFloatingPart = true;
				else
					break;

				if (((*it)[j] == L',') and !WasWarning)
				{
					SetConsoleTextAttribute(Global::consoleOutHandle, FOREGROUND_YELLOW);
					std::wcout << L"Warning! ',' is uncorrect character to separate integer and float parts of number!" << std::endl;
					SetConsoleTextAttribute(Global::consoleOutHandle, FOREGROUND_DEFAULT);
					WasWarning = true;
				}
			}
			++i;

			if (negative)
			{
				currnumber *= -1;
				negative = false;
			}
			ReadFloatingPart = false;
			FloaingPartsRead = 0;


			SetConsoleTextAttribute(Global::consoleOutHandle, FOREGROUND_GREEN);
			std::wcout << currName << L'\t';
			SetConsoleTextAttribute(Global::consoleOutHandle, FOREGROUND_INTENSITY);
			std::wcout << currnumber << std::endl;
			SetConsoleTextAttribute(Global::consoleOutHandle, FOREGROUND_DEFAULT);


			Global::SettinsContext::Settings[currName] = currnumber;
			currnumber = 0;
		}
	}
	catch (const std::exception& ex)
	{
		SetConsoleTextAttribute(Global::consoleOutHandle, FOREGROUND_RED);
		std::cerr << ex.what() << std::endl;
		SetConsoleTextAttribute(Global::consoleOutHandle, FOREGROUND_DEFAULT);
		throw;
	}
}
void Global::SettinsContext::SaveSettings(const char* filename)
{
	SetConsoleTextAttribute(Global::consoleOutHandle, FOREGROUND_YELLOW);
	std::wcout << L"Saving settings" << std::endl;
	SetConsoleTextAttribute(Global::consoleOutHandle, FOREGROUND_DEFAULT);

	std::wofstream file(filename);
	if (!file.is_open())
		throw std::runtime_error(std::string("Failed to find file") + std::string(filename));
	for
	(
		auto it = Global::SettinsContext::GetGlobalVariables().begin();
		it != Global::SettinsContext::GetGlobalVariables().end();
		++it
	)
	file << it->first << L"\t=\t" << it->second << std::endl;
}

const std::map<std::wstring, double>& Global::SettinsContext::GetGlobalVariables()
{
	return Global::SettinsContext::Settings;
}

