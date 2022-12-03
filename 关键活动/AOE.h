#pragma once
#include <iostream>
using namespace std;
//邻接表储存连通图
//边
struct ArcNode {
	ArcNode() :nextArc(NULL), _toNode(-1), _weight(-1),_id(0) {}
	ArcNode(int toNode, int weight,int id) :nextArc(NULL), _toNode(toNode), _weight(weight),_id(id) {}
	int _toNode;			//边的另一顶点
	int _weight;			//边的权重
	int _id;				//边的编号
	ArcNode* nextArc;		//同起点的下一条边
};
//点
struct VNode {
	int outDegree = 0;		//出度
	ArcNode* first = NULL;	//邻接表中从该点出发的第一条边
};
//图
class AGraph {
public:
	AGraph();
	~AGraph();
	bool checkAOE();		//检查输入的图是否满足AOE网络
	bool TopSort();			//拓扑排序决定点的顺序
	void CriticalPath();	//求解关键路径
	//用于调试
	//void print() {
	//	cout << endl << "order:" << endl;
	//	for (int i = 0; i < _nNode; i++) {
	//		cout << order[i] << " ";
	//	}
	//	cout << endl << "in:" << endl;
	//	for (int i = 0; i < _nNode; i++) {
	//		cout << inDegree[i] << " ";
	//	}
	//	cout << endl << "out:" << endl;
	//	for (int i = 0; i < _nNode; i++) {
	//		cout << net[i].outDegree << " ";
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
	VNode* net;   //记录图信息
	int* order, * inDegree;//order记录拓扑排序结果；inDegree记录顶点入度
	int* ve, * vl;//顶点相关：ve，事件最早可能开始时间；vl，事件最迟允许开始时间
	int*e, *l;	  //边相关：e，活动最早可能开始时间；l，活动最迟允许开始时间
	int* edgeInfo;//记录边起点和终点信息
	int _nEvent;  //边的条数
	int _nNode;   //顶点的个数
};

AGraph::AGraph()
{
	int nNode, nEvent;
	int from, to, weight;
	while (true) {
		cin >> nNode;
		if (cin.fail() || nNode <= 0 || nNode > 100) {
			cerr << "任务交接点N：输入错误，重新输入！" << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			continue;
		}
		cin >> nEvent;
		if (cin.fail() || nEvent <= 0 || nEvent > nNode * (nNode - 1) / 2) {
			cerr << "任务数量M：输入错误，重新输入！" << endl;
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
				cerr << "任务信息：输入错误，重新输入！" << endl;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				flag = false;
			}
			if (!flag)break;
			from -= 1;
			to -= 1;
			ArcNode* arc = new ArcNode(to, weight, i);
			//加入起点from的链表
			if (net[from].first == nullptr) {
				net[from].first = arc;
			}
			else {
				arc->nextArc = net[from].first;
				net[from].first = arc;
			}
			net[from].outDegree++;	//边的起点出度加一
			inDegree[to]++;			//边的终点入度加一
			//最多有100个顶点，则该数前三位记录起点，后三位记录终点
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

bool AGraph::checkAOE()
{
	for (int i = 0; i < _nNode; i++) {
		if (net[i].outDegree == 0 && i != _nNode - 1) {
			cerr << "存在多终点！" << endl;
			return false;
		}
		if (inDegree[i] == 0&&i!=0) {
			cerr << "存在多起点！" << endl;
			return false;
		}
	}
	return true;
}

bool AGraph::TopSort()
{
	int top = -1, count = 0;
	for (int i = 0; i < _nNode; i++) {
		if (net[i].outDegree == 0 && i != _nNode - 1) {
			cerr << "存在多终点！" << endl;
			return false;
		}
		if (inDegree[i] == 0) {//将所有入度为零的点加入栈中
			inDegree[i] = top;
			top = i;
		}
	}
	for (int i = 0; i < _nNode; i++) {
		if (top == -1) {	//成环条件
			cerr << "成环" << endl;
			return false;
		}
		else {
			int temp = top;	//退栈
			top = inDegree[top];
			order[count++] = temp;	//记录拓扑排序
			//将该点所有相连的边的另一顶点入度减一
			ArcNode* edge = net[temp].first;
			while (edge!=NULL) {
				int k = edge->_toNode;
				if ((--inDegree[k]) == 0) {//如果有减完一后入度为0的加入栈中
					inDegree[k] = top;
					top = k;
				}
				//ve取从起点到此顶点的最大时间作为该事件可以开始的最早时间
				if (ve[temp] + edge->_weight > ve[k])
					ve[k] = ve[temp] + edge->_weight;
				//遍历下一条边
				edge = edge->nextArc;
			}
		}
	}
	return true;

}

void AGraph::CriticalPath()
{
	int top = _nNode - 1;
	int v = order[top--];	//按拓扑逆序出栈
	vl[v] = ve[v];			//终点ve和vl相等
	while (top != -1) {
		v= order[top--];
		ArcNode* p = net[v].first;
		vl[v] = INT_MAX;
		//vl取该顶点到终点的最短路径作为该事件最迟允许开始时间
		while (p != NULL) {
			if (vl[p->_toNode] - p->_weight < vl[v])
				vl[v] = vl[p->_toNode] - p->_weight;
			p = p->nextArc;
		}
	}
	//求活动，即每条边的e[i]，l[i]
	for (int i = 0; i < _nNode; i++) {
		ArcNode* p = net[i].first;
		while (p != NULL) {
			//某活动最早开始时间即其起点的最早开始时间
			e[p->_id] = ve[i];
			//某活动最迟允许开始时间即为终点最迟开始时间-活动持续时间
			l[p->_id] = vl[p->_toNode] - p->_weight;
			//下一条边
			p = p->nextArc;
		}
	}
	//终点的ve或vl即整个项目最早完成时间
	cout << ve[_nNode - 1] << endl;
	//关键路径即为e[i]==l[i]的活动
	for (int i = 0; i < _nEvent; i++) {
		if (e[i] == l[i]) {
			cout << edgeInfo[i] / 1000+1 << "->" << edgeInfo[i] % 1000 +1<< endl;
		}
	}
} 