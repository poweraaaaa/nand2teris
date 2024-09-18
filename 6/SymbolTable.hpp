#pragma once
#include<iostream>
#include <unordered_map>
#include <string>
using std::string;

class SymbolTable {
public:
	void Constructor();
	void addEntry(string symbol, int address);
	void base();
	bool contains(string symbol);
	int GetAddress(string symbol);
	std::unordered_map<string, int> labels;
};

void SymbolTable::Constructor() {
	std::unordered_map<string, int> labels;
	base();//≥ı ºªØ
}
void SymbolTable::base() {


	labels["SP"] = 0;
	labels["LCL"] = 1;
	labels["ARG"] = 2;
	labels["THIS"] = 3;
	labels["THAT"] = 4;
	for (int i= 0; i < 16; ++i) {
		labels["R" + std::to_string(i)] = i;
	}
	labels["SCREEN"] = 16384; // 0x4000
	labels["KDB"] = 24576; // 0x6000
}

void  SymbolTable::addEntry(string symbol, int address) {

	labels[symbol] = address;
}

bool SymbolTable::contains(string symbol) {
	if (labels.find(symbol) == labels.end())
	{
		return false;
	}
	else
		return true;
}

int SymbolTable::GetAddress(string symbol) {

	return labels[symbol];
}