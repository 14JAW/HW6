#pragma once
#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include "Event.h"
#include <vector>

using namespace std;

class Queue {
public:
	//constructor
	Queue(vector<Event> queueOfEvents);

private:
	vector<Event> queue;
};

#endif QUEUE_H