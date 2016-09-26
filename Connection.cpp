#include "Connection.h"



Connection::Connection()
{
}


Connection::~Connection()
{
}

asio::io_service Connection::_io_service;

std::stringstream Connection::MakeConnection(std::string url)
{
	std::stringstream ss;
	asio::ip::tcp::iostream requestStream;
	requestStream.expires_from_now(std::chrono::milliseconds(10000));
	std::string host = this->geturl(url);
	std::string suburl = this->getpath(url);

	requestStream.connect(Resolve(host, this->_io_service));

	requestStream
		<< "GET " << suburl << " HTTP/1.1\r\n"
		<< "Host: " << host << "\r\n"
		<< "Connection: close\r\n\r\n";

	std::string oneLine;
	std::getline(requestStream, oneLine);

	while (std::getline(requestStream, oneLine) && oneLine != "\r")
	{
		//std::cout << oneLine << std::endl;
	}

	while (std::getline(requestStream, oneLine))
	{


		std::regex re("\"(.*)\"");
		std::smatch match;
		if (std::regex_search(oneLine, match, re))
		{
			for (int i = 1; i < match.size(); ++i)
			{
				std::string t = match[i];
				std::replace(t.begin(), t.end(), '<', '\0');
				std::replace(t.begin(), t.end(), '>', '\0');
				ss << t << std::endl;
			}
		}

		re = (">(.*)<");
		if (std::regex_search(oneLine, match, re))
		{
			for (int i = 1; i < match.size(); ++i)
			{

				std::string t = match[i];
				std::replace(t.begin(), t.end(), '<', '\0');
				std::replace(t.begin(), t.end(), '>', '\0');
				ss << t << std::endl;
			}
		}
	}
	return ss;
}


asio::ip::tcp::endpoint Connection::Resolve(std::string s, asio::io_service &_resolver)
{
	asio::ip::tcp::resolver resolver(_resolver);
	asio::ip::tcp::resolver::query query(s, "http");
	asio::ip::tcp::resolver::iterator iter = resolver.resolve(query);
	asio::ip::tcp::resolver::iterator end; // End marker.
	asio::ip::tcp::endpoint endpoint;
	while (iter != end)
	{
		endpoint = *iter++;
		//std::cout << endpoint << std::endl;
	}
	return endpoint;
}


std::string inline Connection::getpath(std::string &in)
{
	in = stripHttp(in);
	in = in.substr(geturl(in).length());
	return in;
}

std::string inline Connection::geturl(std::string &in)
{
	in = stripHttp(in);
	if (in.find("/"))
	{
		return in.substr(0, in.find("/"));
	}
	else return in;
}

std::string inline Connection::stripHttp(std::string &in) {
	if (in.compare(0, 7, "http://") == 0)
	{
		return in.substr(7, in.length());
	}
	else if (in.compare(0, 8, "https://") == 0)
	{
		return in.substr(8, in.length());
	}
	else
	{
		return in;
	}
}




ConnectionManager::ConnectionManager(std::string url)
{
	this->Connect(url);
}

ConnectionManager::~ConnectionManager() {};


void ConnectionManager::Connect(std::string url)
{
	// get buffer
	Connection c;
	m_buffer = c.MakeConnection(url);
	this->fetch(m_buffer);
	// digest urls and check rules
	//spawn new url threads
	//put the buffer into a tree
	//write down the tree
	//merge trees and save it into the file
}

void ConnectionManager::fetch(std::stringstream &ss)
{
	for (std::string temp; std::getline(ss, temp, ' ');)
	{
		std::regex re("([a-zA-Z/:]+[\.]+[a-zA-Z\./?=]*[^\s,@])"); // overkill for a single line search...
		std::smatch sm;

		if ((temp.find('\n') != std::string::npos) && (temp.find('\n') != temp.length()))
		{
			std::replace(temp.begin(), temp.end(), '\n', ' ');
			ss << ' ' << temp << ' ';
			continue;
		}
		//check for url, remove them
		//check for dot, remove the dot
		if (std::regex_search(temp, sm, re))
		{
			m_vUrl.push_back(temp);
			continue;
		}
		if (!temp.empty() && temp.at(temp.size() - 1) == '.')
		{
			temp.pop_back();
		}


		m_tree.insert(temp);
		//if ()
	}

	for (auto s : m_tree) { std::cout << s << std::endl; } 	for (auto s : m_vUrl) { std::cout << s << std::endl; }
	std::getchar();
}

