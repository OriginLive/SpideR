#pragma once
#ifndef FACTORY_H
#define FACTORY_H


#include "Console.h"
#include <map>
#include <string>

class Factory
{
public:
	virtual Console* create_context() = 0;
};


class WindowsFactory : public Factory
{
public:
	Console* create_context() { return new WindowsConsole; }
};

class LinuxFactory : public Factory
{
	Console* create_context() { return new LinuxShell; }
};

#endif // !FACTORY_H