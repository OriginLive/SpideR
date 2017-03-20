#pragma once
#include "Console.h"

#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include <conio.h>
#include "Manager.h"


//win includes
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>

int splashSize = 5;
std::string input;
void WindowsConsole::Display() 
{
	State = std::make_unique<SplashState>();
	WriteOut(State->DisplayText());
	WriteOut("	Input your command: ");
}

void LinuxShell::Display()
{
	std::cout << "Linux";
}



void Console::WriteOut(std::string in)
{
	bool show = true;
	while (!in.empty())
	{
		if (_kbhit()) { show = false; }
			std::cout << in.front();
			if (show)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(15));
			}
			in.erase(0, 1);
	}
}

void Console::Input()	//this part could be improved!
{
	input += _getche();
	if (!input.empty())
	{

		if (input.back() == '\r')
		{
			input.pop_back();
			//input = input.substr(0, input.length() - 2);
			Manager::instance().FireCommand(input);
			input.clear(); // Press enter to return
			system("cls");
			WriteOut(this->State->DisplayText());
			Console::WriteOut("	Input your command: ");
		}
	}
	if (!input.empty())
	{
		if (input.back() == '\b')
		{
			input.pop_back();
			if (!input.empty())
			{
				input.pop_back();
			}
			system("cls");
			std::cout << this->State->DisplayText() << "	Input your command: " << input;

		}
	}



	std::vector<std::string> vec = Manager::instance().ListCommands(input);
	for (int i = 0; i < 5; ++i)
	{

		COORD pos = { 28, 7 +(SHORT) i};
		HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(output, pos);
		std::cout << "\t\t";
		pos = { 28 + (SHORT)input.length() ,6 };
		SetConsoleCursorPosition(output, pos);
	}

	int i = 0;
	if (!vec.empty()&& !input.empty())
	{
		for (auto it = vec.begin(); it < vec.end(); ++it, ++i)
		{
			
			COORD pos = { 28, (SHORT)this->State->InputLine() + (SHORT) i };
			HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleCursorPosition(output, pos);
			//remember color info
			CONSOLE_SCREEN_BUFFER_INFO csbi;
			GetConsoleScreenBufferInfo(output, &csbi);

			SetConsoleTextAttribute(output, 0x08);
			Console::WriteOut(*it);

			SetConsoleTextAttribute(output, csbi.wAttributes); // restore
			pos = { 28 + (SHORT)input.length() ,6 };
			SetConsoleCursorPosition(output, pos);
		}
	}
	//check commands

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
		std::string("	It's modular design allows it to include AI to lean and comprehend sentences\n\n") +
		std::string("	Type \"help\" for a list of commands\n");
}

std::string HelpState::DisplayText() {

	return  std::string("	This is a sample help page.\n\n") +
		std::string("	Use the command \"Connect\" to connect to a website\n") +
		std::string("	Example: Connect www.google.com\n") +
		std::string("	The above command would output google's http page\n") +
		std::string("	\n");
}
