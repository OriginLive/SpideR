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
#include <future>
#include <thread>

#include "Manager.h"
#include "Queen.h"

bool is_running = true;
namespace py = pybind11;


int main()
{

#ifdef _WIN32
	std::unique_ptr<WindowsFactory> factory = std::make_unique<WindowsFactory>();
#elif defined __linux__
	std::unique_ptr<LinuxFactory> factory = std::make_unique<LinuxFactory>();
#endif

	std::ofstream out("err.txt"); // Error output
	std::cerr.rdbuf(out.rdbuf()); // Redirecting it to err.txt

	//Py_Initialize();
	//py::object scope = py::module::import("__main__").attr("__dict__");
	//py::eval_file("script.py", scope);

	cURLpp::Cleanup cleanupmanager; // Automatically release network resources upon exit
	Manager::instance().ReadConfig();
	std::shared_ptr<Console> display(std::move(factory->create_context()));
	Manager::instance().SetDisplay(display);
	display->Display();

	Manager::instance().RegisterCommand("help", [&](void*) { display->State = std::make_unique<HelpState>(); });
	Manager::instance().RegisterCommand("connect", [=](void* in) { Queen q( *(static_cast<std::string*>(in)) ); });
	Manager::instance().RegisterCommand("quit", [&](void*) {is_running = false;}); 

	std::thread t1([]() {Manager::instance().CheckProgress(); });
	

	while (is_running)
	{
		display->Input();
	}
	return 0;
}
