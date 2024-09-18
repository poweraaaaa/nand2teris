#pragma once
#include <iostream>//有符号版本
#include <string>
#include<bitset>
#include "Code.hpp"
#include "Parser.hpp"
#include"SymbolTable.hpp"
using std::string;

class signed_assemble {
public:
	signed_assemble( ifstream & ifile,string iname,ofstream & ofile,string oname );
	void first_assemble();
	void second_assemble();
	void c_assemble();
	void a_assemble();

private:
	Code code;
	Parser parser;
	SymbolTable symboltable;
	int RAM = 16;
	ifstream& ifile;
	ofstream& ofile;
	string iname, oname,symbol,command;
	c_type type = c_type::A_COMMAND;
	int lines = 0;//记录地址
};

signed_assemble::signed_assemble(ifstream& ifile, string iname, ofstream& ofile, string oname) :
	ifile(ifile), iname(iname), ofile(ofile), oname(oname), parser(ifile) {};

void signed_assemble::first_assemble() {
	lines = 0;
	symboltable.Constructor();
	while (parser.hasMoreCommands())
	{
		
		parser.advance();
		type = parser.commandType();
		if (type==c_type::L_COMMAND)
		{
			symbol = parser.symbol();
			symboltable.addEntry(symbol, lines);
		}
		else if (type==c_type::Z_COMMAND)
		{
		}
		else
		{
			lines++;
		}
	}
	ifile.clear();
	ifile.seekg(0, std::ios::beg);
}

void signed_assemble::second_assemble() {
	while (parser.hasMoreCommands())
	{
		parser.advance();
		type = parser.commandType();
		if (type==c_type::A_COMMAND)
		{
			a_assemble();
		}
		else if (type==c_type::C_COMMAND)
		{
			c_assemble();
		}
	}
}
void signed_assemble::a_assemble() 
{
	string bincommand;
	int outcommand=0;
	symbol = parser.symbol();
	if (symboltable.contains(symbol))//符号表有的就是int
	{
		outcommand = symboltable.GetAddress(symbol);
	}
	else if(isdigit(symbol.front()))//符号表无的就是string
	{
		outcommand = stoi(symbol);
	}
	else
	{
		symboltable.addEntry(symbol, RAM);
		outcommand = RAM;
		RAM++;
	}
	bincommand = bitset<16>(outcommand).to_string();
	ofile << bincommand << endl;
}

void signed_assemble::c_assemble() {
	string dest = parser.dest();
	string comp = parser.comp();
	string jump = parser.jump();
	string bincommand;
	unsigned int outcommand = 0b1110000000000000;
	outcommand |= code.dest(dest);
	outcommand |= code.comp(comp);
	outcommand |= code.jump(jump);
	bincommand = bitset<16>(outcommand).to_string();
	
	ofile << bincommand << endl;
}