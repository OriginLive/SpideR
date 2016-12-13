#pragma once
#include "Console.h"

#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include <memory>
#include "Manager.h"


const std::string SplashText
{
"	SpideR, 1.0 (Freeware)\n"
"	Made with care, 2016 by Origin\n"
"	(SpideR) Web spider crawler made to gather words and sort them\n"
"	Its modular design (will) allow it to include AI to learn and comprehend sentences\n\n"
"	Type \"help\" for a list of commands\n"
};

const std::string HelpText
{

"	Commands:\n"
"	\"help\" - This screen.\n"
"	\"connect website\" - Connect to given website and crawl it based on settings.\n"
"	\"quit\" - Exit program.\n"
"	\n"
};


LinuxShell::LinuxShell()
{
	State = std::make_unique<SplashState>();
}

void LinuxShell::Display()
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



std::string SplashState::DisplayText()
{
	return SplashText;
}

std::string HelpState::DisplayText()
{
	return HelpText;
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
