#pragma once
#include <iostream>
#include <cstring>
using namespace std;

template<class T, class N>
class Prim {
private:
	int num;
	T** net;
	T* lowcost;
	bool* visit;
	int* parent;
	N* index;
	int findIndex(N x);
public:
	Prim(int sz=4);
	~Prim() { makeEmpty(); }
	void init(const int& num);
	bool nodeInput();
	bool input();
	int minCost();
	bool createTree(N start);
	void printTree();
	void makeEmpty();
};

template<class T, class N>
inline int Prim<T, N>::findIndex(N x)
{
	for (int i = 0; i < num; i++) {
		if (index[i] == x)return i;
	}
	return -1;
}

template<class T, class N>
inline Prim<T, N>::Prim(int sz) :num(sz)
{
	net = new int* [num];
	for (int i = 0; i < num; i++) {
		net[i] = new int[num]();
	}
	lowcost = new T[num];
	visit = new bool[num];
	parent = new int[num];
	index = new char[num];
	for (int i = 0; i < num; i++) {
		lowcost[i] = INT_MAX;
		visit[i] = false;
		parent[i] = -1;
		index[i] = '0';
	}
}

template<class T, class N>
inline void Prim<T, N>::init(const int &num)
{
	net = new int* [num];
	for (int i = 0; i < num; i++) {
		net[i] = new int[num]();
	}
	lowcost = new T[num];
	visit = new bool[num];
	parent = new int[num];
	index = new char[num];
	for (int i = 0; i < num; i++) {
		lowcost[i] = INT_MAX;
		visit[i] = false;
		parent[i] = -1;
		index[i] = '#';
	}
}

template<class T, class N>
inline bool Prim<T, N>::nodeInput()
{
	cout << "请依次输入各顶点的名称：" << endl;
	for (int i = 0; i < num; i++) {
		cin >> index[i];
		if (cin.fail())return false;
	}
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	return true;
}

template<class T, class N>
inline bool Prim<T, N>::input()
{
	N leftN, rightN;
	T len;
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			net[i][j] = 0;
		}
	}
	while (true) {
		cout << "请输入两个顶点及边：";
		cin >> leftN >> rightN >> len;
		if (leftN == '?' || rightN == '?' || len == 0) {
			break;
		}
		int leftNode = findIndex(leftN);
		int rightNode = findIndex(rightN);
		if (cin.fail() || leftNode == -1 || rightNode == -1)
			return false;
		net[leftNode][rightNode] = len;
		net[rightNode][leftNode] = len;
	}
	return true;
}

template<class T, class N>
inline int Prim<T, N>::minCost()
{
	int min = INT_MAX, min_index = 0;
	for (int i = 0; i < num; i++) {
		if (visit[i] == false && lowcost[i] < min) {
			min = lowcost[i];
			min_index = i;
		}
	}
	return min_index;
}

template<class T, class N>
inline bool Prim<T, N>::createTree(N start)
{
	for (int i = 0; i < num; i++) {
		lowcost[i] = INT_MAX;
		visit[i] = false;
		parent[i] = -1;
	}
	if (findIndex(start) == -1)return false;
	lowcost[findIndex(start)] = 0;
	parent[findIndex(start)] = -1;
	for (int i = 0; i < num - 1; i++) {
		int u = minCost();
		visit[u] = true;
		for (int v = 0; v < num; v++) {
			if (net[u][v] != 0 && visit[v] == false && net[u][v] < lowcost[v]) {
				parent[v] = u;
				lowcost[v] = net[u][v];
			}
		}
	}
	return true;
}

template<class T, class N>
inline void Prim<T, N>::printTree()
{
	cout << "最小生成树的顶点及边为：" << endl;
	for (int i = 0; i < num; i++) {
		if (parent[i] != -1) {
			cout << index[parent[i]];
			cout << "-<" << net[i][parent[i]] << ">->";
			cout << index[i] << endl;
		}
	}
}

template<class T, class N>
inline void Prim<T, N>::makeEmpty()
{
	for (int i = 0; i < num; i++) {
		delete[]net[i];
	}
	delete[]net;
	delete[]lowcost;
	delete[]visit;
	delete[]parent;
	delete[]index;
}
