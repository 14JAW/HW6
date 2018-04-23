//Joel Akers && Tucker Rhodes

#include "wire.h"

Wire::Wire(vector<char> historyTemp, vector<Gate*> gatesTemp, int wireNumberTemp, string nameTemp, char valueTemp)
{
	history = historyTemp;
	driver = gatesTemp;
	wireNumber = wireNumberTemp;
	name = nameTemp;
	value = valueTemp;

}

void Wire::SetValue(char valueInt) {
	value = valueInt;
	SetHistoryAt(history.size() + 1, valueInt);
}

void Wire::SetHistoryAt(int time, char highLow) {
	if (time > history.size() + 1) {
		history.resize(time + 1);
	}
	history.at(time + 1) = highLow;
}

void Wire::SetDriverAt(Gate* g) {
	Gate* gatePtr = g;
	driver.resize(driver.size() + 1);

	driver.at(driver.size()) = gatePtr;
}

void Wire::SetWireNumber(int wireNum)
{
	wireNumber = wireNum;
}

string Wire::GetName() {
	return name;
}

char Wire::GetValue() {
	return value;
}

Gate * Wire::GetDriverAt(int index)
{
	return nullptr;
}

int Wire::GetWireNumber()
{
	return wireNumber;
}

