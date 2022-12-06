#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "tree.h"
using namespace std;

//��װ����������ɾ�Ĳ�Ĳ���
void operation(Tree<mystring>&tr,char oper) {
	mystring tempP, tempC;
	if (oper == 'A' || oper == 'a') {
		cout << "������Ҫ������ͥ���˵�������";
		cin >> tempP;
		if (!tr.find(tempP,true)) {
			cerr << "������û�г�Ա" << tempP;
		}
		else {
			int nChild;
			while (true) {
				cout << "������" << tempP << "�Ķ�Ů������";
				cin >> nChild;
				if (cin.fail() || nChild <= 0) {
					cin.clear();
					cin.ignore(INT_MAX, '\n');
					cerr << "��������Ƿ���\n";
					continue;
				}
				else
					break;
			}//�����Ů����
			cout << "����������" << tempP << "�Ķ�Ů��������";
			for (int i = 1; i <= nChild; i++) {
				cin >> tempC;
				if (!tr.insertChild(tempP, tempC))//��Ӻ��ӵĺ�������falseֵ�и��ڵ㲻���ں��������ֿ���
					cerr << "�����ظ�\n";//���ڵ�������������������ˣ���������ֻʣ��һ�ַ���Ϊfalse
			}
			cout << tempP << "�ĵ�һ�������ǣ�";
			tr.printCurrentChild();
		}
	}
	else if (oper == 'B' || oper == 'b') {//�ò�����ʵ��Aû�������
		cout << "������Ҫ��Ӷ��ӣ���Ů�������˵�������";
		cin >> tempP;
		if (!tr.find(tempP,true)) {
			cerr << "������û�г�Ա" << tempP;
		}
		else {
			cout << "������" << tempP << "����ӵĶ��ӣ���Ů������������";
			cin >> tempC;
			if (!tr.insertChild(tempP, tempC))
				cerr << "�����ظ�\n";
			cout << tempP << "�ĵ�һ�������ǣ�";
			tr.printCurrentChild();
		}
	}
	else if (oper == 'C' || oper == 'c') {
		cout << "������Ҫ��ɢ��ͥ���˵�������";
		cin >> tempP;
		if (!tr.find(tempP,true)) {
			cerr << "������û�г�Ա" << tempP;
		}
		else {
			cout << "Ҫ��ɢ��ͥ����" << tempP << endl;
			cout << tempP << "�ĵ�һ�������ǣ�";
			tr.printCurrentChild();//����ڽ�ɢǰ����Ȼ��Ҫ���������
			tr.destroyFamily(tempP);
		}
	}
	else {
		cout << "������Ҫ�����������˵ĵ�ǰ������";
		cin >> tempP;
		if (!tr.find(tempP,true)) {
			cerr << "������û�г�Ա" << tempP;
		}
		else {
			cout << "��������ĺ��������";
			cin >> tempC;
			if (tr.changeName(tempP, tempC))
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
	cout << "**                 E --- ��ӡ����                   **" << endl;
	cout << "**                 F --- �˳�����                   **" << endl;
	cout << "======================================================" << endl;
	cout << "���Ƚ���һ�����ף�" << endl;

	mystring name;
	char oper;
	cout << "���������ȵ�����:";
	cin >> name;
	Tree<mystring>jp(name);
	cout << "�˼��׵������ǣ�";
	jp.printCurrent();

	while (true) {
		cout << endl << endl << "������Ҫִ�еĲ�����";
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cin >> oper;
		if (!(oper >= 'A' && oper <= 'E' || oper >= 'a' && oper <= 'e')) {
			cerr << "����Ƿ���������";
			continue;
		}
		if (oper == 'F' || oper == 'f')
			exit(-1);
		else if(oper == 'E' || oper == 'e')
			jp.print();
		else
			operation(jp,oper);
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