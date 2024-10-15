#pragma once
#include<iostream>
#include <string>
#include<fstream>
#include "Parser.hpp"
using std::string;

class codewriter {
public:
	codewriter(ofstream& ofile) :
		ofile(ofile) {};
	void setFileName(string filename);
	void writeArthmelt(string command);
	void WritePushPop(VMtype type, string segment, int index);

private:
	void write(string outcommand);
	string changeseg(string segment,int index);
	void w_eq();
	void w_gt();
	void w_lt();
	string oname;
	ofstream& ofile;
	int jumpcount = 0;
};

void codewriter::writeArthmelt(string command) {
	if (command == "add")
	{
		write("@SP");
		write("AM=M-1");
		write("D=M");
		write("A=A-1");
		write("M=M+D");
	}
	else if (command == "sub")
	{
		write("@SP");
		write("AM=M-1");
		write("D=M");
		write("A=A-1");
		write("M=M-D");
	}
	else if (command == "neg")
	{
		write("@SP");
		write("A=M-1");
		write("M=-M");
	}
	else if (command == "eq")
	{
		w_eq();
	}
	else if (command == "gt")
	{
		w_gt();
	}
	else if (command == "lt")
	{
		w_lt();
	}
	else if (command == "and")
	{
		write("@SP");
		write("AM=M-1");
		write("D=M");
		write("A=A-1");
		write("M=D&M");
	}
	else if (command == "or")
	{
		write("@SP");
		write("AM=M-1");
		write("D=M");
		write("A=A-1");
		write("M=D|M");
	}
	else if (command == "not")
	{
		write("@SP");
		write("A=M-1");
		write("M=!M");
	}
}

string codewriter::changeseg(string segment,int index) {

	if (segment == "constant")
	{
		return "SP";
	}
	else if (segment == "local")
	{
		return "LCL";
	}
	else if (segment == "argument")
	{
		return "ARG";
	}
	else if (segment == "this")
	{
		return "THIS";
	}
	else if (segment=="that")
	{
		return "THAT";
	}
	else if (segment=="temp")
	{
		return "R" + to_string(index + 5);
	}
	else if (segment == "pointer")
	{
		return "R" + to_string(index + 3);
	}
	else
	{
		return "R"+to_string(index+16);
	}
}


void codewriter::WritePushPop(VMtype type, string segment, int index) {
	string seg = changeseg(segment,index);
	if (type == VMtype::C_PUSH)
	{
		if (segment=="constant")
		{
			write("@"+to_string(index) + " // push " + segment + " " + to_string(index));
			write("D=A");
			write("@SP");
			write("A=M");
			write("M=D");
			write("@SP");
			write("M=M+1");
		}
		else if (segment == "temp" || segment == "pointer"||segment=="static")
		{
			write("@" + seg + " // push " + segment + " " + to_string(index));
			write("D=M");
			write("@SP");
			write("A=M");
			write("M=D");
			write("@SP");
			write("M=M+1");
		}
		else
		{
			write("@" + to_string(index)+" // push " + segment + " " + to_string(index));
			write("D=A");
			write("@" + seg);
			write("A=M+D");
			write("D=M");
			write("@SP");
			write("A=M");
			write("M=D");
			write("@SP");
			write("M=M+1");
		}
		
	}
	else if (type == VMtype::C_POP) {
		if (segment == "constant")
		{
			write("@SP// pop " + segment + " " + to_string(index));
			write("AM=M-1");
			write("D=M");
			write("@" + to_string(index));
			write("M=D");
		}
		else if (segment=="temp"||segment=="pointer" || segment == "static")
		{
			write("@SP// pop " + segment + " " + to_string(index));
			write("AM=M-1");
			write("D=M");
			write("@" + seg);
			write("M=D");
		}
		else {
			write("@"+to_string(index) + " // pop " + segment + " " + to_string(index));
			write("D=A");
			write("@"+seg);
			write("D=M+D");
			write("@R13");
			write("M=D");
			write("@SP");
			write("AM=M-1");
			write("D=M");
			write("@R13");	
			write("A=M");
			write("M=D");
		}
	}
}

void codewriter::w_eq() {
	string lable("EQ" + oname + to_string(jumpcount));//添加跳转标签
	write("@SP");
	write("AM=M-1");
	write("D=M");
	write("A=A-1");
	write("D=M-D");
	write("@" + lable);
	write("D;JEQ");
	write("D=1");//=0
	write("(" + lable + ")");
	write("D=D-1");
	write("@SP");
	write("A=M-1");
	write("M=D");
	jumpcount++;
}
void codewriter::w_gt() {//x>y
	string lable("GT" + oname + to_string(jumpcount));//添加跳转标签
	write("@SP");
	write("AM=M-1");
	write("D=M");
	write("A=A-1");
	write("D=M-D");
	write("@" + lable+"ok");
	write("D;JGT");
	write("D=0");
	write("@" + lable + "no");
	write("D;JEQ");
	write("(" + lable +"ok"+ ")");
	write("D=-1");
	write("(" + lable  + "no"+ ")");
	write("@SP");
	write("A=M-1");
	write("M=D");
	jumpcount++;
}

void codewriter::w_lt() {//x<y
	string lable("LT" + oname + to_string(jumpcount));//添加跳转标签
	write("@SP");
	write("AM=M-1");
	write("D=M");
	write("A=A-1");
	write("D=M-D");
	write("M=-1");
	write("@" + lable + "ok");
	write("D;JLT");
	write("D=0");
	write("@" + lable + "no");
	write("D;JEQ");
	write("(" + lable  + "ok"+ ")");
	write("D=-1");
	write("(" + lable  + "no"+")");
	write("@SP");
	write("A=M-1");
	write("M=D");
	jumpcount++;
}


void codewriter::write(string outcommand) {

	ofile << outcommand << endl;
}

void codewriter::setFileName(string filename) {

	cout << filename << "The new VM file translation process has started." << endl;
}