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
std::string input="";
void WindowsConsole::Display(bool fast) 
{

	State = std::make_unique<SplashState>();

	// WRITE 10 LINES, USE OF TIMING DEPENDS ON BOOL

	// 4 are text (or 5 without next empty line), lines start from 0
	// (1 newline)					 // Line 4
	// 1 help						 // Line 5
	// 1 newline					 // Line 6
	// 1 progress + rotating star	 // Line 7
	// 1 newline					 // Line 8
	// 1 input						 // Line 9

	if (fast)
	{
		system("cls");
		std::cout << State->DisplayText();
		std::cout << "\n\tProgress:	"<< LastEvent << "*\n"; //8th line
		std::cout << "\n\tInput your command: "; //10th line
		std::cout << input;
	}
	else
	{
		WriteOut(State->DisplayText());
		std::cout << "\n\tProgress:	" << LastEvent << "*\n"; //8th line
		WriteOut("\n\tInput your command: "); //10th line
	}

}

void LinuxShell::Display(bool fast)
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
	
	input += _getch();
	if (!input.empty())
	{
		_putch(input.back());
	}
	if (!input.empty())
	{

		if (input.back() == '\r')
		{
			input.pop_back();
			//input = input.substr(0, input.length() - 2);
			Manager::instance().FireCommand(input);
			input.clear();
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
				this->Display(true);
			}

		}
	}
	if (!input.empty())
	{
		if (input.back() == '\t')
		{
		input.pop_back();
		std::vector<std::string> vec = std::move(Manager::instance().ListCommands(input));
		input = vec.at(0);
		this->Display(true);

		}
	}



	std::vector<std::string> vec = std::move(Manager::instance().ListCommands(input));
	for (int i = 0; i < 5; ++i) // Write Tabs for autocomplete
	{

		COORD pos = { 28, (SHORT)this->State->InputLine() + (SHORT)i+1 }; // GO TO AUTOCOMPLETE
		HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(output, pos);
		std::cout << "\t\t";
		pos = { 28 + (SHORT)input.length() ,(SHORT)this->State->InputLine() }; // GO BACK TO INPUT
		SetConsoleCursorPosition(output, pos);
	}

	int i = 0;
	if (!vec.empty()&& !input.empty())
	{
		for (auto it = vec.begin(); it < vec.end(); ++it, ++i) // WRITE THE AUTOCOMPLETE
		{
			
			COORD pos = { 28, (SHORT)this->State->InputLine() + (SHORT)i+1 }; // GOTO AUTOCOMPLETE
			HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleCursorPosition(output, pos);
			//remember color info
			CONSOLE_SCREEN_BUFFER_INFO csbi;
			GetConsoleScreenBufferInfo(output, &csbi);

			SetConsoleTextAttribute(output, 0x08);
			Console::WriteOut(*it);

			SetConsoleTextAttribute(output, csbi.wAttributes); // restore
			pos = { 28 + (SHORT)input.length() ,(SHORT)this->State->InputLine() };	// GO BACK TO INPUT
			SetConsoleCursorPosition(output, pos);
		}
	}
	//check commands

}

void Console::WriteCurrentEvent(std::string in)
{
	LastEvent = in;
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi; // CURRENT CONSOLE INFO
	GetConsoleScreenBufferInfo(output, &csbi);


	COORD pos = { 18, (SHORT)this->State->ProgressLine() };
	SetConsoleCursorPosition(output, pos);
	std::cout << "\t\t\t\t\t\t";
	SetConsoleCursorPosition(output, pos);
	if (in.size() > 58)
	{
		in = in.substr(0, 55) + "...";
	}
	std::cout << (in);
	SetConsoleCursorPosition(output, csbi.dwCursorPosition);
}

void Console::ProgressStar()
{
	progress = true;
	static const char starsheet[] = { '\\','|','/','-' }; //Display a \ | / star
	int i = 1;
	while (Manager::instance().m_working)
	{
		HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO csbi; // CURRENT CONSOLE INFO
		GetConsoleScreenBufferInfo(output, &csbi);


		COORD pos = { 18+38+24, (SHORT)this->State->ProgressLine() };
		SetConsoleCursorPosition(output, pos);
		std::cout << (starsheet[i%4]);
		SetConsoleCursorPosition(output, csbi.dwCursorPosition);
		i++;
		if (i > 8)i = 1;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi; // CURRENT CONSOLE INFO
	GetConsoleScreenBufferInfo(output, &csbi);


	COORD pos = { 18 + 38+24, (SHORT)this->State->ProgressLine() };
	SetConsoleCursorPosition(output, pos);
	std::cout << "*";
	SetConsoleCursorPosition(output, csbi.dwCursorPosition);
	progress = false;
}

IConsoleState::IConsoleState()
{
}

IConsoleState::~IConsoleState()
{
}

Console::Console()
{
	progress = false;
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
