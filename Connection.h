#pragma once
#define ASIO_STANDALONE 
#ifndef CONNECTION_H
#define CONNECTION_H

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>


#include <string>
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
	Connection(const std::string&, std::stringstream& stream);
	bool has_stream();
	std::stringstream get_stream();

private:
	void resolve_connection();
	std::string url;
	std::stringstream& streamhandle;
};

#endif // !CONNECTION_H
