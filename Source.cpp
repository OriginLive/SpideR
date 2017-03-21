#define NOMINMAX
#include <curlpp/cURLpp.hpp>
#include "Factory.h"
#include <memory>
#include <map>
#include <string>
#include <functional>
#include <utility>
#include <pybind11/eval.h>
#include <Python.h>

#include "Manager.h"
#include "Queen.h"

bool IsRunning = true;
namespace py = pybind11;


int main()
{

#ifdef _WIN32
	std::unique_ptr<WindowsFactory> factory = std::make_unique<WindowsFactory>();
#elif defined __linux__
	std::unique_ptr<LinuxFactory> factory = std::make_unique<LinuxFactory>();
#endif

	Logger l;
	l.Log("test");

	//Py_Initialize();
	//py::object scope = py::module::import("__main__").attr("__dict__");
	//py::eval_file("script.py", scope);

	cURLpp::Cleanup cleanupmanager; // Automatically release network resources upon exit
	Manager::instance().ReadConfig();
	std::unique_ptr<Console> display(std::move(factory->create_context()));
	display->Display();

	Manager::instance().RegisterCommand("help", [&](void*) { display->State = std::make_unique<HelpState>(); });
	Manager::instance().RegisterCommand("connect", [=](void* in) { Queen q( *(static_cast<std::string*>(in)) ); });
	Manager::instance().RegisterCommand("quit", [&](void*) {IsRunning = false;}); 

	while (IsRunning)
	{
		display->Input();
	}
	return 0;
}
