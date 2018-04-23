//Joel Akers && Tucker Rhodes

//GATE.CPP

#include "gate.h"
#include "wire.h"
#include <string>
using namespace std;



Gate::Gate(Wire * input1Temp, Wire * outputTemp, Wire * input2Temp, int typeIntTemp, int delayNumTemp)
{
	input1 = input1Temp;
	output = outputTemp;
	input2 = input2Temp;
	type = typeIntTemp;
	delay = delayNumTemp;
}

void Gate::SetGateType(string gateType) {
	if (gateType == "AND") {
		type = 0;
	}
	else if (gateType == "NAND") {
		type = 2;
	}
	else if (gateType == "OR") {
		type = 3;
	}
	else if (gateType == "NOR") {
		type = 4;
	}
	else if (gateType == "XOR") {
		type = 5;
	}
	else if (gateType == "XNOR") {
		type = 6;
	}
	else if (gateType == "NOT") {
		type = 7;
	}
}

int Gate::GetDelay() {
	return delay;
}

Wire* Gate::GetInput1() {
	return input1;
}

Wire* Gate::GetInput2() {
	return input2;
}

Wire* Gate::GetOutput() {
	return output;
}

//
bool Gate::ApplyType() {

	switch (type) {
	case 0://AND

		if (output->GetValue() == '1') {
			if (input1->GetValue() == '1' && input2->GetValue() == '1') {
				return false;
			}
			else {
				return true;
			}
		}
		else if (output->GetValue() == '0'){
			if (input1->GetValue() == '1' && input2->GetValue() == '1') {
				return true;
			}
			else {
				return false;
			}
		}
		else {//value was 'X'
			return true;
		}
		break;

	case 1://NAND
		if (output->GetValue() == '1') {
			if (input1->GetValue() == '1' && input2->GetValue() == '1') {
				return true;
			}
			else {
				return false;
			}
		}
		else if (output->GetValue() == '0') {
			if (input1->GetValue() == '1' && input2->GetValue() == '1') {
				return false;
			}
			else {
				return true;
			}
		}
		else {
			return true;
		}
		break;

	case 2://OR
		if (output->GetValue() == '1') {
			if (input1->GetValue() == '1' || input2->GetValue() == '1') {
				return false;
			}
			else {
				return true;
			}
		}
		else if (output->GetValue() == '0') {
			if (input1->GetValue() == '1' || input2->GetValue() == '1') {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return true;
		}

		break;

	case 3://NOR
		if (output->GetValue() == '1') {
			if (input1->GetValue() == '1' || input2->GetValue() == '1') {
				return true;
			}
			else {
				return false;
			}
		}
		else if (output->GetValue() == '0') {
			if (input1->GetValue() == '1' || input2->GetValue() == '1') {
				return false;
			}
			else {
				return true;
			}
		}
		else {
			return true;
		}

		break;

	case 4://XOR
		if (output->GetValue() == '1') {
			if (input1->GetValue() == input2->GetValue()) {
				return true;
			}
			else {
				return false;
			}
		}
		else if (output->GetValue() == '0') {
			if (input1->GetValue() == input2->GetValue()) {
				return false;
			}
			else {
				return true;
			}
		}
		else {
			return true;
		}

		break;

	case 5://XNOR
		if (output->GetValue() == '1') {
			if (input1->GetValue() == input2->GetValue()) {
				return false;
			}
			else {
				return true;
			}
		}
		else if (output->GetValue() == '0') {
			if (input1->GetValue() == input2->GetValue()) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return true;
		}
		break;

	case 6://NOT
		return true;
		break; 

	default: return false;
	}
}

Wire * Gate::findWireForGate(vector<Wire*> wires, int wireNum)
{
	for (int i = 0; i < wires.size(); i++) {
		if (wires[i]->GetWireNumber() == wireNum) {
			return wires[i];
		}
	}
	return NULL;
}

char Gate::GetWireNewValue() {

	switch (type) {
	case 0://AND
		if (input1->GetValue() == '1' && input2->GetValue() == '1') {
			return '1';
		}
		else {
			return '0';
		}
		break;
	case 1://NAND
		if (input1->GetValue() == '1' && input2->GetValue() == '1') {
			return '0';
		}
		else {
			return '1';
		}
		break;
	case 2://OR
		if (input1->GetValue() == '1' || input2->GetValue() == '1') {
			return '1';
		}
		else {
			return '0';
		}
		break;
	case 3://NOR
		if (input1->GetValue() == '1' || input2->GetValue() == '1') {
			return '0';
		}
		else {
			return '1';
		}
		break;
	case 4://XOR
		if (input1->GetValue() == input2->GetValue()) {
			return '0';
		}
		else {
			return '1';
		}
		break;
	case 5://XNOR
		if (input1->GetValue() == input2->GetValue()) {
			return '1';
		}
		else {
			return '0';
		}
		break;
	case 6://NOT
		if (input1->GetValue() == '1') {
			return '0';
		}
		else {
			return '1';
		}
		break;
	default: break;
	}
}