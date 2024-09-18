#include <iostream>//适配有符号版本
#include <string>
#include <fstream>
#include "assembler.hpp"
using std::string;

string handchange(string inputname) {
	string outputname;
	if (inputname.rfind(".")!=string::npos)
	{
		outputname = inputname.erase(inputname.rfind("."));
		outputname.append(".hack");
	}
	else
	{
		cout << "error:filename error" << endl;
	}
	return outputname;
}

int main() {

	string inputName;
	cin >> inputName;
	string outputName;
	ifstream inputfile(inputName);
	if (!inputfile.good())
	{
		cerr << "error: unable to open input stream" << endl;
		return 1;
	}
	outputName=handchange(inputName);
	ofstream outputfile(outputName);//新建prog.asm
	if (!outputfile.good())
	{
		cerr << "error: unable to open output stream" << endl;
		return 1;
	}
	signed_assemble assemble(inputfile,inputName,outputfile,outputName);
	assemble.first_assemble();
	assemble.second_assemble();

	if (outputfile.is_open())
	{
		outputfile.close();
	}
	if (inputfile.is_open())
	{
		inputfile.close();
	}
}
