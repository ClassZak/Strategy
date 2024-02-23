#pragma once
#include "Global.h"

const std::wstring Global::ObjectContext::ObjectClasses[Global::ObjectContext::Count] =
{
	L"",
	L"Button",
	L"ButtonWithImage",
	L"OverlayPanel",
	L"StandartSoldier"
};


void Global::ObjectContext::LoadObjects(std::list<GameObject*>* objectList, const char* filename)
{
	SetConsoleTextAttribute(Global::consoleOutHandle, FOREGROUND_YELLOW);
	std::wcout << L"Object loading" << std::endl;
	SetConsoleTextAttribute(Global::consoleOutHandle, FOREGROUND_INTENSITY);
	std::cout << "Loading file:" << filename << std::endl;
	SetConsoleTextAttribute(Global::consoleOutHandle, FOREGROUND_GREEN);
	std::vector<std::wstring> lines;
	{
		std::wstring fullText = ReadUtf8File(filename);
		lines = WStringToVector(fullText);
	}
	

	bool objectTypeFound = false;
	unsigned int objectsCount = 1;
	Global::ObjectContext::ObjectType objectType = Global::ObjectContext::UNKNOWN;


	for(std::vector<std::wstring>::iterator it=lines.begin();it!=lines.end();++it)
	{
		if (STLStringIsEmpty(*it))
			continue;

		if (!objectTypeFound)
		{
			std::vector<std::wstring> words = FindWords(*it);
			if (words.size() == 0)
				continue;
			if (words.size() > 2)
			{
				throw std::runtime_error("Error during find correct type of object");
				return;
			}
			if (words.size() == 2)
				objectsCount = (unsigned)StringToLongLong(words[1], true);
			else
				objectsCount = 1;

			objectType = Global::ObjectContext::FindTypeIndex(words[0]);

			if (objectType == Global::ObjectContext::UNKNOWN)
			{
				SetConsoleTextAttribute(Global::consoleOutHandle, FOREGROUND_RED);
				std::wcout << L"This types is not in correct list" << std::endl << 
					L"curr=" << *it << std::endl;
				throw std::runtime_error("Failed to find correct type index");
				return;
			}
			objectTypeFound = true;
		}
		else
		{
			std::vector<std::wstring> params = FindWords(*it);
			std::vector<long long> numberParams = StringVectorToLongLong(params, true);
			switch (objectType)
			{
				case Global::ObjectContext::STANDARTSOLDIER:
				{
					sf::Texture* rTexture=
					&Global::TexturesContext::GetTextures()
						.find(L"StandartSoldier")->second.at((std::size_t)numberParams[2]);
					StandartSoldier* s = new StandartSoldier
					(
						(int)numberParams[0],
						(int)numberParams[1],
						rTexture->getSize().x,
						rTexture->getSize().y,
						rTexture
					);
					
					if (numberParams.size() == 4)
					{
						s->SetHp((unsigned)numberParams[3]);
					}
					if (numberParams.size() == 5)
					{
						s->SetMaxHp((unsigned)numberParams[3]);
						s->SetHp((unsigned)numberParams[4]);
					}

					objectList->push_back((GameObject*)s);
					std::wcout << L"New object of " << 
					Global::ObjectContext::ObjectClasses[Global::ObjectContext::STANDARTSOLDIER] << 
					std::endl;
					std::wcout << L"x:" << s->GetCoordinates().x << L"\ty:" << s->GetCoordinates().y <<
						L"\thp:" << s->GetHp() << L"\tmax hp:" << s->GetMaxHp() << std::endl;;

					break;
				}
				default:
					break;
			}
			/*switch (objectType)
			{
				case Loader::BUTTON:
				{
					Button* b = new Button();
					if (params.size() != 4)
					{
						std::cout << "Error during find correct params for object" << std::endl;
						delete b;
						return objects;
					}

					sf::Vector2f coordinates(StringToLongLong(params[0]), StringToLongLong(params[1]));
					b->SetCoordinates(coordinates);
					objects.push_back(b);
					break;
				}
				case Loader::STANDARTSOLDIER:
				{
					StandartSoldier* s = new StandartSoldier
					(
						numberParams[0] + Global::LEFT_EDGE_LENGTH,
						numberParams[1],
						Global::TexturesContext::GetTextures()["StandartSoldier"][numberParams[2]].getSize().x,
						Global::TexturesContext::GetTextures()["StandartSoldier"][numberParams[2]].getSize().y,
						&Global::TexturesContext::GetTextures()["StandartSoldier"][numberParams[2]]
					);
					if (numberParams.size() == 4)
					{
						s->hp = numberParams[3];
					}
					if (numberParams.size() == 5)
					{
						s->maxHp = numberParams[3];
						s->hp = numberParams[4];
					}

					objects.push_back(s);
					break;
				}
				default:
				{
					std::cout << "Unknown object type" << std::endl;
					return objects;
					break;
				}
			}*/

			--objectsCount;
			if (!objectsCount)
				objectTypeFound = false;
		}
	}
}
void Global::ObjectContext::SaveObjects(std::list<GameObject*>* objectList, const char* filename)
{
	SetConsoleTextAttribute(Global::consoleOutHandle, FOREGROUND_YELLOW);
	std::wcout << L"Saving objects" << std::endl;
	SetConsoleTextAttribute(Global::consoleOutHandle, FOREGROUND_INTENSITY);
	std::cout << "path:" << filename << std::endl;
	SetConsoleTextAttribute(Global::consoleOutHandle, FOREGROUND_DEFAULT);

	if (objectList->empty())
	{
		SetConsoleTextAttribute(Global::consoleOutHandle, FOREGROUND_YELLOW);
		std::cout << "Warning! List of objects is empty!" << std::endl;
		SetConsoleTextAttribute(Global::consoleOutHandle, FOREGROUND_DEFAULT);
		return;
	}

	std::wofstream file(filename);
	file << L"Амогус";
	if (file.bad())
		file.clear();
	SetConsoleTextAttribute(Global::consoleOutHandle, FOREGROUND_GREEN);

	for (std::list<GameObject*>::iterator it = objectList->begin(); it != objectList->end(); ++it)
	{
		if (StandartSoldier* s = dynamic_cast<StandartSoldier*>(*it))
		{
			//x, y, number of texture, max hp, hp
			UINT64 textureNumber = 0;
			for
			(
				auto it = (*Global::TexturesContext::GetTextures().find(L"StandartSoldier")).second.begin();
				it != (*Global::TexturesContext::GetTextures().find(L"StandartSoldier")).second.end(); 
				++it,++textureNumber
			)
			{
				if (s->GetTexture()==&(*it))
					break;
			}

			file << L"StandartSoldier" << std::endl << s->GetCoordinates().x << L'\t' << s->GetCoordinates().y << 
			L'\t' << textureNumber << L'\t' << s->GetHp() << '\t' << s->GetMaxHp()<< std::endl;
			std::wcout<< L"StandartSoldier" << std::endl << s->GetCoordinates().x << L'\t' << s->GetCoordinates().y <<
			L'\t' << textureNumber << L'\t' << s->GetHp() << '\t' << s->GetMaxHp() << std::endl;
		}
	}
	SetConsoleTextAttribute(Global::consoleOutHandle, FOREGROUND_DEFAULT);
}



Global::ObjectContext::ObjectType Global::ObjectContext::FindTypeIndex(const std::wstring& str)
{
	Global::ObjectContext::ObjectType index = Global::ObjectContext::ObjectType::UNKNOWN;
	if (str[str.length() - 1] != L'\n')
	{
		while (str != Global::ObjectContext::ObjectClasses[index])
		{
			index = (Global::ObjectContext::ObjectType)((int)(index + 1));
			if (index > Global::ObjectContext::ObjectType::Count - 1)
				break;
		}
	}
	else
	{
		std::wstring strbuff = str;
		strbuff.erase(strbuff.length() - 1);

		while (strbuff != Global::ObjectContext::ObjectClasses[index])
		{
			index=(Global::ObjectContext::ObjectType)((int)(index+1));
			if (index > Global::ObjectContext::ObjectType::Count - 1)
				break;
		}
	}

	if (index == Global::ObjectContext::ObjectType::Count)
	{
		std::cout << "Types of Object not found" << std::endl;
		index = Global::ObjectContext::UNKNOWN;
	}
	return index;
}
