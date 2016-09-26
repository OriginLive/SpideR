#pragma once
#include <map>
#include <string>
#include <map>
#include <functional>
#include <iostream>
#include "Console.h"
#include <vector>
#include <algorithm>
#include "Console.h"


struct Settings
{
	int speed = 0;
	std::string izbira = "";
};



class Manager
{
public:
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
		if (m_CommandList.find(in) == m_CommandList.end())
		{
			std::cout << "err"; //hmm  Manager::instance().RegisterCommand("err", [=](std::string err) { display->WriteOut(err); });
		}
		else
		{
			m_CommandList[in](nullptr);
		}
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



protected:
	Console* m_display;
	void operator=(Manager const&) = delete;
	Manager(Manager const&) = delete;


	Manager();
	~Manager();
};