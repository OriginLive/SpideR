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
#include <functional>
#include <iostream>
#include <fstream>
#include "Console.h"
#include <vector>
#include <set>
#include <algorithm>
#include <sstream>
#include <chrono>
#include <ctime>
#include <atomic>
#include <thread>
#include <mutex>
class Spider; // Forward decleration "Spider.h"


enum SortingType {unchanged, lowercase, capitalize, uppercase};

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
	Logger& operator<<(std::string);
	void Log(std::string);

	static Logger &instance()
	{
		static Logger m_inst;
		return m_inst;
	}

	void SetLog();
private:
	void m_Log(std::string);
	std::string m_logname ="Log";
	std::ofstream m_file;

protected:
	void operator=(Logger const&) = delete;
	Logger(Logger const&) = delete;


	Logger();
	~Logger();
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
	 void SetDisplay(std::shared_ptr<Console>);

	 static void CheckProgress();


	 std::shared_ptr<Console> m_display;
	 std::unique_ptr<Settings> Config;
	 //template <typename T>
	 std::map<std::string, std::function<void(void*)>> m_CommandList{};

	 std::atomic<bool> m_working = false;
	 static std::mutex m_MutexSpiderSet;
	 static std::set<std::shared_ptr<Spider>> m_SpiderSet;


protected:
	
	void operator=(Manager const&) = delete;
	Manager(Manager const&) = delete;


	Manager();
	~Manager();
};

#endif // !MANAGER_H
