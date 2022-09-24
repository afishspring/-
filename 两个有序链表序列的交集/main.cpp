#include<iostream>
#include"mylist.hpp"
using namespace std;

bool input(list<int>& _l) {
	int temp = 0;
	while (true) {
		cin >> temp;
		if (cin.fail()) {
			cerr << "����Ƿ��ַ�" << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');

			return false;
		}
		else {
			if (temp == -1) {
				break;
			}
			else {
				_l.push_back(temp);
			}
		}
	}
	return true;
}

//������������˫ָ�����������
void unit(list<int>& _lista, list<int>& _listb) {
	list<int>::iterator ita = _lista.begin(), itb = _listb.begin();
	int vala = 0, valb = 0, pa = 1;
	while (ita != ++_lista.end() && itb != ++_listb.end()) {
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
}

int main() {
	list<int>lista, listb;
	cout << "�����������ǽ����������У���-1��β" << endl;
	while (!input(lista) || !input(listb)) {
		cout << "�����������ǽ����������У���-1��β" << endl;
	}
	unit(lista, listb);
	lista.print();
	cout << endl;
}
/*
1 2 5 -1
2 4 5 8 10 -1
*/