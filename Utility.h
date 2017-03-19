#ifndef UTILITY_HPP
#define UTILITY_HPP

namespace utility_tools
{
	inline int find_http_length(std::string url)
	{
		if (url.compare(0, 7, "http://") == 0)
		{
			return 7;
		}
		else if (url.compare(0, 8, "https://") == 0)
		{
			return 8;
		}
		else
		{
			return 0;
		}
	}

	inline std::string get_host(std::string url)
	{
		int start = find_http_length(url);
		auto search = url.find('/', start);
    		return url.substr(0, search);
	}

	inline std::string get_path(std::string url)
	{
		int start = find_http_length(url);
		auto search = url.find('/', start);
		if (search != std::string::npos)
		{
			url = url.substr(search, std::string::npos);
		}
		if (url.empty())
		{
			url = '/';
		}
		return url;
	}
}

#endif


