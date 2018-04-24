//Joel Akers && Tucker Rhodes

#include "wire.h"
#include "gate.h"
#include <vector>
#include <fstream>
#include <queue>
#include <stdio.h>
//#include <string>
using namespace std;
class JoelError {};

class ParseError : JoelError {
public:
private:
	int errorCode;
	string message;
};

struct Event {
	Wire* wire;
	int time;
	char value;
	int delay;

	Event(Wire* w, int timeVal, char valueChar, int delayVal = 0) {
		wire = w;
		time = timeVal;
		value = valueChar;//Value of output wire
		delay = delayVal;//Delay time for gate if there is a gate
	}

	bool operator <(const struct Event& e) const {
		return time < e.time;
	}

	//Check if event changes any gate's outputs
	bool gateOutChanged() {
		bool outDidChange = false;
		for (int i = 0; i < wire->driver.size(); i++) {
			Gate* g = wire->driver[i];
			if (g->ApplyType()) {
				return true;
			}
		}
		return false;
	}
};


typedef priority_queue<Event> Queue;

Wire * findWire(vector<Wire*> wires, int wireNum)
{
	for (int i = 0; i < wires.size(); i++) {
		if (wires[i]->GetWireNumber() == wireNum) {
			return wires[i];
		}
	}
	return NULL;
}
Wire * findWire(vector<Wire*> wires, string wireName)
{
	for (int i = 0; i < wires.size(); i++) {
		if (wires[i]->GetName() == wireName) {
			return wires[i];
		}
	}
	return NULL;
}

bool Repeat() {
	//option to go again
	cout << "\nWould you like to try again? (y/n) ";
	char answer;
	cin >> answer;
	if (answer != 'y' && answer != 'Y') {
		return false;
	}
	else {
		return true;
	}
}

void PrintWire(Wire* w) {

	int sizeOfHistory = 0;
	if (w->history.size() <= 60) {
		sizeOfHistory = w->history.size();
	}
	else {
		sizeOfHistory = 60;
	}

	cout << w->name << ": ";

	for (int i = 0; i < sizeOfHistory; i++) {
		if (w->history[i] == '1') {
			cout << "-";
		}
		else if (w->history[i] == '0') {
			cout << "_";
		}
		else {
			cout << "X";
		}

	}
	cout << endl;
}

void PrintReport(vector<Wire*> wires) {
	int displayTime = 0;
	for (int i = 0; i < wires.size(); i++) {
		if (wires[i]->name != "") {
			PrintWire(wires[i]);
		}
	}
	for (int i = 0; i < displayTime; i++) {
		if (displayTime % 5 == 0) {
			cout << displayTime << "    ";
		}
	}
	cout << "pause Hit" << endl;
	char pause;
	cin >> pause;
}

