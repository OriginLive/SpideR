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
#include <cstring>
#include <vector>
#include <set>
#include <algorithm>
#include <sstream>
#include <chrono>
#include <ctime>
#include <atomic>
#include <thread>
#include <mutex>
#include <type_traits>
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

	 std::atomic<bool> m_working{false};
	 static std::mutex m_MutexSpiderSet;
	 static std::set<std::shared_ptr<Spider>> m_SpiderSet;


protected:
	
	void operator=(Manager const&) = delete;
	Manager(Manager const&) = delete;


	Manager();
	~Manager();
};

//
// LOGGER
//


namespace Logger
{
	
	class Logger
	{
	public:

		template <typename T>
		inline typename std::enable_if<!std::is_integral<T>::value,Logger&>::type operator<<(const T in)			//TODO make a temporary type, so that log << "text"; is different from log <<"some"<<"text";
		{
			if (Manager::instance().Config->debug == true)
			{
				std::string instring = (std::string)in;
				m_InternalBuffer.append(instring);
				try {
					if (m_InternalBuffer.substr(m_InternalBuffer.size() - 1) == "\n")
					{
						m_Log(m_InternalBuffer);
						Manager::instance().m_display->WriteCurrentEvent(m_InternalBuffer);
						m_InternalBuffer.clear();
					}
				}
				catch (std::out_of_range& e)
				{
					std::cerr << e.what();
					//Do nuffin
				}
			}
			return *this;
		}
		template <typename T>
		inline typename std::enable_if<std::is_integral<T>::value, Logger&>::type operator<<(const T in)
		{
			Logger::operator<< (std::to_string(in));
			return *this;
		}
		template <typename T>
		inline void Log(T in)
		{
			*this<< in;
		}

		static Logger &instance()
		{
			static Logger m_inst;
			return m_inst;
		}

		void SetLog();
	private:
		std::string m_InternalBuffer;
		void m_Log(std::string);
		std::string m_logname = "Log";
		std::ofstream m_file;

	protected:
		void operator=(Logger const&) = delete;
		Logger(Logger const&) = delete;


		Logger();
		~Logger();
	};
	extern Logger &log; // = Logger::instance();
}

#endif // !MANAGER_H
