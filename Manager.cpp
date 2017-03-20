#include "Manager.h"



void Manager::FireCommand(std::string in)
{
	std::stringstream ss;
	ss << in.data();
	std::string temp;
	std::getline(ss, temp, ' ');
	if (m_CommandList.find(temp) == m_CommandList.end())
	{
		std::cout << "err"; //hmm  Manager::instance().RegisterCommand("err", [=](std::string err) { display->WriteOut(err); });
	}
	else
	{
		if (temp == "connect") // ultra stupid, instead of looking for specific commands, perhaps a better use would be to have an Event class which held templated data, and an id with enum/guid.
		{
			std::string temp2;
			std::getline(ss, temp2, ' ');
			m_CommandList[temp](static_cast<void*>(&temp2));
		}
		else
		{
			m_CommandList[temp](nullptr);
		}
	}
	ss.clear();
}

std::vector<std::string> Manager::ListCommands(const std::string & in) {
	std::vector<std::string> vec;
	auto it = m_CommandList.lower_bound(in);
	if (it == m_CommandList.end()) { return vec; }
	for (; it != m_CommandList.end(); ++it)
	{
		auto res = std::mismatch(in.begin(), in.end(), it->first.begin(), it->first.end());

		if (res.first == in.end())
		{
			vec.push_back(it->first);
		}
		else
		{
			break;
		}
	}
	return vec;
}

void Manager::ReadConfig() {
	Config = std::make_unique<Settings>();

	std::ifstream file("Settings.json", std::ifstream::in);
	if (file.is_open())
	{

		std::string s;
		file.seekg(0, std::ios::end);
		s.reserve(file.tellg());
		file.seekg(0, std::ios::beg);
		s.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

		rapidjson::Document doc;
		doc.Parse(s.c_str());

		this->Config->textspeed = doc["textspeed"].GetInt();
		this->Config->depth = doc["depth"].GetInt();
		this->Config->debug = doc["debug"].GetInt();
		auto it = this->Config->eMap.find(doc["type"].GetString());
		if (it != this->Config->eMap.end())
		{
			this->Config->type = it->second;
		}
		else
		{
			std::cerr << "Wrong type, available types are \"unchanged, allsmall, firstcapital, fullcapital\".";
		}

	}
	else
	{
		std::cerr << "Error opening settings file.";
	}
	file.close();
}

void Manager::WriteToFile(const std::set<std::string>& data)
{
	std::cout << "Writing to file..\n";
	std::ofstream file("Output.txt", std::ifstream::out);
	if (file.is_open())
	{
		std::copy(data.begin(), data.end(), std::ostream_iterator<std::string>(file, "\n"));
	}
	else
	{
		std::cerr << "Error saving the file.";
	}
	file.close();
}

Manager::Manager()
{
}


Manager::~Manager()
{
}

Settings::Settings()
{
	eMap.insert(std::pair<std::string, SortingType>("unchanged", unchanged));
	eMap.insert(std::pair<std::string, SortingType>("allsmall", allsmall));
	eMap.insert(std::pair<std::string, SortingType>("firstcapital", firstcapital));
	eMap.insert(std::pair<std::string, SortingType>("fullcapital", fullcapital));
}