void ParseInputs(string fileName, vector<Wire*>& wires, vector<Gate*>& gates, Queue& q) {

	ifstream instream;
	instream.open(fileName);

	string temp, whiteboard;
	instream >> temp;
	instream >> whiteboard;

	if (temp == "CIRCUIT") {

		while (!instream.eof()) {
			string type;
			instream >> type;

			if (type == "INPUT" || type == "OUTPUT") {

				string nameStr;
				instream >> nameStr;//Get wire name
				cout << " " << type << " " << nameStr << endl;
				int wireNum;
				instream >> wireNum;//Get Wire Number
				if (findWire(wires, nameStr) == NULL) {//Insert wire into vector
					while (wires.size() < wireNum){
						vector<char> history;
						vector<Gate*> g;
						Wire* w = new Wire(history, g, wireNum, nameStr);
						wires.push_back(w);
					}
				}
			}
			else if (type != ""){
				int delay;
				instream >> delay;
				string useless;
				instream >> useless;
				int input1 = 0;
				instream >> input1;	
				Wire* wire1 = NULL;
				if (findWire(wires, input1) == NULL) {
					while (wires.size() <= input1) {
						vector<char> history;
						vector<Gate*> g;
						Wire* w = new Wire(history, g, input1);
						wires.push_back(w);
						wire1 = w;
					}
				}
				wire1 = findWire(wires, input1);

				int input2 = -1;
				Wire* wire2 = NULL;
				if (type != "NOT") {
					instream >> input2;
					if (findWire(wires, input2) == NULL) {
						while (wires.size() <= input2) {
							vector<char> history;
							vector<Gate*> g;
							Wire* w = new Wire(history, g, input2);
							wires.push_back(w);
							wire2 = w;
						}
					}
				}
				wire2 = findWire(wires, input2);

				int output;
				instream >> output;
				Wire* wire3 = NULL;
				if (findWire(wires, output) == NULL) {
					while (wires.size() <= output) {
						vector<char> history;
						vector<Gate*> g;
						Wire* w = new Wire(history, g, output);
						wires.push_back(w);
						wire3 = w;
					}
				}
				wire3 = findWire(wires, output);

				Gate* g = new Gate(wire1, wire3, wire2);
				g->SetGateType(type);
				g->delay = delay;
				gates.push_back(g);
			}
		}
	}
	else {
		while (!instream.eof()) {
			string type;
			instream >> type;

			string name;
			instream >> name;

			int time;
			instream >> time;

			char value;
			instream >> value;

			if (findWire(wires, name) == NULL) {
				vector<char> history;
				for (int i = 0; i < time; i++) {
						history.push_back('X');
				}
				history.push_back(value);
				vector<Gate*> gates;
				int wireNumber= wires.size();
				Wire* w = new Wire(history, gates, wireNumber, name, value);
				wires.push_back(w);
				Event e(w, time, value, 0);
				q.push(e);
			}
			else {
				Wire* w = findWire(wires, name);

				int i = 0;
				char startChar = '\0';
				if (w->history.size() > 0) {
					startChar = w->history.at(w->history.size() - 1);
				}
				while (w->history.size() < time) {
					w->history.push_back(startChar);
				}
				w->history.push_back(value);
				Event e(w, time, value, 0);
				q.push(e);
			}
		}
	}
	instream.close();
}

int main() {
	bool playing = true;
	vector<Wire*> wireVector;
	vector<Gate*> gateVector;
	Queue q;
	while (playing) {

		string inputFile;
		cout << "\n\n\nWhat is the name of the circuit test file (base name only): ";

		cin >> inputFile;
		string inputFileV = inputFile + "_v.txt";
		inputFile += ".txt";

		ParseInputs(inputFile, wireVector, gateVector, q);
		ParseInputs(inputFileV, wireVector, gateVector, q);

		/*
		

		//Actual code FIXME ///////////////////////////////////////////////////////////////////////
		int timer = 0;
		Event e;
		while (timer <= 60 && !q.empty()){
			e = q.top();
			q.pop();
			Wire* w = e.wire;
			if (e.gateOutChanged()) {
				int i = 0; 
				while (i < w->driver.size()) {
					if (w->driver[i]->ApplyType()) {
						Event e1;
						e1.time = w->driver[i]->delay + timer;
						e1.wire = w->driver[i]->output;
						
						int sizer = e1.wire->history.size();
						e1.wire->history.resize(timer + 1);

						for (int j = sizer; j < timer; j++) {
							e1.wire->history[j] = e1.wire->history[sizer - 1];
						}
						e1.wire->history[timer] = w->driver[i]->GetWireNewValue();
						e1.value = e1.wire->history[timer];

						q.push(e1);
					}
				}
				//something does change so we need to 
			}
			e = q.top();
			timer = e.time;
		}
		*/
		//Actual code FIXME ///////////////////////////////////////////////////////////////////////

		//option to go again
		PrintReport(wireVector);//FIXME
		playing = Repeat();//FIXME

	}
	return 0;
}
