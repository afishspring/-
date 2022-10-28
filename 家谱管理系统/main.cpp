#include <iostream>
#include "tree.h"
using namespace std;

void operation(Tree<string>&tr,char oper) {
	string tempP, tempC;
	if (oper == 'A' || oper == 'a') {
		cout << "������Ҫ������ͥ���˵�������";
		cin >> tempP;
		if (!tr.find(tempP)) {
			cerr << "������û�г�Ա" << tempP;
		}
		else {
			int nChild;
			cout << "������" << tempP << "�Ķ�Ů������";
			cin >> nChild;
			cout << "����������" << tempP << "�Ķ�Ů��������";
			for (int i = 1; i <= nChild; i++) {
				cin >> tempC;
				if (!tr.insertChild(tempP, tempC))cerr << "error";
			}
			cout << tempP << "�ĵ�һ�������ǣ�";
			tr.printCurrentChild();
		}
	}
	else if (oper == 'B' || oper == 'b') {
		cout << "������Ҫ��Ӷ��ӣ���Ů�������˵�������";
		cin >> tempP;
		if (!tr.find(tempP)) {
			cerr << "������û�г�Ա" << tempP;
		}
		else {
			cout << "������" << tempP << "����ӵĶ��ӣ���Ů������������";
			cin >> tempC;
			if (!tr.insertChild(tempP, tempC))cerr << "error";
			cout << tempP << "�ĵ�һ�������ǣ�";
			tr.printCurrentChild();
		}
	}
	else if (oper == 'C' || oper == 'c') {
		cout << "������Ҫ��ɢ��ͥ���˵�������";
		cin >> tempP;
		if (!tr.find(tempP)) {
			cerr << "������û�г�Ա" << tempP;
		}
		else {
			cout << "Ҫ��ɢ��ͥ����" << tempP << endl;
			cout << tempP << "�ĵ�һ�������ǣ�";
			tr.printCurrentChild();
			tr.destroyFamily(tempP);
		}
	}
	else {
		cout << "������Ҫ�����������˵ĵ�ǰ������";
		cin >> tempP;
		if (!tr.find(tempP)) {
			cerr << "������û�г�Ա" << tempP;
		}
		else {
			cout << "��������ĺ��������";
			cin >> tempC;
			tr.changeName(tempP, tempC);
			cout << tempP << "�Ѹ���Ϊ" << tempC;
		}
	}
}

int main() {
	cout << "**                  ���׹���ϵͳ                    **" << endl;
	cout << "======================================================" << endl;
	cout << "**               ��ѡ��Ҫִ�еĲ�����               **" << endl;
	cout << "**                 A --- ���Ƽ���                   **" << endl;
	cout << "**                 B --- ��Ӽ�ͥ��Ա               **" << endl;
	cout << "**                 C --- ��ɢ�ֲ���ͥ               **" << endl;
	cout << "**                 D --- ���ļ�ͥ��Ա����           **" << endl;
	cout << "**                 E --- �˳�����                   **" << endl;
	cout << "======================================================" << endl;
	cout << "���Ƚ���һ�����ף�" << endl;

	string name;
	char oper;
	cout << "���������ȵ�����:";
	cin >> name;
	Tree<string>jp(name);
	cout << "�˼��׵������ǣ�";
	jp.printCurrent();

	while (true) {
		cout << endl << endl << "������Ҫִ�еĲ�����";
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cin >> oper;
		if (!(oper >= 'A' && oper <= 'E' || oper >= 'a' && oper <= 'e')) {
			cerr << "�����ʲô����";
			continue;
		}
		if (oper == 'E' || oper == 'e') {
			exit(-1);
		}
		else {
			operation(jp,oper);
		}
	}
	return 0;
}

/*
P0
A
P9
A
P0
2
P1 P2
A
P1
3
P11 P12 P13
B
P2
P21
C
P2
*/