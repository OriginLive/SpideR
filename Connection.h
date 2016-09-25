#pragma once
#define ASIO_STANDALONE 
#include<string>
#include "asio-1.10.6\include\asio.hpp"
#include <iostream>
#include <chrono>
#include <regex>
#include "Manager.h"



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