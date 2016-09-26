#pragma once
#ifndef CONSOLE_H
#define CONSOLE_H


#include <string>
class Console
{
public:
	virtual void Display() = 0;
	void WriteOut(std::string in);
	void Input();
};

class WindowsConsole : public Console
{
public:
	void Display();
};

class LinuxShell : public Console
{
public:
	void Display();
};

#endif // !CONSOLE_H