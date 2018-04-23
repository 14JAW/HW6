//Joel Akers && Tucker Rhodes

//EVENT.H

#pragma once
#ifndef EVENT_H
#define EVENT_H
#include <iostream>
#include "wire.h"
#include "gate.h"

using namespace std;

class Event {
public:
	//constructor
	Event(Wire* wire, int timeVal, char valueChar, int countVal);

	//Mutators
	void SetWire(Wire* wire);
	void SetTime(int timeVal);
	void SetValue(char valueChar);
	void SetCount(int countVal);

	//Accessors
	Wire* GetWire();
	int GetTime();
	char GetValue();
	int GetCount();

//private:
	Wire* w;
	int time;
	char value;
	int count;
};
#endif EVENT_H