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
	std::string DisplayText();
	std::string Action() { return ""; };
	int InputLine() { return 7; };
};

class HelpState : public IConsoleState
{
public:
	std::string DisplayText();;
	std::string Action() { return ""; };
	int InputLine() { return 7; };
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
