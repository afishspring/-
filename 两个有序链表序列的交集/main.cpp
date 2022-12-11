#include<iostream>
#include"mylist.h"
using namespace std;

bool input(list<int>& _l) {
	int temp = 0;
	while (true) {
		cin >> temp;
		if (cin.fail()) {//非法字符输入
			cerr << "输入非法字符" << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			return false;
		}
		else if (temp < *(_l.end())&&_l.get_length()>0 && temp != -1) {//前一位输入大于现在的输入
			cerr << "输入序列必须为非降序\n";
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			return false;
		}
		else {
			if (temp == -1) {//终止
				break;
			}
			else {
				_l.push_back(temp);
			}
		}
	}
	return true;
}

//求两链表交集，双指针遍历两链表
void unit(list<int>& _lista, list<int>& _listb) {
	list<int>::iterator ita = _lista.begin(), itb = _listb.begin();
	int vala = 0, valb = 0, pa = 1;
	while (ita != ++_lista.end() && itb != ++_listb.end()) {//遍历到两指针之一到达尾部
		vala = *ita;
		valb = *itb;
		if (vala < valb) {
			ita++;
			_lista.del_node(pa);
		}
		else if (vala == valb) {
			ita++;
			pa++;
			itb++;
		}
		else {
			itb++;
		}
	}
	while (ita != ++_lista.end()) {//因为选定lista作为结果链表，所以需要把后面多余的元素删除
		ita++;
		_lista.del_node(pa);//pa不变，删除一个，下一个要删除的序号仍然是pa
	}
}

int main() {
	list<int>lista, listb;
	cout << "请输入两个非降序链表序列，以-1结尾" << endl;
	while (!input(lista)) {//输入lista
		lista.makeEmpty();
	}
	while (!input(listb)) {//输入listb
		listb.makeEmpty();
	}
	unit(lista, listb);//求交集
	lista.print();//输出结果lista
}
/*
1 2 5 -1
2 4 5 8 10 -1

1 3 5 -1
2 4 6 8 10 -1

1 2 3 4 5 -1
1 2 3 4 5 -1

3 5 7 -1
2 3 4 5 6 7 8 -1

2 3 4 5 6 7 8 -1
3 5 7 -1

-1
10 100 1000 -1
*/