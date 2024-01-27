#ifndef SAVER_H
#define SAVER_H

#ifndef MAX_UNSIGNED_LONG_LONG
#define MAX_UNSIGNED_LONG_LONG 18446744073709551615
#endif
#ifndef MAX_UNSIGNED_INT
#define MAX_UNSIGNED_INT 4294967295
#endif


#define SavedSettings "data/SavedSettings.txt"
#define SavedObjects "data/SavedObjects.txt"


#include "ButtonWithImage.h"
#include "OverlayPanel.h"
#include "StandartSoldier.h"




#include <SFML/System/String.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <vector>
#include <iterator>
#include <map>
#include <algorithm>
#include <list>


#include "Global.h"
struct Saver
{
	template<typename T>
	static unsigned long long SaveObjects
	(std::list<T*,std::allocator<T*>>& objects,const char* filename=SavedObjects)
	{
		std::ofstream file(filename);
		if(!file.is_open())
		{
			throw std::runtime_error("Failed to save objects");
			return 0;
		}
		unsigned long long objectsCount=0;
		for(auto i=objects.begin();i!=objects.end();++i)
		{
			if(StandartSoldier* s=dynamic_cast<StandartSoldier*>(*i))
			{
				file<<"StandartSoldier\n";
				file<<s->x-Global::DOWN_EDGE_LENGTH;
				file<<'\t';
				file<<s->y;
				file<<'\t';
				file<<0;
				file<<'\t';
				file<<s->maxHp;
				file<<'\t';
				file<<s->hp;
				file<<'\n';
				++objectsCount;
			}
		}
		file.close();
		return objectsCount;
	}
	static std::size_t LoadVariablesCount(const char* filename=SavedSettings);
	static std::map<std::string, float> LoadGlobalVariables(const char* filename=SavedSettings);
};


#endif
