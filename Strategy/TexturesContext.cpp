#ifndef TEXTURES_CONTEXT
#define TEXTURES_CONTEXT
#include "Global.h"
std::map<std::wstring,std::vector<sf::Image>>
Global::TexturesContext::images=std::map<std::wstring,std::vector<sf::Image>>();
std::map<std::wstring,std::vector<sf::Texture>>
Global::TexturesContext::textures=std::map<std::wstring,std::vector<sf::Texture>>();


const std::map<std::wstring,std::vector<sf::Image>>& Global::TexturesContext::GetImages()
{
	return Global::TexturesContext::images;
}
const std::map<std::wstring,std::vector<sf::Texture>>& Global::TexturesContext::GetTextures()
{
	return Global::TexturesContext::textures;
}


void Global::TexturesContext::LoadImages(const char* filename)
{
	try
	{
		std::map<std::wstring,std::vector<sf::Image> > images;
		std::vector<std::wstring> lines;
		{
			std::cout << "Loading textures" << std::endl;
			std::wstring fullText = ReadUtf8File(filename);
			lines = WStringToVector(fullText);
		}
		std::vector<std::wstring>words;
		std::vector<std::pair<std::wstring,std::wstring>>classPaths;
		std::pair<std::wstring,std::wstring>currPair;
		for(std::vector<std::wstring>::iterator it=lines.begin();it!=lines.end();++it)
		{
			if(STLStringIsEmpty(*it))
			continue;
			words=FindWords(*it);
			if(words.size()!=2)
			{
				throw std::runtime_error("Uncorred setting for texture pack\n");
				return;
			}
			currPair.first=words[0];
			currPair.second=words[1];
			words.clear();
			
			
			if(std::find(classPaths.begin(),classPaths.end(),currPair)!=classPaths.end())
			{
				std::cout<<"Path is repeats"<<std::endl;
				continue;
			}
			
			classPaths.push_back(currPair);
			
			
			sf::Image im;
			im.loadFromFile((char*)currPair.second.c_str());
			im.createMaskFromColor(sf::Color::White);
			images[currPair.first].push_back(im);
			
			std::wcout<<L"New image for "<<currPair.first<<std::endl<<L"Image path: "<<
			currPair.second<<std::endl<<L"Image size:"<<im.getSize().x*im.getSize().y*4<<std::endl;
		}
		Global::TexturesContext::images=images;
	}
	catch(const std::exception& ex)
	{
		std::cerr<<ex.what()<<std::endl;
		std::cout<<ex.what()<<std::endl;
	}
}
void Global::TexturesContext::InitTextures()
{
	std::map<std::wstring,std::vector<sf::Texture>> textures;
	for
	(
		auto i=Global::TexturesContext::images.begin();
		i!=Global::TexturesContext::images.end();
		++i
	)
	{
		std::vector<sf::Texture>currTextures;
		sf::Texture t;
		for(std::vector<sf::Image>::const_iterator j=i->second.begin();j!=i->second.end();++j)
		{
			t.loadFromImage(*j);
			currTextures.push_back(t);
		}
		textures[i->first]=currTextures;
	}
	Global::TexturesContext::textures=textures;
}

#endif
