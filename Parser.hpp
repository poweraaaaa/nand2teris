#pragma once
#include <iostream>
#include <string>
#include <cctype>
using namespace std;
enum class c_type {
	A_COMMAND,
	C_COMMAND,
	L_COMMAND,
	Z_COMMAND//代表这一行是注释或是空白行
};
class Parser 
{
public:

	Parser(istream& input):linepos(0),input(input){}

	bool hasMoreCommands();//基本函数
	void advance();
	c_type commandType();
	string symbol();
	string dest();
	string comp();
	string jump();

private:
	istream& input;
	std::string::iterator it;
	c_type type = c_type::A_COMMAND;
	int linepos;
	bool nextline();
	string command,line;
};



bool Parser::nextline() {
	if (getline(input,line))//读取输入文件，放入line中
	{

		linepos++;
		it = line.begin();//it是迭代器，逐字读取
		return true;
	}
	return false;
}

bool Parser::hasMoreCommands() {
	return nextline();
}

void Parser::advance() {
		command.clear();
		type = c_type::Z_COMMAND;//标志检查空白字符问题
		while (it != line.end()) {

			if (*it == '/' && *(it + 1) == '/' && (it + 1) != line.end())
			{
				type = c_type::Z_COMMAND;
				break;
			}
			else if (*it != ' ')
			{
				type = c_type::A_COMMAND;
				command.append(1, *it);
			}
			it++;
		}
}

c_type Parser::commandType() {//判断命令类型
	if (type==c_type::Z_COMMAND)
	{
		type = c_type::A_COMMAND;//重置一下
		return c_type::Z_COMMAND;
	}
	else if (command.front() == '@')
	{
		return c_type::A_COMMAND;
	}
	else if (command.front()=='(')
	{
		return c_type::L_COMMAND;
	}
	
	else {
		return c_type::C_COMMAND;
	}
}

string Parser::symbol() {//切分symbol
	if (commandType() == c_type::A_COMMAND)
	{
		return command.substr(1);
	}
	else
		return command.substr(1, command.size() - 2);
}

string Parser::dest() {//筛选d区
	if (command.find('=')!=std::string::npos)
	{
		return command.substr(0, command.find('='));
	}
	return "";
}

string Parser::comp() {//筛选c区

	if (command.find('=')==std::string::npos)//无dest区
	{
		return command.substr(0, command.find(';'));
	}
	if (command.find(';') == std::string::npos)//无jmp区
	{
		return command.substr(command.find('=')+1);
	}
	return command.substr(command.find('=') + 1, command.find(';'));
}

string Parser::jump() {
	if (command.find(';') != std::string::npos)
	{
		return command.substr(command.find(';') + 1);
	}
	return "";
}