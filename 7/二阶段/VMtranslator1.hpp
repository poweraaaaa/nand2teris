#pragma once
#include "Parser.hpp"
#include "CodeWrite.hpp"
#include<string.h>
using std::string;

class translator {
public:
	translator(ifstream& ifile, string iname, ofstream& ofile, string oname) :
		ifile(ifile), iname(iname), ofile(ofile), oname(oname), parser(ifile) ,codewrite(ofile){};
	void trans();

private:
	parser parser;
	codewriter codewrite;
	ifstream& ifile;
	ofstream& ofile;
	string iname, oname,command,segment;
	int index=0;
};

void translator::trans() {
	while (parser.hasMoreCommands())
	{
		if (parser.advance())
		{	
			if (parser.commandType()==VMtype::C_ARITHMETIC)
			{
				command = parser.arg1();
				codewrite.writeArthmelt(command);
			}
			else
			{
				index = parser.Arg2();
				segment = parser.ARG1();
				codewrite.WritePushPop(parser.commandType(),segment, index);
			}
		}
	}
}