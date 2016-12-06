#include "ConnectionManager.h"
#include "Connection.h"

ConnectionDelegate::ConnectionDelegate(const ConnectionManager& manager)
{
	m_vUrl= manager.m_vUrl;
	m_tree = manager.m_tree;
}

ConnectionManager::ConnectionManager()
{
}

ConnectionManager::ConnectionManager(const std::string& url)
{	
	std::vector<ConnectionManager> DepthList(depth);
	for (int i = 0; i < depth; ++i)
	{
		if (i == 0)
		{
			DepthList[0].Connect(url);
			continue;
		}
		
		auto sit =  DepthList.begin() + i - 1;
		ConnectionDelegate del(*sit);
		del.PassData(DepthList[i].m_vUrl, DepthList[i].m_tree);
		
		for (int j = i-1; j >= 0; --j)
		{
			for (auto it = DepthList[j].m_vUrl.begin(); it != DepthList[j].m_vUrl.end(); ++it)
			{
				for (auto itm = DepthList[depth].m_vUrl.begin(); itm != DepthList[depth].m_vUrl.end(); ++itm)
				{
					if (itm->compare(*it) == 0)
					{
						DepthList[depth].m_vUrl.erase(itm);
					}
				}
			}
		}
		DepthList[0].m_tree.insert(DepthList[depth].m_tree.begin(), DepthList[depth].m_tree.end());
	}
	WriteToFile(DepthList[0].m_tree);
}

ConnectionManager::~ConnectionManager() {};



void ConnectionDelegate::PassData(std::vector<std::string>& urlList, std::set<std::string>& wordTree)
{
	urlList.insert(urlList.end(), this->m_vUrl.begin(), this->m_vUrl.end());
	wordTree.insert(this->m_tree.begin(), this->m_tree.end());
}


void ConnectionManager::Connect(std::string url) // Logic here
{
	// get buffer
	Connection c(url);
	std::cout << "Fetching stream.\n";
	m_buffer = c.get_stream();
	this->fetch(m_buffer);
	m_buffer.flush();

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
			switch (Manager::instance().Config->type) //Snitches be bad, what would be a better way to implement settings, perhaps by using a state->rules() callback?
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
			
		std::regex re("([a-zA-Z/:]+[\.]+[a-zA-Z\./?=]*[^\s,@\\\"])"); // overkill for a single line search...
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
			if (sm[1].str().substr(sm[1].str().size() - 4) != ".gif") // add moar, CHECK FOR SETTINGS AND APPLY THE RULES
			{
				m_vUrl.push_back(sm[1]);
			}
			continue;
		}
		if (!temp.empty() && temp.at(temp.size() - 1) == '.')
		{
			temp.pop_back();
		}
		
		std::cout << temp << '\n';
		m_tree.insert(temp);
		//if ()
	}
	
}

void ConnectionManager::WriteToFile(std::set<std::string> treeIn)
{
	std::ofstream file("Output.txt", std::ifstream::out);
	if (file.is_open())
	{
		std::copy(treeIn.begin(), treeIn.end(), std::ostream_iterator<std::string>(file, " "));
	}
	else
	{
		std::cerr << "Error saving the file.";
	}
	file.close();
}


