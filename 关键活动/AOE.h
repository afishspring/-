#pragma once
#include <iostream>
using namespace std;

struct ArcNode {
	ArcNode() :nextArc(NULL), _toNode(-1), _weight(-1),_id(0) {}
	ArcNode(int toNode, int weight,int id) :nextArc(NULL), _toNode(toNode), _weight(weight),_id(id) {}
	int _toNode;
	int _weight;
	int _id;
	ArcNode* nextArc;
	friend class AGraph;
};

struct VNode {
	ArcNode* first = NULL;
	friend class AGraph;
};

class AGraph {
public:
	AGraph();
	~AGraph();
	bool TopSort();
	void CriticalPath();
	//���ڵ���
	//void print() {
	//	cout << endl << "order:" << endl;
	//	for (int i = 0; i < _nNode; i++) {
	//		cout << order[i] << " ";
	//	}
	//	cout << endl << "ve:" << endl;
	//	for (int i = 0; i < _nNode; i++) {
	//		cout << ve[i] << " ";
	//	}
	//	cout << endl << "vl:" << endl;
	//	for (int i = 0; i < _nNode; i++) {
	//		cout << vl[i] << " ";
	//	}
	//	cout << endl << "e:" << endl;
	//	for (int i = 0; i < _nEvent; i++) {
	//		cout << e[i] << " ";
	//	}
	//	cout << endl << "l:" << endl;
	//	for (int i = 0; i < _nEvent; i++) {
	//		cout << l[i] << " ";
	//	}
	//}
private:
	VNode* net;
	int* order, * inDegree;
	int* ve, * vl, *e, *l;
	int* edgeInfo;
	int _nEvent;
	int _nNode;
};

AGraph::AGraph()
{
	int nNode, nEvent;
	int from, to, weight;
	while (true) {
		cin >> nNode;
		if (cin.fail() || nNode <= 0 || nNode > 100) {
			cerr << "���񽻽ӵ�N����������������룡" << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			continue;
		}
		cin >> nEvent;
		if (cin.fail() || nEvent <= 0 || nEvent > nNode * (nNode - 1) / 2) {
			cerr << "��������M����������������룡" << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			continue;
		}
		break;
	}
	_nNode = nNode;
	_nEvent = nEvent;
	net = new VNode[nNode];
	order = new int[nNode] {};
	inDegree = new int[nNode] {};
	ve = new int[nNode] {};
	vl = new int[nNode] {};
	e = new int[_nEvent] {};
	l = new int[_nEvent] {};
	edgeInfo = new int[_nEvent] {};

	while (true) {
		bool flag = true;
		for (int i = 0; i < _nEvent; i++) {
			cin >> from >> to >> weight;
			if (cin.fail() || from<1 || from>_nNode || to<1 || to>_nNode || weight < 0) {
				cerr << "������Ϣ����������������룡" << endl;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				flag = false;
			}
			if (!flag)break;
			from -= 1;
			to -= 1;
			ArcNode* arc = new ArcNode(to, weight, i);
			arc->nextArc = net[from].first;
			net[from].first = arc;
			inDegree[to]++;
			edgeInfo[i] = from * 1000 + to;
		}
		if (!flag)continue;
		break;
	}
}

AGraph::~AGraph()
{
	for (int i = 0; i < _nNode; i++) {
		ArcNode* p = net[i].first;
		while (p != NULL) {
			net[i].first = p->nextArc;
			delete p;
			p = net[i].first;
		}
	}
	delete[]net;
	delete[]order;
	delete[]inDegree;
	delete[]ve;
	delete[]vl;
	delete[]e;
	delete[]l;
}

bool AGraph::TopSort()
{
	int top = -1, count = 0;
	for (int i = 0; i < _nNode; i++)
		if (inDegree[i] == 0) {
			inDegree[i] = top;
			top = i;
		}
	for (int i = 0; i < _nNode; i++) {
		if (top == -1) {
			cerr << "0" << endl;
			return false;
		}
		else {
			int temp = top;
			top = inDegree[top];
			order[count++] = temp;
			ArcNode* edge = net[temp].first;
			while (edge!=NULL) {
				int k = edge->_toNode;
				if ((--inDegree[k]) == 0) {
					inDegree[k] = top;
					top = k;
				}
				if (ve[temp] + edge->_weight > ve[k])
					ve[k] = ve[temp] + edge->_weight;
				edge = edge->nextArc;
			}
		}
	}
	return true;

}

void AGraph::CriticalPath()
{
	int top = _nNode - 1;
	int v = order[top--];
	vl[v] = ve[v];
	while (top != -1) {
		v= order[top--];
		ArcNode* p = net[v].first;
		vl[v] = vl[p->_toNode];
		while (p != NULL) {
			if (vl[p->_toNode] - p->_weight < vl[v])
				vl[v] = vl[p->_toNode] - p->_weight;
			p = p->nextArc;
		}
	}

	for (int i = 0; i < _nNode; i++) {
		ArcNode* p = net[i].first;
		while (p != NULL) {
			e[p->_id] = ve[i];
			l[p->_id] = vl[p->_toNode] - p->_weight;
			p = p->nextArc;
		}
	}

	cout << ve[_nNode - 1] << endl;
	for (int i = 0; i < _nEvent; i++) {
		if (e[i] == l[i]) {
			cout << edgeInfo[i] / 1000+1 << "->" << edgeInfo[i] % 1000 +1<< endl;
		}
	}
}