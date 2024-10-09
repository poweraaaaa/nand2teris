#pragma once
#include<iostream>
#include <string>
#include<fstream>
using namespace std;

enum class VMtype
{
	C_ARITHMETIC, /**< Arithmetic command. */
	C_PUSH,       /**< Push command. */
	C_POP,        /**< Pop command. */
	C_LABEL,      /**< Label command. */
	C_GOTO,       /**< Goto command. */
	C_IF,         /**< If Goto command. */
	C_FUNCTION,   /**< Function command. */
	C_RETURN,     /**< Return command. */
	C_CALL        /**< Call command. */
};

class parser {
public:
	parser(ifstream& input) :inputfile (input),marker(0){};
	bool hasMoreCommands();
	bool advance();
	VMtype commandType();
	string arg1();
	int Arg2();

private:
	ifstream& inputfile;
	string::iterator it;
	string line;
	string command,com1;
	bool empty_f = false;
	int marker;
};

bool parser::hasMoreCommands() {
	if (getline(inputfile, line))
	{
		it = line.begin();
		return true;
	}
	return false;
}

bool parser::advance() {
	command.clear();
	if (parser::line.empty())//È¥µô¿Õ°×ÐÐ
	{
		return false;
	}
	else
	{
		while (it!=line.end())
		{
			if (*it=='/'&&*(it+1)=='/')//È¥µô×¢ÊÍ
			{
				return false;
			}
			command.append(1,*it);
			it++;
		}
		return true;
	}
}

VMtype parser::commandType() {
	if (command.find("pop")!=std::string::npos)
	{
		return VMtype::C_POP;
	}
	else if (command.find("push")!=std::string::npos)
	{
		return VMtype::C_PUSH;
	}
	return VMtype::C_ARITHMETIC;
}

string parser::arg1() {
	if (commandType()==VMtype::C_ARITHMETIC)
	{
		return command;
	}
	else
	{
		return command.substr(0, command.find(' '));
	}
}

int parser::Arg2() {
	com1 = command.substr(command.find(' ') + 1);
	return stoi(com1.substr(com1.find(' ') + 1));
}

