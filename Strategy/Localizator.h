#ifndef LOCALIZATOR_H
#define LOCALIZATOR_H

#include <SFML/System/String.hpp>
#include <string>
#include <vector>
#include <iterator>
#include <map>


struct Localizator
{
	static const std::map<std::string, std::vector<sf::String> > Localization;
};

const std::map<std::string, std::vector<sf::String> > Localizator::Localization=
[]() -> std::map<std::string, std::vector<sf::String> >
{
	std::map<std::string, std::vector<sf::String> > locale;
	for
	(
		std::map<std::string, std::vector<std::string> >::const_iterator it=Loader::LocaledText.begin();
		it!=Loader::LocaledText.end();
		++it
	)
	locale[it->first]=Loader::STLStringToSF(it->second);
	
	
	return locale;
}();
#endif
