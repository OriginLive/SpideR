#pragma once
#ifndef CONSOLE_H
#define CONSOLE_H
#include <string>
#include <memory>



class IConsoleState
{
public:
	virtual std::string DisplayText() = 0;
	virtual int InputLine() = 0;
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
	int InputLine() { return 7; };
	std::string SplashState::DisplayText()
	{

	return  std::string("	SpideR, 1.0 (Freeware)\n") +
			std::string("	Made with care, 2016 by Origin with a lot of contrubiton by Tor\n") +
			std::string("	(SpideR) Web spider crawler made to gather words and sort them\n") +
			std::string("	It's modular design allows it to include AI to lean and comprehend sentences\n\n") +
			std::string("	Type \"help\" for a list of commands\n");
	}
};

class HelpState : public IConsoleState
{
public:
	//std::string DisplayText();
	std::string Action() { return ""; };
	int InputLine() { return 7; };
	std::string HelpState::DisplayText()
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
	virtual void Display() = 0;
	void WriteOut(std::string in);
	void Input();
	void WriteCurrentEvent(std::string in);

	std::unique_ptr<IConsoleState> State;

};

class WindowsConsole : public Console
{
public:
	void Display();
};

class LinuxShell : public Console
{
public:
	LinuxShell();
	void Display();
};





#endif // !CONSOLE_H
