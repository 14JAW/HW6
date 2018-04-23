//Joel Akers && Tucker Rhodes

//EVENT.CPP

#include "Event.h"

Event::Event(Wire * wire, int timeVal, char valueChar, int countVal)
{
	w = wire;
	time = timeVal;
	value = valueChar;
	count = countVal;
}

void Event::SetWire(Wire * wire)
{
	w = wire;
}

void Event::SetTime(int timeVal)
{
	time = timeVal;
}

void Event::SetValue(char valueChar)
{
	value = valueChar;
}

void Event::SetCount(int countVal)
{
	count = countVal;
}

Wire * Event::GetWire()
{
	return w;
}

int Event::GetTime()
{
	return time;
}

char Event::GetValue()
{
	return value;
}

int Event::GetCount()
{
	return count;
}
