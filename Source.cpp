#include "Factory.h"
#include <map>
#include <string>
#include <functional>
#include "Manager.h"
#include "ConnectionManager.h"
#include <utility>

Factory* factory = nullptr;
bool IsRunning = true;
Console* display = nullptr;


int main() {

#ifdef _WIN32
	factory = new WindowsFactory;
#elif defined __linux__
	factory = new LinuxFactory;
#endif
	Manager::instance().ReadConfig();

	display = factory->create_context();
	display->Display();

	Manager::instance().RegisterCommand("help", [=](void*) { display->State = std::make_unique<HelpState>(); });
	Manager::instance().RegisterCommand("connect", [=](void* in) { ConnectionManager cm( *(static_cast<std::string*>(in)) ); });
	//Manager::instance().RegisterCommand("quit", [=](
	//Manager::instance().RegisterCommand("err", [=](std::string err) { display->WriteOut(err); });

	while (IsRunning)
	{
		display->Input();
		//main loop2

	}
}
