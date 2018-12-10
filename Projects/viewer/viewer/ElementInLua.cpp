#include "Header.h"

void myWindow::AddTransistor(string name, string drain, string gate, string source, string substrate, string type) {
	Transistor *tr = new Transistor;
	
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
	transistors.push_back(tr);
}

Gate * myWindow::AddGate(string name, GateType type) {
	Gate *gate = new Gate;
	

	gate->name = name;
	gate->type = type;

	switch (type) {
		case gt_invertor:
			gate->pinsIn.resize(1);
			gate->pinsIn[0] = NULL;
			gate->pinsOut.resize(1);
			gate->pinsOut[0] = NULL;
			break;
		case gt_nand2:
			gate->pinsIn.resize(2);
			gate->pinsIn[0] = NULL;
			gate->pinsIn[1] = NULL;
			gate->pinsOut.resize(1);
			gate->pinsOut[0] = NULL;
			break;
		case gt_nor2:
			gate->pinsIn.resize(2);
			gate->pinsIn[0] = NULL;
			gate->pinsIn[1] = NULL;
			gate->pinsOut.resize(1);
			gate->pinsOut[0] = NULL;
			break;
	}
	gates.push_back(gate);
	return gate;
}

int myWindow::ElementInLua(string pathFile)
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	luaL_dofile(L, "resolver2.lua");
	luaL_openlibs(L);
	lua_pcall(L, 0, 0, 0);

	LuaRef Elements = getGlobal(L, "elements");
	LuaRef t = Elements(pathFile);
	LuaRef count = t["count"];
	string TransistorCount = count["transistors"].cast<string>();
	string InventorCount = count["invertors"].cast<string>();
	string Nand2Count = count["nand2"].cast<string>();
	string Nor2Count = count["nor2"].cast<string>();
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
			string drain = current["drain"].cast<string>();
			string gate = current["gate"].cast<string>();
			string substrate = current["substrate"].cast<string>();
			string type = current["type"].cast<string>();
			AddTransistor(name, drain, gate, source, substrate, type);
		}
	}
	if (!invertors.isNil()) {
		int count_inv = invertors.length();
		cout << "Invertors: " << count_inv << endl;
		for (int i = 1; i <= count_inv; i++) {
			if (invertors[i].isNil()) continue;
			LuaRef current = invertors[i];
			LuaRef items = current["items"];
			string name = current["name"].cast<string>();
			string in = current["inA"].cast<string>();
			string out = current["out"].cast<string>();
			string vdd = current["vdd"].cast<string>();
			string vss = current["vss"].cast<string>();
			Gate *gate = AddGate(name, gt_invertor);
			for (int n = 1; n <= items.length(); n++) {
				for (int j = 0; j < transistors.size(); j++) {
					if (transistors[j]->name == items[n].cast<string>())
						gate->CompositionGate.push_back(transistors[j]);
				}
			}
			for (int i = 0; i < nets.size(); i++) {
				if (nets[i]->name == in) {
					gate->pinsIn[0] = nets[i];
					nets[i]->connection.push_back(gate);
				}
			}
			if (gate->pinsIn[0] == NULL) {
				Net *net = new Net;
				net->name = in;
				nets.push_back(net);
				gate->pinsIn[0] = net;
				nets[i]->connection.push_back(gate);
			}
			for (int i = 0; i < nets.size(); i++) {
				if (nets[i]->name == out) {
					gate->pinsOut[0] = nets[i];
					nets[i]->connection.push_back(gate);
				}
			}
			if (gate->pinsOut[0] == NULL) {
				Net *net = new Net;
				net->name = out;
				nets.push_back(net);
				gate->pinsOut[0] = net;
				nets[i]->connection.push_back(gate);
			}
			for (int i = 0; i < nets.size(); i++) {
				if (nets[i]->name == vss) {
					gate->vss = nets[i];
					nets[i]->connection.push_back(gate);
				}
			}
			if (gate->vss == NULL) {
				Net *net = new Net;
				net->name = vss;
				nets.push_back(net);
				gate->vss = net;
				nets[i]->connection.push_back(gate);
			}
			for (int i = 0; i < nets.size(); i++) {
				if (nets[i]->name == vdd) {
					gate->vdd = nets[i];
					nets[i]->connection.push_back(gate);
				}
			}
			if (gate->vdd == NULL) {
				Net *net = new Net;
				net->name = vdd;
				nets.push_back(net);
				gate->vdd = net;
				nets[i]->connection.push_back(gate);
			}
		}
	}
	if (!nand2.isNil()) {
		int count_nand = nand2.length();
		cout << "Nand: " << count_nand << endl;
		for (int i = 1; i <= count_nand; i++) {
			LuaRef current = nand2[i];
			LuaRef items = current["items"];
			string name = current["name"].cast<string>();
			string inA = current["inA"].cast<string>();
			string inB = current["inB"].cast<string>();
			string out = current["out"].cast<string>();
			string vdd = current["vdd"].cast<string>();
			string vss = current["vss"].cast<string>();
			Gate *gate = AddGate(name, gt_nand2);
			for (int n = 1; n <= items.length(); n++) {
				for (int j = 0; j < transistors.size(); j++) {
					if (transistors[j]->name == items[n].cast<string>())
						gate->CompositionGate.push_back(transistors[j]);
				}
			}
			for (int i = 0; i < nets.size(); i++) {
				if (nets[i]->name == inA) {
					gate->pinsIn[0] = nets[i];
					nets[i]->connection.push_back(gate);
				}
			}
			if (gate->pinsIn[0] == NULL) {
				Net *net = new Net;
				net->name = inA;
				nets.push_back(net);
				gate->pinsIn[0] = net;
				nets[i]->connection.push_back(gate);
			}
			for (int i = 0; i < nets.size(); i++) {
				if (nets[i]->name == inB) {
					gate->pinsIn[1] = nets[i];
					nets[i]->connection.push_back(gate);
				}
			}
			if (gate->pinsIn[1] == NULL) {
				Net *net = new Net;
				net->name = inB;
				nets.push_back(net);
				gate->pinsIn[1] = net;
				nets[i]->connection.push_back(gate);
			}
			for (int i = 0; i < nets.size(); i++) {
				if (nets[i]->name == out) {
					gate->pinsOut[0] = nets[i];
					nets[i]->connection.push_back(gate);
				}
			}
			if (gate->pinsOut[0] == NULL) {
				Net *net = new Net;
				net->name = out;
				nets.push_back(net);
				gate->pinsOut[0] = net;
				nets[i]->connection.push_back(gate);
			}
			for (int i = 0; i < nets.size(); i++) {
				if (nets[i]->name == vss) {
					gate->vss = nets[i];
					nets[i]->connection.push_back(gate);
				}
			}
			if (gate->vss == NULL) {
				Net *net = new Net;
				net->name = vss;
				nets.push_back(net);
				gate->vss = net;
				nets[i]->connection.push_back(gate);
			}
			for (int i = 0; i < nets.size(); i++) {
				if (nets[i]->name == vdd) {
					gate->vdd = nets[i];
					nets[i]->connection.push_back(gate);
				}
			}
			if (gate->vdd == NULL) {
				Net *net = new Net;
				net->name = vdd;
				nets.push_back(net);
				gate->vdd = net;
				nets[i]->connection.push_back(gate);
			}
		}
	}
	if (!nor2.isNil()) {
		int count_nor = nor2.length();
		cout << "Nor2: " << count_nor << endl;
		for (int i = 1; i <= count_nor; i++) {
			LuaRef current = nor2[i];
			LuaRef items = current["items"];
			string name = current["name"].cast<string>();
			string inA = current["inA"].cast<string>();
			string inB = current["inB"].cast<string>();
			string out = current["out"].cast<string>();
			string vdd = current["vdd"].cast<string>();
			string vss = current["vss"].cast<string>();
			Gate *gate = AddGate(name, gt_nor2);
			for (int n = 1; n <= items.length(); n++) {
				for (int j = 0; j < transistors.size(); j++) {
					if (transistors[j]->name == items[n].cast<string>())
						gate->CompositionGate.push_back(transistors[j]);
				}
			}
			for (int i = 0; i < nets.size(); i++) {
				if (nets[i]->name == inA) {
					gate->pinsIn[0] = nets[i];
					nets[i]->connection.push_back(gate);
				}
			}
			if (gate->pinsIn[0] == NULL) {
				Net *net = new Net;
				net->name = inA;
				nets.push_back(net);
				gate->pinsIn[0] = net;
				nets[i]->connection.push_back(gate);
			}
			for (int i = 0; i < nets.size(); i++) {
				if (nets[i]->name == inB) {
					gate->pinsIn[1] = nets[i];
					nets[i]->connection.push_back(gate);
				}
			}
			if (gate->pinsIn[1] == NULL) {
				Net *net = new Net;
				net->name = inB;
				nets.push_back(net);
				gate->pinsIn[1] = net;
				nets[i]->connection.push_back(gate);
			}
			for (int i = 0; i < nets.size(); i++) {
				if (nets[i]->name == out) {
					gate->pinsOut[0] = nets[i];
					nets[i]->connection.push_back(gate);
				}
			}
			if (gate->pinsOut[0] == NULL) {
				Net *net = new Net;
				net->name = out;
				nets.push_back(net);
				gate->pinsOut[0] = net;
				nets[i]->connection.push_back(gate);
			}
			for (int i = 0; i < nets.size(); i++) {
				if (nets[i]->name == vss) {
					gate->vss = nets[i];
					nets[i]->connection.push_back(gate);
				}
			}
			if (gate->vss == NULL) {
				Net *net = new Net;
				net->name = vss;
				nets.push_back(net);
				gate->vss = net;
				nets[i]->connection.push_back(gate);
			}
			for (int i = 0; i < nets.size(); i++) {
				if (nets[i]->name == vdd) {
					gate->vdd = nets[i];
					nets[i]->connection.push_back(gate);
				}
			}
			if (gate->vdd == NULL) {
				Net *net = new Net;
				net->name = vdd;
				nets.push_back(net);
				gate->vdd = net;
				nets[i]->connection.push_back(gate);
			}
		}
	}

	return 0;
}

