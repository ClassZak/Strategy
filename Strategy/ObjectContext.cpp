#pragma once
#include "Global.h"

const std::wstring Global::ObjectContext::ObjectClasses[Global::ObjectContext::Count] =
{
	L"Button",
	L"ButtonWithImage",
	L"OverlayPanel",
	L"StandartSoldier"
};


void Global::ObjectContext::LoadObjects(std::list<Object>& objectList, const char* filename)
{
	std::wfstream file(filename);
	if (!file.is_open())
		throw std::runtime_error("Failed to find file of objects");

	bool objectTypeFound = false;
	unsigned int objectsCount = 1;
	int objectType = -1;


	std::wstring curr;
	while(std::getline(file, curr))
	{
		if (STLStringIsEmpty(curr))
			continue;

		if (!objectTypeFound)
		{
			std::vector<std::wstring> words = FindWords(curr);
			if (words.size() == 0)
				continue;
			if (words.size() > 2)
			{
				std::cout << "Error during find correct type of object" << std::endl;
				return;
			}
			if (words.size() == 2)
				objectsCount = StringToLongLong(words[1], true);
			else
				objectsCount = 1;

			objectType = Global::ObjectContext::FindTypeIndex(words[0]);

			if (objectType == -1)
			{
				std::wcout << L"This types is not in correct list" << std::endl << L"curr=" << curr << std::endl;
				return;
			}
			objectTypeFound = true;
		}
		else
		{
			std::vector<std::wstring> params = FindWords(curr);
			std::vector<long long> numberParams = StringVectorToLongLong(params, true);
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
	file.close();

}
void Global::ObjectContext::SaveObjects(std::list<Object>& objectList, const char* filename)
{

}



unsigned int Global::ObjectContext::FindTypeIndex(const std::wstring& str)
{
	unsigned int index = 0;
	if (str[str.length() - 1] != L'\n')
	{
		while (str != Global::ObjectContext::ObjectClasses[index])
		{
			++index;
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
			++index;
			if (index > Global::ObjectContext::ObjectType::Count - 1)
				break;
		}
	}

	if (index == Global::ObjectContext::ObjectType::Count)
	{
		std::cout << "Types of Object not found" << std::endl;
		index = -1;
	}
	return index;
}