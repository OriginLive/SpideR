#pragma once
#include "Console.h"

#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include <memory>
#include "Manager.h"


int splashSize = 5;
std::string input;

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


IConsoleState::IConsoleState()
{
}

IConsoleState::~IConsoleState()
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

std::string SplashState::DisplayText() {

	return  std::string("	SpideR, 1.0 (Freeware)\n") +
		std::string("	Made with care, 2016 by Origin\n") +
		std::string("	(SpideR) Web spider crawler made to gather words and sort them\n") +
		std::string("	Its modular design (will) allow it to include AI to learn and comprehend sentences\n\n") +
		std::string("	Type \"help\" for a list of commands\n");
}

std::string HelpState::DisplayText() {

	return  std::string("	Commands:\n") +
		std::string("	\"help\" - This screen.\n") +
		std::string("	\"connect website\" - Connect to given website and crawl it based on settings.\n") +
		std::string("	\"quit\" - Exit program.\n") +
		std::string("	\n");
}
