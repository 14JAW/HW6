//Joel Akers && Tucker Rhodes

#pragma once
#ifndef GATE_H
#define GATE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;
class Wire;

class Gate {
public:
	//Constructor
	Gate(Wire* input1, Wire* output, Wire* input2 = NULL, int typeInt = 0, int delayNum = 0);

	//mutators
	void SetGateType(string gateType);

	//Accessors
	Wire* GetInput1();
	Wire* GetInput2();
	Wire* GetOutput();
	int GetDelay();
	
	//other Functions
	bool ApplyType();
	char GetWireNewValue();
	Wire* findWireForGate(vector<Wire*> wires, int wireNum);
//private:
	Wire* input1;
	Wire* input2;
	Wire* output;
	int delay;
	int type;
};
#endif