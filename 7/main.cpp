#include <iostream>
#include "VMtranslator1.hpp"
using std::string;

string handchange(string inputname) {
	string outputname;
	if (inputname.rfind(".") != string::npos)
	{
		outputname = inputname.erase(inputname.rfind("."));
		outputname.append(".asm");
	}
	else
	{
		cout << "error:filename error" << endl;
	}
	return outputname;
}


int main() {
	string inputname;
	cin >>inputname;
	string outputname;
	outputname=handchange(inputname);
	ifstream ifile(inputname);
	if (!ifile.good())
	{
		cerr << "error: unable to open input stream" << endl;
		return 1;
	}

	ofstream ofile(outputname);
	if (!ofile.good())
	{
		cerr << "error: unable to open output stream" << endl;
		return 1;
	}

	translator VMtrans(ifile,inputname,ofile,outputname);
	VMtrans.trans();
	if (ofile.is_open())
	{
		ofile.close();
	}
	if (ifile.is_open())
	{
		ifile.close();
	}
}//D:\nand2tetris\projects\7\StackArithmetic\SimpleAdd\SimpleAdd.vm
//D:\nand2tetris\projects\7\StackArithmetic\StackTest\StackTest.vm