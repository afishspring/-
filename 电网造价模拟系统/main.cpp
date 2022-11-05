#include <iostream>
#include "PrimTree.h"
using namespace std;

void inputClear(string error)
{
	cerr << error << endl;
	cin.clear();
	cin.ignore(INT_MAX, '\n');
}

bool checkProgress(bool is[3],const char &oper) {
	int nowStep = 0;
	if (oper >= 'A' && oper <= 'D')nowStep = oper - 'A';
	else if (oper >= 'a' && oper <= 'd')nowStep = oper - 'a';
	int step = -1;
	for (int i = 0; i < nowStep; i++) {
		if (is[i] == false)step = i;
	}
	switch (step) {
	case 0:
		inputClear("�������δ֪���޷����д˲�����");
		break;
	case 1:
		inputClear("��������Ϣδ֪���޷����д˲�����");
		break;
	case 2:
		inputClear("δ������С���������޷����д˲�����");
		break;
	default:
		return true;
	}
	return false;
}

int main() {
	cout << "**                 �������ģ��ϵͳ                  **" << endl;
	cout << "=======================================================" << endl;
	cout << "**                A --- ������������                 **" << endl;
	cout << "**                B --- ��ӵ����ı�                 **" << endl;
	cout << "**                C --- ������С������               **" << endl;
	cout << "**                D --- ��ʾ��С������               **" << endl;
	cout << "**                E --- �˳�  ����                   **" << endl;
	cout << "=======================================================" << endl;

	char oper, ch;
	int num; //�������
	bool isOper[3] = {};
	Prim<int, char>net;

	while (true) {
		cout <<endl<< "��ѡ�������";
		cin >> oper;
		if (!(oper >= 'A' && oper <= 'E' || oper >= 'a' && oper <= 'e'))inputClear("����������");
		else if (oper == 'E' || oper == 'e')exit(1);
		else if (oper == 'A' || oper == 'a') {
			isOper[0] = false;
			isOper[1] = false;
			isOper[2] = false;
			cout << "�����붥��ĸ�����";
			cin >> num;
			if (cin.fail() || num <= 0)inputClear("�����������");
			net.makeEmpty();
			net.init(num);
			while (!net.nodeInput()) {
				inputClear("����������������");
				continue;
			}
			isOper[0] = true;
		}
		else if (oper == 'B' || oper == 'b') {
			if (!checkProgress(isOper,oper))continue;
			while (!net.input()) {
				inputClear("��������Ϣ��������");
				continue;
			}
			isOper[1] = true;
		}
		else if (oper == 'C' || oper == 'c') {
			if (!checkProgress(isOper,oper))continue;
			cout << "��������ʼ���㣺";
			cin >> ch;
			if (!net.createTree(ch)) {
				inputClear("��С����������ʧ�ܣ�");
				continue;
			}
			cout << "����Prim��С��������" << endl;
			isOper[2] = true;
		}
		else if (oper == 'D' || oper == 'd') {
			if (!checkProgress(isOper, oper))continue;
			net.printTree();
		}
	}
}
/*
A
4
a b c d
B
a b 8
b c 7
c d 5
d a 11
a c 18
b d 12
? ? 0
C
d
D
*/