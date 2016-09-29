#include "Manager.h"



Manager::Manager()
{
}


Manager::~Manager()
{
}

Settings::Settings()
{
	eMap.insert(std::pair<std::string, SortingType>("unchanged", unchanged));
	eMap.insert(std::pair<std::string, SortingType>("small", small));
	eMap.insert(std::pair<std::string, SortingType>("firstcapital", firstcapital));
	eMap.insert(std::pair<std::string, SortingType>("fullcapital", fullcapital));
}
