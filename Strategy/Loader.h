#ifndef LOADER_H
#define LOADER_H

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
#include <locale>


#define SettingsDirection "data/InterfaceSettings.txt"
#define Objects "data/Objects.txt"
#define Textures "data/Textures.txt"
#ifndef MAX_UNSIGNED_LONG_LONG
#define MAX_UNSIGNED_LONG_LONG 18446744073709551615
#endif
#ifndef MAX_UNSIGNED_INT
#define MAX_UNSIGNED_INT 4294967295
#endif


#include "ButtonWithImage.h"
#include "OverlayPanel.h"
#include "StandartSoldier.h"

#include "Global.h"
#include "Functions.h"

unsigned long long PowerTen(const unsigned short n=1);
struct Loader
{
	enum ObjectType
	{
		BUTTON,
		BUTTONWITHIMAGE,
		OVERLAYPANEL,
		STANDARTSOLDIER,
		Count
	};
	
	static std::vector<std::string> LoadSTLStringsInVector(const char* filename=SettingsDirection);
	static std::size_t LoadVariablesCount();
	static std::vector<std::string> LoadGlobalVariablesNames(const char* filename=SettingsDirection);
	static std::vector<std::string> LoadGlobalVariablesNames(const std::vector<std::string>& lines);
	static std::vector<float> LoadGlobalValuesFromFile(const char* filename=SettingsDirection);
	static std::vector<float> FindGlobalVariables_Values(const std::vector<std::string>& lines);
	static std::vector<std::string>::iterator FindLocalisationPointer(std::vector<std::string>& text);
	static std::map<std::string, float> LoadGlobalVariables();
	
	
	static unsigned int FindTypeIndex(const std::string& str);
	static std::list<Object*> LoadObjects(const char* filename=Objects);
	static const std::string ObjectClasses[Loader::ObjectType::Count];	
	
	
	static const std::map<std::string, float> Variables;
};
#endif
