#include "Factory.h"
#define Windows
#include <map>
#include <string>
#include <functional>
#include "Manager.h"
#include "Connection.h"
#include <utility>

Factory* factory = nullptr;
bool IsRunning = true;
Console* display = nullptr;


int main() {

#ifdef Windows
	factory = new WindowsFactory;
#else
	factory = new LinuxFactory;
#endif // Windows
	Manager::instance().ReadConfig();

	display = factory->create_context();
	display->Display();

	Manager::instance().RegisterCommand("help", [=](void*) { display->State = std::make_unique<HelpState>(); });
	Manager::instance().RegisterCommand("connect", [=](void* in) { ConnectionManager cm( *(static_cast<std::string*>(in)) ); });
	//Manager::instance().RegisterCommand("err", [=](std::string err) { display->WriteOut(err); });

	

	//Manager::instance().FireCommand("Help");

//	HelpCommand h(display, &Console::WriteOut, t);
//	h.execute();
//	HelpCommand();


	while (IsRunning)
	{
		display->Input();
		//main loop2

	}
}