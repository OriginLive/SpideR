#pragma once
#define ASIO_STANDALONE 
#ifndef CONNECTION_H
#define CONNECTION_H

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



class Connection
{
public:
	Connection(const std::string&);
	~Connection();
	bool has_stream();
	std::stringstream get_stream();

private:
	void send_get();
	void resolve_connection();
	std::string strip_http(const std::string&);
	std::string get_host(const std::string&);
	std::string get_path(const std::string&);

	asio::ip::tcp::iostream socket;
	static asio::io_service _io_service;
	std::stringstream stream;
	std::string url;
	std::string host;
	std::string path;
};

#endif // !CONNECTION_H
