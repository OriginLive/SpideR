#ifndef QUEEN_H
#define QUEEN_H
#include <vector>
#include <list>
#include <unordered_set>
#include <set>
#include <map>
#include "Spider.h"
#include "Manager.h"
#include "Utility.h"

typedef std::vector<std::string> string_vector;
typedef std::deque<std::string> string_deque;
typedef std::set<std::string> string_set;
typedef std::list<std::string> string_list;

/********************************
 *            QUEEN             *
 ********************************
 * 
 * Queen is spawned with 1 or more urls
 * Main loop cf current depth <= max depth, 
 * and there are still links in the url_pool
 *
 * If program is set to be polite
 * check if there is an exclusion list for each url gathered
 * If not, send a robot_spider to get it (group urls under hosts? to avoid checking too much)
 * Also check if there are urls that have already been visited
 *
 * Compile a list of urls and spawn a spider to crawl them
 * 
 */
 

class Queen
{
public:
	Queen(std::string url);

private:
	void crawl();
	void check_url_pool();
	void read_robots_txt(std::string url);
	void add_to_visited();
	void save_data();
	
	uint32_t current_depth;
	uint32_t max_depth;
	bool polite;
	string_list url_pool;
	string_set data_pool;
	std::map<std::string, string_set> exclusion_list;
	std::unordered_set<std::string> urls_visited;
};

#endif
