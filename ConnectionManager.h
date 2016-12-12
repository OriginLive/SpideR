#pragma once
#define ASIO_STANDALONE 
#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H


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
#include <unordered_set>





/* ConnectionMaster is initialized.
 * It has an initial url, a set of visited urls.
 * Visit the first url and gather data, if depth is > 1 then gather urls.
 * Some value set to make enforce this behaviour, keeping or throwing urls.
 * Then, if depth > 1, create a connectionmanager and pass it the urls gathered
 * add these urls to the visited list
 * The submanager crawls the site and calls its parse function to gather words into a tree, gather url if required
 * Then pass these back to the master, who will remove duplicate urls, add the data to the tree, and if needed, pass these urls on
 */






class ConnectionManager 
{
	friend class ConnectionMaster;
public:
	ConnectionManager(const std::vector<std::string>& url_list, const bool& gather_urls);
	ConnectionManager(); // This is to prevent the Master from running on auto like its children
	
	std::stringstream stream;
	std::vector<std::string> url_list;
	std::set<std::string> urls_gathered;
	std::vector<std::string> data_gathered;
protected:
	void crawl_list();
	void parse_stream();
	void return_data(std::vector<std::string>& master_url_list, std::set<std::string>& master_data);
	
	bool gather_urls;
};

class ConnectionMaster : public ConnectionManager
{
public:
	ConnectionMaster(const std::string& url);
private:
	std::unordered_set<std::string> urls_visited;
	std::set<std::string> data;
	int max_depth;

	void master_crawl();
};


#endif


