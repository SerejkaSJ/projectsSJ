#include "stdafx.h"
#include <iostream>
#include <lua.hpp>
#include <LuaBridge.h>
#include <vector> 

#pragma comment(lib, "lua53.lib") 

using namespace std;
using namespace luabridge;
class Net {
public:
	string name;
};

enum TransistorType{

	tt_p = 1,
	tt_n = 0,
};

class Transistor {
public:
	Net *gate;
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

vector<Transistor*> transistors;
vector<Net*> nets;

void AddTransistor(string name, string drain, string gate, string source, string substrate, string type) {
	Transistor *tr = new Transistor;
	transistors.push_back(tr);
	tr->name = name;
	if (type == "N") 
		tr->type = tt_n;
	else 
		tr->type = tt_p;

	for (int i = 0; i < nets.size(); i++) {
		if (nets[i]->name == drain) {
			tr->drain = nets[i];
		}
	}
	if (tr->drain == NULL) {
		Net *net = new Net;
		net->name = drain;
		nets.push_back(net);
		tr->drain = net;
	}
	for (int i = 0; i < nets.size(); i++) {
		if (nets[i]->name == gate) {
			tr->gate = nets[i];
		}
	}
	if (tr->gate == NULL) {
		Net *net = new Net;
		net->name = gate;
		nets.push_back(net);
		tr->gate = net;
	}

	for (int i = 0; i < nets.size(); i++) {
		if (nets[i]->name == source) {
			tr->source = nets[i];
		}
	}
	if (tr->source == NULL) {
		Net *net = new Net;
		net->name = source;
		nets.push_back(net);
		tr->source = net;
	}

	for (int i = 0; i < nets.size(); i++) {
		if (nets[i]->name == substrate) {
			tr->bulk = nets[i];
		}
	}
	if (tr->bulk == NULL) {
		Net *net = new Net;
		net->name = substrate;
		nets.push_back(net);
		tr->bulk = net;
	}


}

int main()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	luaL_dofile(L, "resolver.lua");
	luaL_openlibs(L);
	lua_pcall(L, 0, 0, 0);

	LuaRef t = getGlobal(L, "Elements");
	LuaRef transistorsLua = t["transistors"];
	LuaRef invertors = t["invertors"];
	LuaRef nand2 = t["nand2"];
	LuaRef nor2 = t["nor2"];
	if (!transistorsLua.isNil()) {
		int count_tran = transistorsLua.length();
		cout << "Transistors: " << count_tran << endl;
		for (int i = 1; i <= count_tran; i++) {
			LuaRef current = transistorsLua[i];
			string name = current["name"].cast<string>();
			string source = current["source"].cast<string>();
			string drain = current["sink"].cast<string>();
			string gate = current["gate"].cast<string>();
			string substrate = current["substrate"].cast<string>();
			string type = current["type"].cast<string>();
			AddTransistor(name, drain, gate, source, substrate, type);
		}
	}
	for (int i = 0; i < transistors.size(); ++i)
	{
		cout << "Name: " << transistors[i]->name << endl;
		cout << "source: " << transistors[i]->source->name << endl;
		cout << "drain: " << transistors[i]->drain->name << endl;
		cout << "gate: " << transistors[i]->gate->name << endl;
		cout << "substrate: " << transistors[i]->bulk->name << endl;
		cout << "type: " << transistors[i]->type << endl;
	}
	/*if (!invertors.isNil()) {
		int count_inv = invertors.length();
		cout << "Invertors: " << count_inv << endl;
		for (int i = 1; i <= count_inv; i++) {
			LuaRef current = invertors[i];
			string name = current["name"].cast<string>();
			string in = current["inA"].cast<string>();
			string out = current["out"].cast<string>();
			string vdd = current["vdd"].cast<string>();
			string vss = current["vss"].cast<string>();
		
			//удалить
			cout << endl << "Invertors: " << i << endl;
			cout << "Name: " << name << endl;
			cout << "Vdd: " << vdd << endl;
			cout << "In: " << in << endl;
			cout << "Out: " << out << endl;
			cout << "Vss: " << vss << endl;
		}
	}
	if (!nand2.isNil()) {
		int count_nand = nand2.length();
		cout << "Nand: " << count_nand << endl;
		for (int i = 1; i <= count_nand; i++) {
			LuaRef current = nand2[i];
			string name = current["name"].cast<string>();
			string inA = current["inA"].cast<string>();
			string inB = current["inB"].cast<string>();
			string out = current["out"].cast<string>();
			string vdd = current["vdd"].cast<string>();
			string vss = current["vss"].cast<string>();
		//
			//удалить
			cout << endl << "Nand2: " << i << endl;
			cout << "Name: " << name << endl;
			cout << "Vdd: " << vdd << endl;
			cout << "InA: " << inA << endl;
			cout << "InB: " << inB << endl;
			cout << "Out: " << out << endl;
			cout << "Vss: " << vss << endl;
		}
	}
	if (!nand2.isNil()) {
		int count_nor = nor2.length();
		cout << "Nor2: " << count_nor << endl;
		for (int i = 1; i <= count_nor; i++) {
			LuaRef current = nor2[i];
			string name = current["name"].cast<string>();
			string inA = current["inA"].cast<string>();
			string inB = current["inB"].cast<string>();
			string out = current["out"].cast<string>();
			string vdd = current["vdd"].cast<string>();
			string vss = current["vss"].cast<string>();

			//удалить
			cout << endl << "Nor2: " << i << endl;
			cout << "Name: " << name << endl;
			cout << "Vdd: " << vdd << endl;
			cout << "InA: " << inA << endl;
			cout << "InB: " << inB << endl;
			cout << "Out: " << out << endl;
			cout << "Vss: " << vss << endl;
		}
	}*/

    return 0;
}