int myWindow::locationGate() {
	int numOfMinusOnes = gates.size();
	vector<vector<int>> levels;
	int pos = -1;
	vector<int> out = FindOutElement();
	for (int i = 0; i < out.size(); i++) {
		gates[out[i]]->location.pos_v = i;
	}
	levels.push_back(out);
	numOfMinusOnes = numOfMinusOnes - out.size();

	while (1) {
		if (numOfMinusOnes == 0) break;
		levels.push_back(FindNetsElement(levels[levels.size() - 1], numOfMinusOnes));

	}
	verticalLayout(levels);
	scaleElements(levels);
	return 0;
	/*
	while (1) {
		int size = 0;
		for (int i = 0; i < levels.size(); i++) {
			size = size + levels[i].size();
		}
		cout << "SIIIIZE" << size<<endl;
		if (size == gates.size()) break;
		levels.push_back(FindNetsElement(levels[levels.size()-1]));
		
	}
	for (int i = 0; i < levels.size(); i++) {
		cout << "level " << i<<":"<<endl;
		for (int j = 0; j < levels[i].size(); j++) {
			cout << levels[i][j] << " ";
		}
		cout << endl;
	}
	scaleElements(levels);
	return 0;*/
}


void myWindow::verticalLayout(vector<vector<int>>  levels) {
	for (int i = 1; i < levels.size(); i++) {
		for (int j = 0; j < levels[i].size(); j++) {
		//	gates[levels[i][j]]->location
		}
	}

}
void myWindow::scaleElements(vector<vector<int>>  levels) {
	for (int i = 0; i < levels.size(); i++) {
		int size1 = levels[i].size();
		for (int j = 0; j < levels[i].size(); j++) {
			int size = levels[i].size();
			gates[levels[i][j]]->location.x = x_cord - 90 * (i+1);
			gates[levels[i][j]]->location.y = (((double)(j+1) / (double)(size+1)) * y_cord) - side/2;
		}
	}
	
}
vector<int> myWindow::FindNetsElement(vector<int>  chekLevel, int &numOfMinusOnes) {
	int newRank = gates[chekLevel[0]]->location.pos_h + 1;
	vector<int> level;
	for (int k = 0; k < chekLevel.size(); k++) {
		for (int i = 0; i < gates.size(); i++) {
			if (gates[i]->location.pos_h != -1) continue;
			for (int j = 0; j < gates[chekLevel[k]]->pinsIn.size(); j++) {
				for (int n = 0; n < gates[i]->pinsOut.size(); n++) {
					if (gates[chekLevel[k]]->pinsIn[j] == gates[i]->pinsOut[n]) {
						// ������� gates[i] ����� �� ����� � �������� gates[chekLevel[k]]
						// ����� �����, ������ � ������ ��������
						//*
						for (int g = 0; g < gates[i]->pinsIn.size(); g++) {
							for (int c = 0; c < gates[i]->pinsIn[g]->connection.size(); c++) {
								if (gates[i] == gates[i]->pinsIn[g]->connection[c])	continue;
								if (gates[i]->pinsIn[g]->connection[c]->location.pos_h < newRank)	continue;
								if (gates[i]->pinsIn[g]->connection[c]->location.pos_h == newRank) {
									for (int p = 0; p < gates[i]->pinsIn[g]->connection[c]->pinsIn.size(); p++) {
										if (gates[i]->pinsIn[g] == gates[i]->pinsIn[g]->connection[c]->pinsIn[p])
											goto N;
									}
									for (int l = 0; l < level.size(); l++)
										if (gates[level[l]]->name == gates[i]->pinsIn[g]->connection[c]->name)
											level.erase(level.begin() + l);
									gates[i]->pinsIn[g]->connection[c]->location.pos_h = -1;
									numOfMinusOnes = numOfMinusOnes + 1;
								N:;
								}
							}
						}
						// ������ �����, ������ �� �������� ��������
						for (int g = 0; g < gates[i]->pinsOut.size(); g++) {
							for (int c = 0; c < gates[i]->pinsOut[g]->connection.size(); c++) {
								if (gates[i] == gates[i]->pinsOut[g]->connection[c])	continue;
								if (gates[i]->pinsOut[g]->connection[c]->location.pos_h == -1) goto M;
								if (gates[i]->pinsOut[g]->connection[c]->location.pos_h < newRank)	continue;
								if (gates[i]->pinsOut[g]->connection[c]->location.pos_h == newRank) {
									for (int p = 0; p < gates[i]->pinsOut[g]->connection[c]->pinsIn.size(); p++) {
										//if (gates[i]->pinsIn[p]->connection[c]->location.pos < newRank)	continue;
										if (gates[i]->pinsOut[g]->connection[c]->pinsIn[p] == gates[i]->pinsOut[g])
											goto M;
									}
									//gates[i]->pinsOut[g]->connection[c]->location.pos = -1;
									//numOfMinusOnes = numOfMinusOnes + 1;
								}
							}
						}
						//*/

						level.push_back(i);
						gates[i]->location.pos_h = newRank;
						numOfMinusOnes = numOfMinusOnes - 1;
					}
				M:;
				}
			}
		}
	}
	return level;
}


vector<int> myWindow::FindOutElement(){
	vector<int> outIndex;
	for (int i = 0; i < gates.size(); i++) {
		for (int j = 0; j < gates[i]->pinsOut.size(); j++) {
			bool out;
			for (int k = 0; k < gates.size(); k++) {
				out = true;
				if (i == k) continue;
				for (int n = 0; n < gates[k]->pinsIn.size(); n++) {
					if (gates[i]->pinsOut[j] == gates[k]->pinsIn[n]) {
						out = false;
						break;
					}
				}
				if (out == false)  break;
			}
			if (out == true) {
				gates[i]->location.pos_h = 0;
				cout << "FindOut " << gates[i]->name << endl;
				outIndex.push_back(i);
			}
		}
	}

	return outIndex;
}
/*
1. ���������� �� ��� ������� ������, ��������� ��  ���������!
2. �������� ��������� � ��������

*/