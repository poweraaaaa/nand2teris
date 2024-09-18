#pragma once
#include <iostream>
#include <algorithm>
#include <string>

class Code 
{
public:
	unsigned int dest(std::string command);
	unsigned int comp(std::string command);
	unsigned int jump(std::string command);


};

unsigned int Code::dest(std::string command) {
	unsigned short int d_code=0;
	if (command.find('A') != std::string::npos)
	{
		d_code = d_code | 0b100;
	}
	if (command.find('D') != std::string::npos)
	{
		d_code = d_code | 0B010;
	}
	if (command.find('M')!=std::string::npos)
	{
		d_code = d_code | 0b001;
	}
	return d_code << 3;
}
unsigned int Code::comp(std::string command) {
	unsigned short int mand = 0;
	unsigned short int c_code=0;
	if (command.find('M')!=std::string::npos)
	{
		mand|= 0b1000000;
		std::replace(command.begin(), command.end(), 'M', 'A');
	}

	if (command == "0")
		c_code = 0b101010;
	else if (command == "1")
		c_code = 0b111111;
	else if (command == "-1")
		c_code = 0b111010;
	else if (command == "D")
		c_code = 0b001100;
	else if (command == "A")
		c_code = 0b110000;
	else if (command == "!D")
		c_code = 0b001101;
	else if (command == "!A")
		c_code = 0b110001;
	else if (command == "-D")
		c_code = 0b001111;
	else if (command == "-A")
		c_code = 0b110011;
	else if (command == "D+1")
		c_code = 0b011111;
	else if (command == "A+1")
		c_code = 0b110111;
	else if (command == "D-1")
		c_code = 0b001110;
	else if (command == "A-1")
		c_code = 0b110010;
	else if (command == "D+A")
		c_code = 0b000010;
	else if (command == "D-A")
		c_code = 0b010011;
	else if (command == "A-D")
		c_code = 0b000111;
	else if (command == "D&A")
		c_code = 0b000000;
	else
		c_code = 0b010101;

	return (c_code|=mand) << 6;
}

unsigned int Code::jump(std::string command) {

	if (command == "JGT")
		return 0b001;
	if (command == "JEQ")
		return 0b010;
	if (command == "JGE")
		return 0b011;
	if (command == "JLT")
		return 0b100;
	if (command == "JNE")
		return 0b101;
	if (command == "JLE")
		return 0b110;
	if (command == "JMP")
		return 0b111;

	return 0;  // null case
}
