#pragma once
#include "Console.h"

#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include <memory>
#include "Manager.h"


LinuxShell::LinuxShell()
{
	State = std::make_unique<SplashState>();
}

void LinuxShell::Display(bool fast)
{
	std::cout << "Linux";
}



void Console::WriteOut(std::string in)
{
	std::cout << in;
}

void Console::Input()	//this part could be improved!
{
	WriteOut(this->State->DisplayText());
	Console::WriteOut("	Input your command: ");
	std::string input;
	std::getline(std::cin, input);
	Manager::instance().FireCommand(input);
}

void Console::WriteCurrentEvent(std::string in)
{
}

void Console::ProgressStar()
{
}



Console::Console()
{
}

Console::~Console()
{
}

SplashState::SplashState()
{
}

SplashState::~SplashState()
{
}

IConsoleState::IConsoleState()
{
}

IConsoleState::~IConsoleState()
{
}
