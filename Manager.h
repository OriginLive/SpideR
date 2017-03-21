#pragma once
#ifndef MANAGER_H
#define MANAGER_H

#ifdef _WIN32
#include "rapidjson\document.h"
#elif defined __linux__
#include "rapidjson/document.h"
#endif

#include <map>
#include <string>
#include <map>
#include <functional>
#include <iostream>
#include <fstream>
#include "Console.h"
#include <vector>
#include <set>
#include <algorithm>
#include "Console.h"
#include <sstream>
#include <chrono>
#include <ctime>


enum SortingType {unchanged, allsmall, firstcapital, fullcapital};

class Settings
{
public:
	Settings(); //Horrible :<
	int textspeed = 0;
	int depth = 2;
	bool debug;
	bool polite;
	bool show_http;
	SortingType type = unchanged;
	std::map<std::string, SortingType> eMap;
};


//
// LOGGER
//


class Logger
{
public:
	void operator<<(std::string);
	void Log(std::string);





};







//
// MANAGER
//


class Manager
{
public:


	static Manager &instance()
	{
		static Manager m_inst;
		return m_inst;
	}

	void RegisterCommand(std::string in, std::function<void(void*)> lambda)
	{
		m_CommandList[in] = lambda;
	};

	 void FireCommand(std::string in);
	 std::vector<std::string> ListCommands(const std::string &in);
	 void ReadConfig();
	 void WriteToFile(const std::set<std::string>& data);




	std::unique_ptr<Settings> Config;
	//template <typename T>
	std::map<std::string, std::function<void(void*)>> m_CommandList{};

	void Log(std::string);




protected:
	Console* m_display;
	void operator=(Manager const&) = delete;
	Manager(Manager const&) = delete;


	Manager();
	~Manager();
};

#endif // !MANAGER_H
