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
		inputClear("顶点个数未知，无法进行此操作！");
		break;
	case 1:
		inputClear("电网边信息未知，无法进行此操作！");
		break;
	case 2:
		inputClear("未构造最小生成树，无法进行此操作！");
		break;
	default:
		return true;
	}
	return false;
}

int main() {
	cout << "**                 电网造价模拟系统                  **" << endl;
	cout << "=======================================================" << endl;
	cout << "**                A --- 创建电网顶点                 **" << endl;
	cout << "**                B --- 添加电网的边                 **" << endl;
	cout << "**                C --- 构造最小生成树               **" << endl;
	cout << "**                D --- 显示最小生成树               **" << endl;
	cout << "**                E --- 退出  程序                   **" << endl;
	cout << "=======================================================" << endl;

	char oper, ch;
	int num; //顶点个数
	bool isOper[3] = {};
	Prim<int, char>net;

	while (true) {
		cout <<endl<< "请选择操作：";
		cin >> oper;
		if (!(oper >= 'A' && oper <= 'E' || oper >= 'a' && oper <= 'e'))inputClear("操作数错误！");
		else if (oper == 'E' || oper == 'e')exit(1);
		else if (oper == 'A' || oper == 'a') {
			isOper[0] = false;
			isOper[1] = false;
			isOper[2] = false;
			cout << "请输入顶点的个数：";
			cin >> num;
			if (cin.fail() || num <= 0)inputClear("顶点个数有误！");
			net.makeEmpty();
			net.init(num);
			while (!net.nodeInput()) {
				inputClear("电网顶点输入有误！");
				continue;
			}
			isOper[0] = true;
		}
		else if (oper == 'B' || oper == 'b') {
			if (!checkProgress(isOper,oper))continue;
			while (!net.input()) {
				inputClear("电网边信息输入有误！");
				continue;
			}
			isOper[1] = true;
		}
		else if (oper == 'C' || oper == 'c') {
			if (!checkProgress(isOper,oper))continue;
			cout << "请输入起始顶点：";
			cin >> ch;
			if (!net.createTree(ch)) {
				inputClear("最小生成树构造失败！");
				continue;
			}
			cout << "生成Prim最小生成树！" << endl;
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