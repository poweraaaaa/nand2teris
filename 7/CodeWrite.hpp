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

void codewriter::WritePushPop(VMtype type, string segment, int index) {
	if (type == VMtype::C_PUSH)
	{
		write("@" + to_string(index));
		write("D=A");
		write("@SP");
		write("A=M");
		write("M=D");
		write("@SP");
		write("M=M+1");
	}
	else if (type == VMtype::C_POP) {
		write("@SP");
		write("AM=M-1");
		write("D=M");
		write("@" + to_string(index));
		write("M=D");
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