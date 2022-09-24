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
	int pa = 1, pb = 1;
	int vala=0,valb= 0;
	while (pa != _lista.get_length()+1 && pb != _listb.get_length()+1) {
		vala = _lista.get_node(pa);
		valb = _listb.get_node(pb);
		if (vala < valb) {
			_lista.del_node(pa);
		}
		else if (vala == valb) {
			pa++;
			pb++;
		}
		else {
			pb++;
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