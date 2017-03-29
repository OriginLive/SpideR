#pragma once
#ifndef CONSOLE_H
#define CONSOLE_H
#include <string>
#include <memory>
#include <atomic>



class IConsoleState
{
public:
	virtual std::string DisplayText() = 0;
	virtual int InputLine() = 0;
	virtual int ProgressLine() = 0;
	virtual std::string Action() = 0;
	IConsoleState();
	virtual ~IConsoleState();
};

class SplashState : public IConsoleState
{
public:
	SplashState();
	~SplashState();
	//std::string DisplayText();
	std::string Action() { return ""; };
	int InputLine() { return 9; };
	int ProgressLine() { return 7; };
	std::string DisplayText()
	{

	return  std::string("	SpideR, 1.0 (Freeware)\n") +
			std::string("	Made with care, 2016 by Origin with a lot of contrubiton by Tor\n") +
			std::string("	(SpideR) Web spider crawler made to gather words and sort them\n") +
			std::string("	Its modular design allows it to include AI to learn and comprehend sentences\n\n") +
			std::string("	Type \"help\" for a list of commands\n");
	}
};

class HelpState : public IConsoleState
{
public:
	//std::string DisplayText();
	std::string Action() { return ""; };
	int InputLine() { return 9; };
	int ProgressLine() { return 7; };
	std::string DisplayText()
	{

	return  std::string("	This is a sample help page.\n\n") +
			std::string("	Use the command \"Connect\" to connect to a website\n") +
			std::string("	Example: Connect www.google.com\n") +
			std::string("	The above command would output google's http page\n") +
			std::string("	\n");
	}
};

//
// CONSOLE BELOW
//

class Console
{
public:
	Console();
	virtual ~Console();
	virtual void Display(bool fast = false) = 0;
	virtual void WriteOut(std::string in);
	void Input();
	void WriteCurrentEvent(std::string in);
	void ProgressStar();

	std::unique_ptr<IConsoleState> State;
	std::atomic<bool> progress;
	std::string LastEvent = "\t\t\t\t\t\t\t";

};

class WindowsConsole : public Console
{
public:
	void Display(bool fast = false);
};

class LinuxShell : public Console
{
public:
	LinuxShell();
	void Display(bool fast = false);
};





#endif // !CONSOLE_H
