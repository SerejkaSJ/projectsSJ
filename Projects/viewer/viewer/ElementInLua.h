#pragma once

#include <iostream>
#include <vector>
using namespace std;

enum TransistorType {

	tt_p = 1,
	tt_n = 0,
};


enum GateType {

	gt_invertor = 1,
	gt_nand2 = 2,
	gt_nor2 = 3,

};
struct  Location
{
	double x;
	double y;
	int pos_h = -1;
	int pos_v = -1;
};

class Gate;
class Net {
public:
	string name;
	vector<Gate*> connection;
};


class Transistor {
public:
	Net * gate;
	Net *source;
	Net *drain;
	Net *bulk;
	string name;
	TransistorType type;
	Transistor() {
		gate = NULL;
		source = NULL;
		drain = NULL;
		bulk = NULL;
	}
};
class Gate {
public:
	string name;
	vector<Transistor*> CompositionGate;
	vector<Net*> pinsIn;
	vector<Net*> pinsOut;
	Net* vss;
	Net* vdd;
	GateType type;
	Location location;
};