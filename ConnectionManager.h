#pragma once
#define ASIO_STANDALONE 
#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#ifdef _WIN32
#include "asio-1.10.6\include\asio.hpp"
#elif defined __linux__
#include "asio-1.10.6/include/asio.hpp"
#endif

#include<string>
#include <iostream>
#include <chrono>
#include <regex>
#include "Manager.h"
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <set>


class ConnectionManager // Event Logic here? Wouldn't it be smarter to use event logic in the callback?
{
public:
	ConnectionManager();
	ConnectionManager(const std::string& url);
	virtual ~ConnectionManager();
	
	std::stringstream m_buffer;
	std::vector<std::string> m_vUrl;
	std::set<std::string> m_tree;
private:
	void WriteToFile(std::set<std::string>); //Perhaps this shouldn't be here, but in a generic IO writer class /under manager?/
	virtual void Connect(std::string url);
	virtual void fetch(std::stringstream &ss);
	
	int depth = 1;
};

class ConnectionDelegate : public ConnectionManager // a it of duplication and usless initialization, but hopefully it isn't too bad
{
public:
	ConnectionDelegate(const ConnectionManager&);
	void PassData(std::vector<std::string> &urlList, std::set<std::string> &wordTree);

};
#endif


