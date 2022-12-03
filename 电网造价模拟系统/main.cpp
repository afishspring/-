#include <iostream>
#include "MSTE.h"
using namespace std;

//�ж��Ƿ�˳��ִ��
bool checkProgress(bool is[3],const char &oper) {
	int nowStep = 0, step = -1;
	if (oper >= 'A' && oper <= 'D')nowStep = oper - 'A';
	else if (oper >= 'a' && oper <= 'd')nowStep = oper - 'a';
	for (int i = 0; i < nowStep; i++) {
		if (is[i] == false)step = i;
	}
	switch (step) {
	case 0:
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cerr << "�������δ֪���޷����д˲�����\n";
		break;
	case 1:
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cerr << "��������Ϣδ֪���޷����д˲�����\n";
		break;
	case 2:
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cerr << "δ������С���������޷����д˲�����\n";
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
	cout << "**                E --- ����ѡ���㷨                 **" << endl;
	cout << "**                F --- �˳�  ����                   **" << endl;
	cout << "=======================================================" << endl;

	char oper, ch;
	int num;			//�������
	bool isOper[3] = {};//˳��ִ������
	Prim<int, char>net;
	Kruskal<char>net2;

	int choose;
	while (true) {
		//ѡ���㷨
		cout << "ѡ�� 1.Prim�㷨 2.Kruskal�㷨��";
		cin >> choose;
		if (cin.fail() || choose != 1 && choose != 2) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cerr << "ѡ�����\n";
			continue;
		}
		//�����㷨
		while (true) {
			cout << endl << "��ѡ�������";
			cin >> oper;
			if (!(oper >= 'A' && oper <= 'F' || oper >= 'a' && oper <= 'f')) {
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cerr << "����������\n";
			}
			else if (oper == 'E' || oper == 'e')break;
			else if (oper == 'F' || oper == 'f')exit(1);
			else if (oper == 'A' || oper == 'a') {
				isOper[0] = false;
				isOper[1] = false;
				isOper[2] = false;
				while (true) {
					cout << "�����붥��ĸ�����";
					cin >> num;
					if (cin.fail() || num <= 1) {
						cin.clear();
						cin.ignore(INT_MAX, '\n');
						cerr << "�����������\n";
						continue;
					}
					else break;
				}
				if (choose == 1) {
					net.makeEmpty();
					net.init(num);
					while (!net.nodeInput()) {
						cin.clear();
						cin.ignore(INT_MAX, '\n');
						cerr << "����������������\n";
						continue;
					}
				}
				else {
					net2.makeEmpty();
					net2.init(num);
					while (!net2.nodeInput()) {
						cin.clear();
						cin.ignore(INT_MAX, '\n');
						cerr << "����������������\n";
						continue;
					}
				}
				isOper[0] = true;
			}
			else if (oper == 'B' || oper == 'b') {
				if (!checkProgress(isOper, oper))continue;
				if (choose == 1) {
					while (!net.input()) {
						cin.clear();
						cin.ignore(INT_MAX, '\n');
						cerr << "��������Ϣ��������\n";
						continue;
					}
				}
				else {
					while (!net2.input()) {
						cin.clear();
						cin.ignore(INT_MAX, '\n');
						cerr << "��������Ϣ��������\n";
						continue;
					}
				}
				isOper[1] = true;
			}
			else if (oper == 'C' || oper == 'c') {
				if (!checkProgress(isOper, oper))continue;
				if (choose == 1) {
					cout << "��������ʼ���㣺";
					cin >> ch;
					if (!net.createTree(ch)) {
						cin.clear();
						cin.ignore(INT_MAX, '\n');
						cerr << "��С����������ʧ�ܣ�\n";
						continue;
					}
					cout << "����Prim��С��������" << endl;
				}
				else {
					if (!net2.createTree()) {
						cin.clear();
						cin.ignore(INT_MAX, '\n');
						cerr << "��С����������ʧ�ܣ�\n";
						continue;
					}
					cout << "����Kruskal��С��������" << endl;
				}
				isOper[2] = true;
			}
			else if (oper == 'D' || oper == 'd') {
				if (!checkProgress(isOper, oper))continue;
				if (choose == 1) {
					net.printTree();
				}
				else {
					net2.printTree();
				}
			}
		}
	}
	return 0;
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