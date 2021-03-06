#include "Manager.h"
#include "Spider.h"

void Manager::FireCommand(std::string in)
{
	m_working = true;
	std::stringstream ss;
	ss << in.data();
	std::string temp;
	std::getline(ss, temp, ' ');
	if (m_CommandList.find(temp) == m_CommandList.end())
	{
		std::cerr << "err, " << temp << " is not a valid command\n"; //hmm  Manager::instance().RegisterCommand("err", [=](std::string err) { display->WriteOut(err); });
	}
	else
	{
		if (temp == "connect") // ultra stupid, instead of looking for specific commands, perhaps a better use would be to have an Event class which held templated data, and an id with enum/guid.
		{
			Logger::log.SetLog();
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
	m_working = false;
}

std::vector<std::string> Manager::ListCommands(const std::string & in)
{
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

void Manager::ReadConfig()
{
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
		this->Config->debug = !!doc["debug"].GetInt();
		this->Config->polite = !!doc["polite"].GetInt();
		this->Config->show_http = !!doc["show_http"].GetInt();
		auto it = this->Config->eMap.find(doc["type"].GetString());
		if (it != this->Config->eMap.end())
		{
			this->Config->type = it->second;
		}
		else
		{
			std::cerr << "Wrong type, available types are \"unchanged, allsmall, firstcapital, fullcapital\".";
			Logger::log << "Wrong settings type error";
		}

	}
	else
	{
		std::cerr << "Error opening settings file.";
		Logger::log << "Error opening settings file.";
	}
	file.close();
}

void Manager::WriteToFile(const std::set<std::string>& data)
{
	Logger::log << "Writing to file..";
	std::ofstream file("Output.txt", std::ifstream::out);
	if (file.is_open())
	{
		std::copy(data.begin(), data.end(), std::ostream_iterator<std::string>(file, "\n"));
	}
	else
	{
		std::cerr << "Error saving the file.";
		Logger::log << "Error saving the file.";
	}
	file.close();
}

void Manager::SetDisplay(std::shared_ptr<Console> console)
{
	m_display = console;
}

void Manager::CheckProgress() // POOLING SUCKS, THINK OBSERVER OR CONDITION_VARIABLE
{
	std::thread t1;
	bool active = false;
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));

		if (Manager::instance().m_working == true)
		{
			if (Manager::instance().m_display->progress.load() == false)
			{
				t1 = std::thread(std::bind(&Console::ProgressStar, Manager::instance().m_display)); //Spin the star
				active = true;
			}

			if (m_SpiderSet.size() != 0)
				for (auto s : m_SpiderSet)
				{
					auto x = s->AmIStuck;
					auto timenow = std::chrono::high_resolution_clock::now();
					std::chrono::duration<double> diff = timenow - x;// FOR EACH SPIDER, AmIStuck?
					if (diff.count() > 10)
					{
						std::cerr << &s << " Is taking " << std::chrono::duration_cast<std::chrono::seconds>(diff).count() << "s to check: " << s->CurrentUrl << std::endl;
					}//More than 10s have passed, so it's stuck in a loop?
				}
		}
		if (active)
		{
			t1.join();
			active = false;
		}

	}
}

std::set<std::shared_ptr<Spider>> Manager::m_SpiderSet;

Manager::Manager()
{
}


Manager::~Manager()
{
}

Settings::Settings()
{
	eMap.insert(std::pair<std::string, SortingType>("unchanged", unchanged));
	eMap.insert(std::pair<std::string, SortingType>("lowercase", lowercase));
	eMap.insert(std::pair<std::string, SortingType>("capitalize", capitalize));
	eMap.insert(std::pair<std::string, SortingType>("uppercase", uppercase));
}



/* Inlined code
/////////////////////////////////
template <typename T>
inline typename std::enable_if<!std::is_integral<T>::value, Logger&>::type operator<<(const T in)
{
	if (Manager::instance().Config->debug == true)
	{
		std::string instring = (std::string)in;
		m_InternalBuffer.append(instring);
		try {
			if (m_InternalBuffer.substr(m_InternalBuffer.size() - 1) == "\n")
			{
				m_Log(m_InternalBuffer);
				Manager::instance().m_display->WriteCurrentEvent(m_InternalBuffer);
				m_InternalBuffer.clear();
			}
		}
		catch (std::out_of_range& e)
		{
			std::cerr << e.what();
			//Do nuffin
		}
	}
	return *this;
}
template <typename T>
inline typename std::enable_if<std::is_integral<T>::value, Logger&>::type operator<<(const T in)
{
	Logger::operator<< (std::to_string(in));
	return *this;
}
/////////////////////////////////
*/

void Logger::Logger::m_Log(std::string in)
{
	if (!m_file.is_open())
	{
		m_file.open(m_logname);
	}
	if (m_file.is_open())
	{
		m_file << in;
		m_file.flush();
	}
	else
	{
		std::cerr << "Error saving the file.";
		std::cerr << strerror(errno);
	}
}

//Logger::Logger::operator internal::Liner() const { return {}; }
Logger::Logger &Logger::log = Logger::Logger::instance();

void Logger::Logger::SetLog()
{
	if (m_file.is_open())
	{
		m_file.close();
	}
	auto now = std::chrono::system_clock::now();
	std::time_t start_time = std::chrono::system_clock::to_time_t(now);
	std::stringstream tempstrs;
	char timedisplay[256];
	auto tm = localtime(&start_time);
	if (std::strftime(timedisplay, sizeof(timedisplay), "%F_%H.%M.%S", tm))
	{
		tempstrs << timedisplay;
	}

	m_logname = "Log_" + tempstrs.str() + ".txt";

}



Logger::Logger::Logger()
{
}

Logger::Logger::~Logger()
{
	if (m_file.is_open())
	{
		m_file.close();
	}
}
