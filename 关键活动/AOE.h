#pragma once
#include <iostream>
using namespace std;
//�ڽӱ�����ͨͼ
//��
struct ArcNode {
	ArcNode() :nextArc(NULL), _toNode(-1), _weight(-1),_id(0) {}
	ArcNode(int toNode, int weight,int id) :nextArc(NULL), _toNode(toNode), _weight(weight),_id(id) {}
	int _toNode;			//�ߵ���һ����
	int _weight;			//�ߵ�Ȩ��
	int _id;				//�ߵı��
	ArcNode* nextArc;		//ͬ������һ����
};
//��
struct VNode {
	int outDegree = 0;		//����
	ArcNode* first = NULL;	//�ڽӱ��дӸõ�����ĵ�һ����
};
//ͼ
class AGraph {
public:
	AGraph();
	~AGraph();
	bool checkAOE();		//��������ͼ�Ƿ�����AOE����
	bool TopSort();			//��������������˳��
	void CriticalPath();	//���ؼ�·��
	//���ڵ���
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
	VNode* net;   //��¼ͼ��Ϣ
	int* order, * inDegree;//order��¼������������inDegree��¼�������
	int* ve, * vl;//������أ�ve���¼�������ܿ�ʼʱ�䣻vl���¼��������ʼʱ��
	int*e, *l;	  //����أ�e���������ܿ�ʼʱ�䣻l����������ʼʱ��
	int* edgeInfo;//��¼�������յ���Ϣ
	int _nEvent;  //�ߵ�����
	int _nNode;   //����ĸ���
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
			//�������from������
			if (net[from].first == nullptr) {
				net[from].first = arc;
			}
			else {
				arc->nextArc = net[from].first;
				net[from].first = arc;
			}
			net[from].outDegree++;	//�ߵ������ȼ�һ
			inDegree[to]++;			//�ߵ��յ���ȼ�һ
			//�����100�����㣬�����ǰ��λ��¼��㣬����λ��¼�յ�
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
			cerr << "���ڶ��յ㣡" << endl;
			return false;
		}
		if (inDegree[i] == 0&&i!=0) {
			cerr << "���ڶ���㣡" << endl;
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
			cerr << "���ڶ��յ㣡" << endl;
			return false;
		}
		if (inDegree[i] == 0) {//���������Ϊ��ĵ����ջ��
			inDegree[i] = top;
			top = i;
		}
	}
	for (int i = 0; i < _nNode; i++) {
		if (top == -1) {	//�ɻ�����
			cerr << "�ɻ�" << endl;
			return false;
		}
		else {
			int temp = top;	//��ջ
			top = inDegree[top];
			order[count++] = temp;	//��¼��������
			//���õ����������ıߵ���һ������ȼ�һ
			ArcNode* edge = net[temp].first;
			while (edge!=NULL) {
				int k = edge->_toNode;
				if ((--inDegree[k]) == 0) {//����м���һ�����Ϊ0�ļ���ջ��
					inDegree[k] = top;
					top = k;
				}
				//veȡ����㵽�˶�������ʱ����Ϊ���¼����Կ�ʼ������ʱ��
				if (ve[temp] + edge->_weight > ve[k])
					ve[k] = ve[temp] + edge->_weight;
				//������һ����
				edge = edge->nextArc;
			}
		}
	}
	return true;

}

void AGraph::CriticalPath()
{
	int top = _nNode - 1;
	int v = order[top--];	//�����������ջ
	vl[v] = ve[v];			//�յ�ve��vl���
	while (top != -1) {
		v= order[top--];
		ArcNode* p = net[v].first;
		vl[v] = INT_MAX;
		//vlȡ�ö��㵽�յ�����·����Ϊ���¼��������ʼʱ��
		while (p != NULL) {
			if (vl[p->_toNode] - p->_weight < vl[v])
				vl[v] = vl[p->_toNode] - p->_weight;
			p = p->nextArc;
		}
	}
	//������ÿ���ߵ�e[i]��l[i]
	for (int i = 0; i < _nNode; i++) {
		ArcNode* p = net[i].first;
		while (p != NULL) {
			//ĳ����翪ʼʱ�伴���������翪ʼʱ��
			e[p->_id] = ve[i];
			//ĳ��������ʼʱ�伴Ϊ�յ���ٿ�ʼʱ��-�����ʱ��
			l[p->_id] = vl[p->_toNode] - p->_weight;
			//��һ����
			p = p->nextArc;
		}
	}
	//�յ��ve��vl��������Ŀ�������ʱ��
	cout << ve[_nNode - 1] << endl;
	//�ؼ�·����Ϊe[i]==l[i]�Ļ
	for (int i = 0; i < _nEvent; i++) {
		if (e[i] == l[i]) {
			cout << edgeInfo[i] / 1000+1 << "->" << edgeInfo[i] % 1000 +1<< endl;
		}
	}
} 