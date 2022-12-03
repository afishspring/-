#include <iostream>
#include "MSTE.h"
using namespace std;

//判断是否顺序执行
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
		cerr << "顶点个数未知，无法进行此操作！\n";
		break;
	case 1:
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cerr << "电网边信息未知，无法进行此操作！\n";
		break;
	case 2:
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cerr << "未构造最小生成树，无法进行此操作！\n";
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
	cout << "**                E --- 重新选择算法                 **" << endl;
	cout << "**                F --- 退出  程序                   **" << endl;
	cout << "=======================================================" << endl;

	char oper, ch;
	int num;			//顶点个数
	bool isOper[3] = {};//顺序执行数组
	Prim<int, char>net;
	Kruskal<char>net2;

	int choose;
	while (true) {
		//选择算法
		cout << "选择 1.Prim算法 2.Kruskal算法：";
		cin >> choose;
		if (cin.fail() || choose != 1 && choose != 2) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cerr << "选择错误！\n";
			continue;
		}
		//运行算法
		while (true) {
			cout << endl << "请选择操作：";
			cin >> oper;
			if (!(oper >= 'A' && oper <= 'F' || oper >= 'a' && oper <= 'f')) {
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cerr << "操作数错误！\n";
			}
			else if (oper == 'E' || oper == 'e')break;
			else if (oper == 'F' || oper == 'f')exit(1);
			else if (oper == 'A' || oper == 'a') {
				isOper[0] = false;
				isOper[1] = false;
				isOper[2] = false;
				while (true) {
					cout << "请输入顶点的个数：";
					cin >> num;
					if (cin.fail() || num <= 1) {
						cin.clear();
						cin.ignore(INT_MAX, '\n');
						cerr << "顶点个数有误！\n";
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
						cerr << "电网顶点输入有误！\n";
						continue;
					}
				}
				else {
					net2.makeEmpty();
					net2.init(num);
					while (!net2.nodeInput()) {
						cin.clear();
						cin.ignore(INT_MAX, '\n');
						cerr << "电网顶点输入有误！\n";
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
						cerr << "电网边信息输入有误！\n";
						continue;
					}
				}
				else {
					while (!net2.input()) {
						cin.clear();
						cin.ignore(INT_MAX, '\n');
						cerr << "电网边信息输入有误！\n";
						continue;
					}
				}
				isOper[1] = true;
			}
			else if (oper == 'C' || oper == 'c') {
				if (!checkProgress(isOper, oper))continue;
				if (choose == 1) {
					cout << "请输入起始顶点：";
					cin >> ch;
					if (!net.createTree(ch)) {
						cin.clear();
						cin.ignore(INT_MAX, '\n');
						cerr << "最小生成树构造失败！\n";
						continue;
					}
					cout << "生成Prim最小生成树！" << endl;
				}
				else {
					if (!net2.createTree()) {
						cin.clear();
						cin.ignore(INT_MAX, '\n');
						cerr << "最小生成树构造失败！\n";
						continue;
					}
					cout << "生成Kruskal最小生成树！" << endl;
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