#pragma once
#ifndef MANAGER_H
#define MANAGER_H
#define _CRT_SECURE_NO_WARNINGS

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

enum SortingType { unchanged, lowercase, capitalize, uppercase };

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

	std::atomic<bool> m_working{ false };
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
	namespace internal {
		struct Liner;
	}

	class Logger
	{
	public:
		friend internal::Liner;

		operator internal::Liner() const;

		template <typename T>
		inline void Log(T in)
		{
			internal::Liner() << in;
		}

		static Logger& instance()
		{
			static Logger m_inst;
			return m_inst;
		}

		void SetLog();
	private:
		void m_Log(std::string);
		std::string m_logname = "Log.txt";
		std::ofstream m_file;

	protected:
		void operator=(Logger const&) = delete;
		Logger(Logger const&) = delete;


		Logger();
		~Logger();
	};
	namespace internal
	{
		struct Liner {
			friend class Logger;
			bool Owned = true;
			Liner() = default;
			Liner(Liner &&O) : p_s_{ std::move(O.p_s_) } { O.Owned = false; } //Not actually used 0o
			~Liner()
			{
				if (Owned)
				{
					*p_s_ << std::endl;
					Logger::instance().m_Log(p_s_->str());
					Manager::instance().m_display->WriteCurrentEvent(p_s_->str());
				}
			}

			std::unique_ptr<std::stringstream> p_s_{ new std::stringstream() };
		};

		template <typename T>
		const Liner &operator<<(const Liner &L, T &&E) {
			*L.p_s_ << std::forward<T>(E);
			return L;
		}
	}
	inline Logger::operator internal::Liner() const { return {}; }
	extern Logger &log; // = Logger::instance();
}
using Logger::internal::operator<<;


#endif // !MANAGER_H
