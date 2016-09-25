#pragma once
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