#include "Spider.h"

Spider::Spider(const string_deque& master_url_list, string_list* url_pool, string_set* data_pool, bool gather_urls)
: 
	url_list(master_url_list), 
	url_pool(url_pool),
	data_pool(data_pool),
	gather_urls(gather_urls)
{
}

Spider::Spider()
{
}

void Spider::crawl_list()
{
	while (!url_list.empty())
	{
		AmIStuck = std::chrono::high_resolution_clock::now();
		auto target_url = url_list.back();
		url_list.pop_back();
		if (open_connection(target_url))
		{
			if (Manager::instance().Config->debug)
			{
				std::cout << "Fetched stream from: " << target_url << '\n';
			}
			parse_stream(target_url);
		}
		stream.str(""); // Clear the stream
	}
}

bool Spider::open_connection(std::string target_url)
{
	Connection socket(target_url, stream);
	if (stream.rdbuf()->in_avail()) // If stream is not empty
	{
		return true;
	}
	return false;
}

void Spider::parse_stream(std::string target_url)
{
	Parser parser(utility_tools::get_host(target_url), gather_urls);
	if (parser.load_stream(stream))
	{
		parser.traverse_tree();
		parser.return_data(url_pool, data_pool);
	}
}

Robot_Spider::Robot_Spider(std::string host, std::map<std::string, string_set>* master_exclusion_list)
: host(host)
{
	std::string target_url{host + "/robots.txt"};
	if (Spider::open_connection(target_url))
	{
		parse_stream();
		(*master_exclusion_list)[host].insert(exclusion_set.begin(), exclusion_set.end());
	}
}


void Robot_Spider::parse_stream()
{
	std::string line;
	bool get_paths = false;

	while (std::getline(stream, line))
	{
		if (line == user_agent)
		{
			get_paths = true;
		}
		else if (get_paths && !line.empty())
		{
			std::string path;
			if (line.substr(0, disallow.length()) == disallow)
			{
				path = line.substr(disallow.length(), std::string::npos);
				exclusion_set.insert(path);
			}
			else if (line.empty())
			{
				get_paths = false;
			}
		}
		else
		{
			get_paths = false;
		}
	}
}


				
