#include "ConnectionManager.h"
#include "Connection.h"

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
		ConnectionManager child(url_list, gather_urls);
		child.crawl_list();	
		url_list.clear();
		child.return_data(url_list, data);
		
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


ConnectionManager::ConnectionManager(const std::vector<std::string>& other_url_list, const bool& other_gather_urls)
	: url_list(other_url_list), gather_urls(other_gather_urls)
{	
}

/* Iterate through the list */
void ConnectionManager::crawl_list()
{
	while (!url_list.empty())
	{
		auto target_url = url_list.back();
		url_list.pop_back();
		
		Connection socket(target_url);
		if (socket.has_stream())
		{
			std::cout << "Fetched stream. Parsing...\n";
			stream = socket.get_stream();
			parse_stream();
		}
	}
}

void ConnectionManager::parse_stream()
{
	for (std::string temp; std::getline(stream, temp, ' ');)
	{
		switch (Manager::instance().Config->type)
		{
			case unchanged:
				break;
			case small:
				std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
				break;
			case firstcapital:
				std::transform(temp.begin(), temp.begin()++, temp.begin(), ::toupper);
				break;
			case fullcapital:
				std::transform(temp.begin(), temp.end(), temp.begin(), ::toupper);
				break;
			default:
				break;
		}
		
		std::regex imageexpr{"(.*(jpg|png|bmp|gif)+$)"};
		std::regex urlexpr{"([a-zA-Z/:]+[\\.]+[a-zA-Z\\./?=]*[^\\s,@\\\"])"};
		std::regex tagexpr{"<[^>]+>"};
		std::smatch match;
		
		/* Remove image links */
		if (std::regex_search(temp, match, imageexpr))
		{
			continue;
		}
		/* Gather other urls */
		if (gather_urls)
		{
			if (std::regex_search(temp, match, urlexpr))
			{
				urls_gathered.insert(match.str());
			}
		}
		/* Remove tags */
		if (std::regex_search(temp, match, tagexpr))
		{
			continue;
		}
		data_gathered.push_back(temp);
	}
	
}

void ConnectionManager::return_data(std::vector<std::string>& master_url_list, std::set<std::string>& master_data)
{
	std::copy(urls_gathered.begin(), urls_gathered.end(), std::back_inserter(master_url_list));
	std::copy(data_gathered.begin(), data_gathered.end(), std::inserter(master_data, master_data.end()));
}

