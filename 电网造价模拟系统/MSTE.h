#pragma once
#include <iostream>
#include <cstring>
#define DefaultSz 50
using namespace std;
/************************************************************/
/* Prim算法                                                 */
/************************************************************/
template<class T, class N>
class Prim {
private:
	int num;			//节点数量
	T** net;			//邻接矩阵
	T* lowcost;			//其他节点到生成树的最短距离
	bool* visit;		//标记节点是否加入到树中
	int* parent;		//存储最小生成树路径
	N* index;			//存储节点类型
	int findIndex(N x); //找到节点对应的数字编号
public:
	Prim(int sz=4);				//构造函数
	~Prim() { makeEmpty(); }	//析构函数
	void init(const int& num);	//初始化私有数组
	bool nodeInput();			//输入节点
	bool input();				//输入边信息
	int minCost();				//求解当前距离生成树最近的节点
	bool createTree(N start);	//构建最小生成树
	void printTree();			//显示最小生成树
	void makeEmpty();			//清空所有数组内容
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
	int edgeN = 0;
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
	//初始化
	for (int i = 0; i < num; i++) { 
		lowcost[i] = INT_MAX;
		visit[i] = false;
		parent[i] = -1;
	}
	if (findIndex(start) == -1)return false;	//防止起始点不存在
	lowcost[findIndex(start)] = 0;				//初始赋值
	parent[findIndex(start)] = -1;
	for (int i = 0; i < num - 1; i++) {
		//当前和生成树相连的最小权值的边，此边不在顶点集合的顶点
		int u = minCost();
		visit[u] = true;	//标记顶点已加入生成树
		//lowcost更新新增顶点相连的所有边
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

/************************************************************/
/* Kruskal算法----Edge结构体，用于存储边信息                */
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
/* Kruskal算法----小根堆，用于边的选取                      */
/************************************************************/
template<class T>
class Heap {
public:
	Heap(int sz = DefaultSz);
	~Heap() { clear(); }
	void init(const int &num); //调整堆大小为num
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
		cerr << "堆储存分配失败" << endl;
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
		cerr << "堆储存分配失败" << endl;
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
/* Kruskal算法                                              */
/************************************************************/
template<class N>
class Kruskal {
private:
	//图相关
	int nodeN;					//节点个数
	Heap<Edge<N> >net;			//存储边信息
	Edge<N>* res;				//记录选取的边
	//并查集部分
	int *father;				//并查集数组
	int findFa(int& node);		//寻找node的祖先
	//节点类型和数字编号转换
	N* index;					//存储节点类型
	int findIndex(N x);			//找到节点对应的数字编号
public:
	Kruskal(const int &num=4);
	~Kruskal() { makeEmpty(); }
	void init(const int& num);
	bool nodeInput();			//输入节点
	bool input();				//输入边信息
	bool createTree();			//构建最小生成树
	void printTree();			//显示最小生成树
	void makeEmpty();			//清空所有数组内容
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
	cout << "请依次输入各顶点的名称：" << endl;
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
		cout << "请输入两个顶点及边：";
		cin >> temp;
		if (temp.nodeA == '?' || temp.nodeB == '?' || temp.cost == 0) {
			break;
		}
		if (cin.fail() || findIndex(temp.nodeA) == -1 || findIndex(temp.nodeB) == -1)
			return false;
		net.push(temp);
		edgeN++;
	}
	return edgeN >= 1 ? true : false;//至少图中得有一条边
}

template<class N>
inline bool Kruskal<N>::createTree()
{
	int i = 0;
	while (!net.isEmpty()) {
		Edge<N> t = net.top();					//获取当前权值最小的边
		net.pop();
		int indexA = findIndex(t.nodeA), indexB = findIndex(t.nodeB);
		if (findFa(indexA) == findFa(indexB))	//判断是否成环
			continue;
		father[indexA] = findFa(indexB);		//加入最小生成树
		res[i++] = t;							//边信息存入打印数组
	}
	return true;
}

template<class N>
inline void Kruskal<N>::printTree()
{
	cout << "最小生成树的顶点及边为：" << endl;
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