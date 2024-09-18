#include <iostream>//无符号版本
#include <string>
#include<bitset>
#include "Code.hpp"
#include "Parser.hpp"
using std::string;

class assembler {
public:
	assembler(ifstream& ifile, string iname, ofstream& ofile, string oname);
	void assemblechoose();//判断写入哪种语句
	void assemble_a();
	void assemble_c();

private:
	ifstream& ifile;
	string iname;
	ofstream& ofile;
	string oname;
	Code code;
	Parser parser;
	string command;
	string bincommand;
	c_type type=c_type::A_COMMAND;
};

assembler::assembler(ifstream& ifile, string iname, ofstream& ofile, string oname) ://初始化列表
	ifile(ifile), iname(iname), ofile(ofile), oname(oname), parser(ifile){}


void assembler::assemblechoose() {
	while (parser.hasMoreCommands())
	{
		parser.advance();
		type = parser.commandType();
			if (type == c_type::A_COMMAND)
			{
				assemble_a();
			}
			else if (type ==c_type::C_COMMAND)
			{
				assemble_c();
			}
	}

}
void assembler::assemble_a() {
	string original = parser.symbol();
	int outcommand;
	outcommand = stoi(original);
	bincommand = bitset<16>(outcommand).to_string();
	ofile << bincommand << endl;
}
void assembler::assemble_c() {
	string dest = parser.dest();
	string comp = parser.comp();
	string jump = parser.jump();
	unsigned int outcommand=0;
	outcommand |= code.dest(dest);
	outcommand |= code.comp(comp);
	outcommand |= code.jump(jump);
	outcommand |= 0b1110000000000000;

	bincommand = bitset<16>(outcommand).to_string();
	ofile << bincommand << endl;
}


