#ifndef PARSER_H
#include <regex>
#include <set>
#include <vector>
#include <string>
#include <stack>
#include <sstream>

#include "gumbo.h"

const std::regex imageexpr{"(.*(jpg|png|bmp|gif)+$)"};
const std::regex urlexpr{"([a-zA-Z/:]+[\\.]+[a-zA-Z\\./?=]*[^\\s,@\\\"])"};

class Parser
{
	friend class ConnectionManager;

	Parser(bool other_gather_urls);
	~Parser();

	bool load_stream(std::stringstream& stream);
	void traverse_tree();
	void search_for_link(GumboNode* node);
	void return_data(std::vector<std::string>* const url_pool, std::set<std::string>* const data_pool);
	

	GumboOutput* output;
	bool gather_urls;
	std::set<std::string> urls_gathered;
	std::vector<std::string> data_gathered;
};

#endif
