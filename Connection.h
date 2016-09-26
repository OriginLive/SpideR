#pragma once
#define ASIO_STANDALONE 
#include<string>
#include "asio-1.10.6\include\asio.hpp"
#include <iostream>
#include <chrono>
#include <regex>
#include "Manager.h"
#include <sstream>



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

class ConnectionManager
{
public:
	void Connect(std::string url)
	{
		Connection c;
		c.MakeConnection(url);
		// get buffer
		// digest urls and check rules
		//spawn new url threads
		//put the buffer into a tree
		//write down the tree
		//merge trees and save it into the file
	}
	std::stringstream m_buffer;
	ConnectionManager();
	~ConnectionManager();

};