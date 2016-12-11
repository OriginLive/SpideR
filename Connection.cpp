#include "Connection.h"
#include <exception>


Connection::Connection(const std::string& other_url, std::stringstream& stream)
	: url(other_url), streamhandle(stream)
{
	try
	{
		resolve_connection();
	}
	catch (cURLpp::RuntimeError& e)
	{
		std::cerr << e.what() << '\n';
	}
	catch (cURLpp::LogicError& e)
	{
		std::cerr << e.what() << '\n';
	}
}

void Connection::resolve_connection()
{
	cURLpp::Easy socket;
	cURLpp::options::WriteStream write(&streamhandle);
	socket.setOpt(write);
	if (Manager::instance().Config->debug)
	{
		socket.setOpt(new cURLpp::options::Verbose(true));
	}
	socket.setOpt(new cURLpp::options::FollowLocation(true));
	socket.setOpt(cURLpp::options::Url(url)); 
	socket.perform();
}

