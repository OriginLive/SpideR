#pragma once
#define ASIO_STANDALONE 
#ifndef CONNECTION_H
#define CONNECTION_H


#include<string>
#include "asio-1.10.6\include\asio.hpp"
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



class Connection
{
public:
	std::stringstream MakeConnection(std::string url);
	Connection();
	~Connection();

private:
	asio::ip::tcp::endpoint Resolve(std::string s, asio::io_service &_resolver);
	std::string stripHttp(std::string&);
	std::string geturl(std::string&);
	std::string getpath(std::string&);

	
	static asio::io_service _io_service;
};

class ConnectionManager // Event Logic here? Wouldn't it be smarter to use event logic in the callback?
{
public:

	std::stringstream m_buffer;
	std::vector<std::string> m_vUrl;
	std::set<std::string> m_tree;
	ConnectionManager(std::string url);
	~ConnectionManager();

private:
	void WriteToFile(std::set<std::string>); //Perhaps this shouldn't be here, but in a generic IO writer class /under manager?/
	void Connect(std::string url);
	std::set<std::string> ConnectionManager::fetch(std::stringstream &ss);

};


#endif // !CONNECTION_H