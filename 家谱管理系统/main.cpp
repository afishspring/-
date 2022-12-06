#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "tree.h"
using namespace std;

//封装对树进行增删改查的操作
void operation(Tree<mystring>&tr,char oper) {
	mystring tempP, tempC;
	if (oper == 'A' || oper == 'a') {
		cout << "请输入要建立家庭的人的姓名：";
		cin >> tempP;
		if (!tr.find(tempP,true)) {
			cerr << "家谱里没有成员" << tempP;
		}
		else {
			int nChild;
			while (true) {
				cout << "请输入" << tempP << "的儿女个数：";
				cin >> nChild;
				if (cin.fail() || nChild <= 0) {
					cin.clear();
					cin.ignore(INT_MAX, '\n');
					cerr << "数字输入非法！\n";
					continue;
				}
				else
					break;
			}//输入儿女个数
			cout << "请依次输入" << tempP << "的儿女的姓名：";
			for (int i = 1; i <= nChild; i++) {
				cin >> tempC;
				if (!tr.insertChild(tempP, tempC))//添加孩子的函数返回false值有父节点不存在和重名两种可能
					cerr << "名字重复\n";//父节点存在性已在上面检验过了，所以这里只剩后一种返回为false
			}
			cout << tempP << "的第一代子孙是：";
			tr.printCurrentChild();
		}
	}
	else if (oper == 'B' || oper == 'b') {//该操作其实与A没多大区别
		cout << "请输入要添加儿子（或女儿）的人的姓名：";
		cin >> tempP;
		if (!tr.find(tempP,true)) {
			cerr << "家谱里没有成员" << tempP;
		}
		else {
			cout << "请输入" << tempP << "新添加的儿子（或女儿）的姓名：";
			cin >> tempC;
			if (!tr.insertChild(tempP, tempC))
				cerr << "名字重复\n";
			cout << tempP << "的第一代子孙是：";
			tr.printCurrentChild();
		}
	}
	else if (oper == 'C' || oper == 'c') {
		cout << "请输入要解散家庭的人的姓名：";
		cin >> tempP;
		if (!tr.find(tempP,true)) {
			cerr << "家谱里没有成员" << tempP;
		}
		else {
			cout << "要解散家庭的是" << tempP << endl;
			cout << tempP << "的第一代子孙是：";
			tr.printCurrentChild();//输出在解散前，不然需要额外存姓名
			tr.destroyFamily(tempP);
		}
	}
	else {
		cout << "请输入要更改姓名的人的当前姓名：";
		cin >> tempP;
		if (!tr.find(tempP,true)) {
			cerr << "家谱里没有成员" << tempP;
		}
		else {
			cout << "请输入更改后的姓名：";
			cin >> tempC;
			if (tr.changeName(tempP, tempC))
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
	cout << "**                 E --- 打印家谱                   **" << endl;
	cout << "**                 F --- 退出程序                   **" << endl;
	cout << "======================================================" << endl;
	cout << "首先建立一个家谱！" << endl;

	mystring name;
	char oper;
	cout << "请输入祖先的名字:";
	cin >> name;
	Tree<mystring>jp(name);
	cout << "此家谱的祖先是：";
	jp.printCurrent();

	while (true) {
		cout << endl << endl << "请输入要执行的操作：";
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cin >> oper;
		if (!(oper >= 'A' && oper <= 'E' || oper >= 'a' && oper <= 'e')) {
			cerr << "输入非法操作符！";
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