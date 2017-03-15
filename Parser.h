#ifndef PARSER_H
#include <regex>
#include <set>
#include <deque>
#include <vector>
#include <string>
#include <sstream>
#include <stack>
#include <list>

#include "gumbo.h"

const std::regex imageexpr{"(.*(jpg|png|bmp|gif)+$)"};
const std::regex urlexpr{"([a-zA-Z/:]+[\\.]+[a-zA-Z\\./?=]*[^\\s,@\\\"])"};

class Parser
{
	friend class Spider;

	Parser(std::string host, bool other_gather_urls);
	~Parser();

	bool load_stream(std::stringstream& stream);
	void traverse_tree();
	void get_link(GumboNode* node);
	std::string format_link(std::string link);
	void return_data(std::list<std::string>* const url_pool, std::set<std::string>* const data_pool);
	
	GumboOutput* output;
	std::string host;
	bool gather_urls;
	std::deque<std::string> urls_gathered;
	std::deque<std::string> data_gathered;
};

#endif
