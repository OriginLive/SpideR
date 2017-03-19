#ifndef SPIDER_H
#define SPIDER_H

#include <vector>
#include <queue>
#include <memory>
#include <sstream>

#include "Connection.h"
#include "Parser.h"
#include "Queen.h"
typedef std::vector<std::string> string_vector;
typedef std::deque<std::string> string_deque;
typedef std::set<std::string> string_set;
typedef std::list<std::string> string_list;

class Spider
{
	friend class Queen;
protected:
	Spider(const string_deque& master_url_list, string_list* url_pool, string_set* data_pool, bool gather_urls);
	Spider();
	void crawl_list();
	bool open_connection(std::string target_url);
	void parse_stream(std::string target_url);

	std::stringstream stream;
	string_deque url_list;
	string_list* url_pool; // Pointer
	string_set* data_pool;
	bool gather_urls;
};

class Robot_Spider : public Spider
{
	friend class Queen;
	Robot_Spider(std::string host, std::map<std::string, string_set>* master_exclusion_list);
	void parse_stream();
	
	std::string host;
	std::pair<std::string, std::set<std::string>> exclusion_list;
	const std::string user_agent{"User-agent: *"};
	const std::string disallow{"Disallow: "};
	
};

#endif
