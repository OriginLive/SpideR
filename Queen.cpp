#include "Queen.h"

Queen::Queen(std::string url):
	current_depth(0),
	max_depth(Manager::instance().Config->depth)
	{
	url_pool.push_back(url);
	crawl();
	save_data();
	Logger::log << "Finished!\n";
	}


void Queen::crawl()
{
	while (current_depth++ <= max_depth && !(url_pool.empty()))
	{

		Logger::log << "Crawling depth: " << current_depth << " out of " << max_depth << "\n";
		check_url_pool();
		bool gather_urls = (current_depth < max_depth? true : false);
		add_to_visited();
		string_deque urls_to_send;
		std::copy(url_pool.begin(), url_pool.end(), std::back_inserter(urls_to_send));
		url_pool.clear();
		Spider child(urls_to_send, &url_pool, &data_pool, gather_urls);
		child.crawl_list();
	}

}

void Queen::check_url_pool()
{
	for (auto it = url_pool.begin(); it != url_pool.end(); ++it)
	{
		// Remove duplicates
		auto visited_search = urls_visited.find(*it);
		if (visited_search != urls_visited.end())
		{
			it = url_pool.erase(it);
		}
		// If we are being polite
		else if (Manager::instance().Config->polite)
		{
			std::string host = utility_tools::get_host(*it);
			auto exclusion_search = exclusion_list.find(host);
			if (exclusion_search != exclusion_list.end())
			{
				std::string path = utility_tools::get_path(*it);
				auto path_search = (exclusion_search->second).find(path);
				if (path_search != (exclusion_search->second).end())
				{
					it = url_pool.erase(it);
					if (Manager::instance().Config->debug)
					{
						Logger::log << "Host: " << host << " Path: " << path << " found in exclusion list. Skipping...\n";
					}
					break;
				}
			}	
			else 
			{
				if (Manager::instance().Config->debug)
				{
					Logger::log << "Fetching robots.txt from " << host<< "\n";
				}
				read_robots_txt(*it);
				urls_visited.insert(host +"/robots.txt"); // WHAT IF IT 503's TO ROBOTS.TXT 
				
			}
		}
	}
}

void Queen::read_robots_txt(std::string url)
{
	std::string host = utility_tools::get_host(url);
	Robot_Spider robo(host, &exclusion_list);
}

void Queen::add_to_visited()
{
	std::copy(url_pool.begin(), url_pool.end(), std::inserter(urls_visited, urls_visited.end()));
}

void Queen::save_data()
{
	Manager::instance().WriteToFile(data_pool);
}

