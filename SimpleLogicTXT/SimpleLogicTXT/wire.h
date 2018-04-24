//Joel Akers && Tucker Rhodes

#pragma once
#ifndef WIRE_H
#define WIRE_H

#include <iostream>
#include "gate.h"

using namespace std;
class Gate;

class Wire {
public:
	//constructor, copy constructor, assignment operator, destructor
	Wire(vector<char> history, vector<Gate*> gates, int wireNumber, string name = "", char value = '\0');

	//Mutator
	//void SetName(string nameString);
	void SetValue(char valueInt);
	void SetHistoryAt(int time = 0, char highLow = 'X');
	void SetDriverAt(Gate* g);
	void SetWireNumber(int wireNum);

	//Accessor
	string GetName();
	char GetValue();
	Gate* GetDriverAt(int index = 0);
	int GetWireNumber();

//private:
	string name;
	int wireNumber;
	char value;
	vector<char> history;
	vector<Gate*> driver;
};
#endif WIRE_H