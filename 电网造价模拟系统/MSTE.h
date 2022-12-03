#pragma once
#include <iostream>
#include <cstring>
#define DefaultSz 50
using namespace std;
/************************************************************/
/* Prim�㷨                                                 */
/************************************************************/
template<class T, class N>
class Prim {
private:
	int num;			//�ڵ�����
	T** net;			//�ڽӾ���
	T* lowcost;			//�����ڵ㵽����������̾���
	bool* visit;		//��ǽڵ��Ƿ���뵽����
	int* parent;		//�洢��С������·��
	N* index;			//�洢�ڵ�����
	int findIndex(N x); //�ҵ��ڵ��Ӧ�����ֱ��
public:
	Prim(int sz=4);				//���캯��
	~Prim() { makeEmpty(); }	//��������
	void init(const int& num);	//��ʼ��˽������
	bool nodeInput();			//����ڵ�
	bool input();				//�������Ϣ
	int minCost();				//��⵱ǰ��������������Ľڵ�
	bool createTree(N start);	//������С������
	void printTree();			//��ʾ��С������
	void makeEmpty();			//���������������
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
inline void Prim<T, N>::init(const int &_num)
{
	num = _num;
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
	cout << "�������������������ƣ�" << endl;
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
	int edgeN = 0;
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			net[i][j] = 0;
		}
	}
	while (true) {
		cout << "�������������㼰�ߣ�";
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
		edgeN++;
	}
	return edgeN >= 1 ? true : false;
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
	//��ʼ��
	for (int i = 0; i < num; i++) { 
		lowcost[i] = INT_MAX;
		visit[i] = false;
		parent[i] = -1;
	}
	if (findIndex(start) == -1)return false;	//��ֹ��ʼ�㲻����
	lowcost[findIndex(start)] = 0;				//��ʼ��ֵ
	parent[findIndex(start)] = -1;
	for (int i = 0; i < num - 1; i++) {
		//��ǰ����������������СȨֵ�ıߣ��˱߲��ڶ��㼯�ϵĶ���
		int u = minCost();
		visit[u] = true;	//��Ƕ����Ѽ���������
		//lowcost���������������������б�
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
	cout << "��С�������Ķ��㼰��Ϊ��" << endl;
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

/************************************************************/
/* Kruskal�㷨----Edge�ṹ�壬���ڴ洢����Ϣ                */
/************************************************************/
template<class N>
struct Edge {
	N nodeA, nodeB;
	int cost;
	Edge():nodeA(0), nodeB(0),cost(-1) {}
	Edge(N a, N b, int len) :nodeA(a), nodeB(b), cost(len) {}
	bool operator<(const Edge& x)const {
		return this->cost < x.cost;
	}
	bool operator>(const Edge& x)const {
		return this->cost > x.cost;
	}
	bool operator<=(const Edge& x)const {
		return this->cost <= x.cost;
	}
	bool operator>=(const Edge& x)const {
		return this->cost >= x.cost;
	}
	Edge& operator =(const Edge& x) {
		this->nodeA = x.nodeA;
		this->nodeB = x.nodeB;
		this->cost = x.cost;
		return *this;
	}
	friend ostream& operator <<(ostream& os, const Edge& e) {
		os << e.nodeA << "-<" << e.cost << ">->" << e.nodeB;
		return os;
	}
	friend istream& operator >>(istream& is, Edge& e) {
		is >> e.nodeA>> e.nodeB>>e.cost;
		return is;
	}
};

/************************************************************/
/* Kruskal�㷨----С���ѣ����ڱߵ�ѡȡ                      */
/************************************************************/
template<class T>
class Heap {
public:
	Heap(int sz = DefaultSz);
	~Heap() { clear(); }
	void init(const int &num); //�����Ѵ�СΪnum
	bool push(const T& val);
	bool pop();
	T top();
	bool isEmpty()const { return currentSize == 0 ? true : false; }
	bool isFull()const { return currentSize == maxSize ? true : false; }
	void clear() { delete[]heap; currentSize = 0; maxSize = DefaultSz; }
private:
	T* heap;
	int currentSize;
	int maxSize;
	void siftDown();
	void siftUp();
};

template<class T>
inline Heap<T>::Heap(int size)
{
	maxSize = size > DefaultSz ? size : DefaultSz;
	heap = new T[maxSize];
	if (heap == NULL) {
		cerr << "�Ѵ������ʧ��" << endl;
		exit(-1);
	}
	currentSize = 0;
}

template<class T>
inline void Heap<T>::init(const int& num)
{
	maxSize = num;
	heap = new T[maxSize];
	if (heap == NULL) {
		cerr << "�Ѵ������ʧ��" << endl;
		exit(-1);
	}
	currentSize = 0;
}

template<class T>
inline bool Heap<T>::push(const T& val)
{
	if (isFull())return false;
	heap[currentSize] = val;
	siftUp();
	currentSize++;
	return true;
}

template<class T>
inline bool Heap<T>::pop()
{
	if (isEmpty())return false;
	heap[0] = heap[--currentSize];
	siftDown();
	return true;
}

template<class T>
inline T Heap<T>::top()
{
	return  heap[0];
}

template<class T>
inline void Heap<T>::siftDown()
{
	int i = 0, j = 2 * i + 1;
	T temp = heap[i];
	while (j < currentSize) {
		if (j + 1 < currentSize && heap[j] > heap[j + 1])j++;
		if (temp <= heap[j])break;
		else {
			heap[i] = heap[j];
			i = j;
			j = 2 * i + 1;
		}
	}
	heap[i] = temp;
}

template<class T>
inline void Heap<T>::siftUp()
{
	int j = currentSize, i = (j - 1) >> 1;
	T temp = heap[j];
	while (j > 0) {
		if (heap[i] <= temp)break;
		else {
			heap[j] = heap[i];
			j = i;
			i = (j - 1) >> 1;
		}
	}
	heap[j] = temp;
}

/************************************************************/
/* Kruskal�㷨                                              */
/************************************************************/
template<class N>
class Kruskal {
private:
	//ͼ���
	int nodeN;					//�ڵ����
	Heap<Edge<N> >net;			//�洢����Ϣ
	Edge<N>* res;				//��¼ѡȡ�ı�
	//���鼯����
	int *father;				//���鼯����
	int findFa(int& node);		//Ѱ��node������
	//�ڵ����ͺ����ֱ��ת��
	N* index;					//�洢�ڵ�����
	int findIndex(N x);			//�ҵ��ڵ��Ӧ�����ֱ��
public:
	Kruskal(const int &num=4);
	~Kruskal() { makeEmpty(); }
	void init(const int& num);
	bool nodeInput();			//����ڵ�
	bool input();				//�������Ϣ
	bool createTree();			//������С������
	void printTree();			//��ʾ��С������
	void makeEmpty();			//���������������
};

template<class N>
inline int Kruskal<N>::findFa(int& node)
{
	while (father[node] > 0)node = father[node];
	return node;
}

template<class N>
inline int Kruskal<N>::findIndex(N x)
{
	for (int i = 0; i < nodeN; i++) {
		if (index[i] == x)return i;
	}
	return -1;
}

template<class N>
inline Kruskal<N>::Kruskal(const int& num):nodeN(num)
{
	net.init(nodeN);
	index = new N[nodeN];
	father = new int[nodeN];
	res = new Edge<N>[nodeN -1];
	for (int i = 0; i < nodeN; i++) {
		father[i] = -1;
	}
}

template<class N>
inline void Kruskal<N>::init(const int& num)
{
	nodeN = num;
	net.init(nodeN);
	index = new N[nodeN];
	father = new int[nodeN];
	res = new Edge<N>[nodeN -1];
	for (int i = 0; i < nodeN; i++) {
		father[i] = -1;
	}
}

template<class N>
inline bool Kruskal<N>::nodeInput()
{
	cout << "�������������������ƣ�" << endl;
	for (int i = 0; i < nodeN; i++) {
		cin >> index[i];
		if (cin.fail())return false;
	}
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	return true;
}

template<class N>
inline bool Kruskal<N>::input()
{
	Edge<N> temp;
	int edgeN = 0;
	while (true) {
		cout << "�������������㼰�ߣ�";
		cin >> temp;
		if (temp.nodeA == '?' || temp.nodeB == '?' || temp.cost == 0) {
			break;
		}
		if (cin.fail() || findIndex(temp.nodeA) == -1 || findIndex(temp.nodeB) == -1)
			return false;
		net.push(temp);
		edgeN++;
	}
	return edgeN >= 1 ? true : false;//����ͼ�е���һ����
}

template<class N>
inline bool Kruskal<N>::createTree()
{
	int i = 0;
	while (!net.isEmpty()) {
		Edge<N> t = net.top();					//��ȡ��ǰȨֵ��С�ı�
		net.pop();
		int indexA = findIndex(t.nodeA), indexB = findIndex(t.nodeB);
		if (findFa(indexA) == findFa(indexB))	//�ж��Ƿ�ɻ�
			continue;
		father[indexA] = findFa(indexB);		//������С������
		res[i++] = t;							//����Ϣ�����ӡ����
	}
	return true;
}

template<class N>
inline void Kruskal<N>::printTree()
{
	cout << "��С�������Ķ��㼰��Ϊ��" << endl;
	for (int i = 0; i < nodeN - 1; i++)
		cout << res[i] << endl;
}

template<class N>
inline void Kruskal<N>::makeEmpty()
{
	delete[]index;
	delete[]father;
	delete[]res;
	nodeN = 0;
}