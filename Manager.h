#pragma once
#ifndef MANAGER_H
#define MANAGER_H

#include <map>
#include <string>
#include <map>
#include <functional>
#include <iostream>
#include <fstream>
#include "Console.h"
#include <vector>
#include <algorithm>
#include "Console.h"
#include <sstream>
#include "rapidjson\document.h"

enum SortingType {unchanged, small, firstcapital, fullcapital};

class Settings
{
public:
	Settings(); //Horrible :<
	int textspeed = 0;
	SortingType type = unchanged;
	std::map<std::string, SortingType> eMap;
};



class Manager
{
public:
	//template <typename T>
	std::map<std::string, std::function<void(void*)>> m_CommandList {};

	static Manager &instance() {
		static Manager m_inst;
		return m_inst;
	}

	void RegisterCommand(std::string in, std::function<void(void*)> lambda) {
		m_CommandList[in] = lambda;
	};

	void FireCommand(std::string in)
	{
		std::stringstream ss;
		ss << in.data();
		std::string temp;
		std::getline(ss, temp, ' ');
		if (m_CommandList.find(temp) == m_CommandList.end())
		{
			std::cout << "err"; //hmm  Manager::instance().RegisterCommand("err", [=](std::string err) { display->WriteOut(err); });
		}
		else
		{
			if (temp == "connect") // ultra stupid, instead of looking for specific commands, perhaps a better use would be to have an Event class which held templated data, and an id with enum/guid.
			{
				std::string temp2;
				std::getline(ss, temp2, ' ');
				m_CommandList[temp](static_cast<void*>(&temp2));
			}
			else
			{
				m_CommandList[temp](nullptr);
			}
		}
		ss.clear();
	}

	std::vector<std::string> ListCommands(const std::string &in) {
		std::vector<std::string> vec;
		auto it = m_CommandList.lower_bound(in);
		if (it == m_CommandList.end()) { return vec; }
		for (;it != m_CommandList.end(); ++it)
		{
			auto res = std::mismatch(in.begin(), in.end(), it->first.begin(), it->first.end());

			if (res.first == in.end())
			{
				vec.push_back(it->first);
			}
			else
			{
				break;
			}
		}
		return vec;
	}

	void ReadConfig() {
		Config = std::make_unique<Settings>();
		
		std::ifstream file("Settings.json", std::ifstream::in);
		if (file.is_open()) 
		{

			std::string s;
			file.seekg(0, std::ios::end);
			s.reserve(file.tellg());
			file.seekg(0, std::ios::beg);
			s.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

			rapidjson::Document doc;
			doc.Parse(s.c_str());

			this->Config->textspeed = doc["textspeed"].GetInt();
			auto it = this->Config->eMap.find(doc["type"].GetString());
			if (it != this->Config->eMap.end())
			{
				this->Config->type = it->second;
			}
			else
			{
				std::cerr << "Wrong type, available types are \"unchanged, small, firstcapital, fullcapital\".";
			}

		}
		else
		{
			std::cerr << "Error opening settings file.";
		}
		file.close();
	}


protected:
	Console* m_display;
	std::unique_ptr<Settings> Config;
	void operator=(Manager const&) = delete;
	Manager(Manager const&) = delete;


	Manager();
	~Manager();
};

#endif // !MANAGER_H