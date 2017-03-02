#include "ConnectionManager.h"
#include "Connection.h"
#include "Parser.h"

ConnectionMaster::ConnectionMaster(const std::string& other_url)
{
	std::cout << "Constructed ConnectionMaster.\n";
	url_list.push_back(other_url);
	max_depth = Manager::instance().Config->depth;
	master_crawl();
}

/* Manage the whole crawling process
 * Send urls to children and gather their results */
void ConnectionMaster::master_crawl()
{
	for (int i = 0; i < max_depth && !url_list.empty(); i++)
	{
		std::cout << "Crawling depth " << i + 1 << " out of max_depth " << max_depth << ".\n";

		/* Mark urls to be sent as visited */
		std::copy(url_list.begin(), url_list.end(), std::inserter(urls_visited, urls_visited.end()));
		gather_urls = (i < max_depth - 1 ? 1 : 0);
		ConnectionManager child(&url_list, &data, url_list, gather_urls);
		url_list.clear();
		child.crawl_list(); // Child returns data through ptr
		
		/* Remove urls already visited from the list */
		for (auto it = url_list.begin(); it != url_list.end(); ++it)
		{
			auto search = urls_visited.find(*it);
			if (search != urls_visited.end())
			{
				it = url_list.erase(it);
			}
		}
	}
	/* Save data */
	Manager::instance().WriteToFile(data);
}
/////////////////////////////////////////////////////////////////////////////

ConnectionManager::ConnectionManager()
{
}


ConnectionManager::ConnectionManager
(
	std::vector<std::string>* const url_pool_ptr,
	std::set<std::string>* const data_pool_ptr,
	const std::vector<std::string>& other_url_list,
	const bool& other_gather_urls
)
	:
	url_pool(url_pool_ptr),
	data_pool(data_pool_ptr),
	url_list(other_url_list),
	gather_urls(other_gather_urls)
{	
}

/* Iterate through the list */
void ConnectionManager::crawl_list()
{
	while (!url_list.empty())
	{
		auto target_url = url_list.back();
		url_list.pop_back();
		
		Connection socket(target_url, stream);
		if (stream.rdbuf()->in_avail()) // If stream is not empty
		{
			std::cout << "Fetched stream. Parsing...\n";
			parse_stream();
		}
		stream.str(""); // Clear the stream
	}
}

void ConnectionManager::parse_stream()
{
	Parser parser(gather_urls);
	if (parser.load_stream(stream))
	{
		parser.traverse_tree();
		parser.return_data(url_pool, data_pool);
	}
}

