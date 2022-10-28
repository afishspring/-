#include <iostream>
#include "tree.h"
using namespace std;

void operation(Tree<string>&tr,char oper) {
	string tempP, tempC;
	if (oper == 'A' || oper == 'a') {
		cout << "请输入要建立家庭的人的姓名：";
		cin >> tempP;
		if (!tr.find(tempP)) {
			cerr << "家谱里没有成员" << tempP;
		}
		else {
			int nChild;
			cout << "请输入" << tempP << "的儿女个数：";
			cin >> nChild;
			cout << "请依次输入" << tempP << "的儿女的姓名：";
			for (int i = 1; i <= nChild; i++) {
				cin >> tempC;
				if (!tr.insertChild(tempP, tempC))cerr << "error";
			}
			cout << tempP << "的第一代子孙是：";
			tr.printCurrentChild();
		}
	}
	else if (oper == 'B' || oper == 'b') {
		cout << "请输入要添加儿子（或女儿）的人的姓名：";
		cin >> tempP;
		if (!tr.find(tempP)) {
			cerr << "家谱里没有成员" << tempP;
		}
		else {
			cout << "请输入" << tempP << "新添加的儿子（或女儿）的姓名：";
			cin >> tempC;
			if (!tr.insertChild(tempP, tempC))cerr << "error";
			cout << tempP << "的第一代子孙是：";
			tr.printCurrentChild();
		}
	}
	else if (oper == 'C' || oper == 'c') {
		cout << "请输入要解散家庭的人的姓名：";
		cin >> tempP;
		if (!tr.find(tempP)) {
			cerr << "家谱里没有成员" << tempP;
		}
		else {
			cout << "要解散家庭的是" << tempP << endl;
			cout << tempP << "的第一代子孙是：";
			tr.printCurrentChild();
			tr.destroyFamily(tempP);
		}
	}
	else {
		cout << "请输入要更改姓名的人的当前姓名：";
		cin >> tempP;
		if (!tr.find(tempP)) {
			cerr << "家谱里没有成员" << tempP;
		}
		else {
			cout << "请输入更改后的姓名：";
			cin >> tempC;
			tr.changeName(tempP, tempC);
			cout << tempP << "已更改为" << tempC;
		}
	}
}

int main() {
	cout << "**                  家谱管理系统                    **" << endl;
	cout << "======================================================" << endl;
	cout << "**               请选择要执行的操作：               **" << endl;
	cout << "**                 A --- 完善家谱                   **" << endl;
	cout << "**                 B --- 添加家庭成员               **" << endl;
	cout << "**                 C --- 解散局部家庭               **" << endl;
	cout << "**                 D --- 更改家庭成员姓名           **" << endl;
	cout << "**                 E --- 退出程序                   **" << endl;
	cout << "======================================================" << endl;
	cout << "首先建立一个家谱！" << endl;

	string name;
	char oper;
	cout << "请输入祖先的名字:";
	cin >> name;
	Tree<string>jp(name);
	cout << "此家谱的祖先是：";
	jp.printCurrent();

	while (true) {
		cout << endl << endl << "请输入要执行的操作：";
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cin >> oper;
		if (!(oper >= 'A' && oper <= 'E' || oper >= 'a' && oper <= 'e')) {
			cerr << "输入的什么东西";
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