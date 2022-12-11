#include<iostream>
#include"mylist.h"
using namespace std;

bool input(list<int>& _l) {
	int temp = 0;
	while (true) {
		cin >> temp;
		if (cin.fail()) {//�Ƿ��ַ�����
			cerr << "����Ƿ��ַ�" << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			return false;
		}
		else if (temp < *(_l.end())&&_l.get_length()>0 && temp != -1) {//ǰһλ����������ڵ�����
			cerr << "�������б���Ϊ�ǽ���\n";
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			return false;
		}
		else {
			if (temp == -1) {//��ֹ
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
	while (ita != ++_lista.end() && itb != ++_listb.end()) {//��������ָ��֮һ����β��
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
	while (ita != ++_lista.end()) {//��Ϊѡ��lista��Ϊ�������������Ҫ�Ѻ�������Ԫ��ɾ��
		ita++;
		_lista.del_node(pa);//pa���䣬ɾ��һ������һ��Ҫɾ���������Ȼ��pa
	}
}

int main() {
	list<int>lista, listb;
	cout << "�����������ǽ����������У���-1��β" << endl;
	while (!input(lista)) {//����lista
		lista.makeEmpty();
	}
	while (!input(listb)) {//����listb
		listb.makeEmpty();
	}
	unit(lista, listb);//�󽻼�
	lista.print();//������lista
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