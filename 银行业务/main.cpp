#include <iostream>
#include "myqueue.hpp"
using namespace std;
//���������ݽ��м���Ϸ�
//[left,right]Ϊ���ݷ�Χ
bool inputCheck(int& num, const int left, const int right) {
	if (cin.fail() || num < left) {
		cerr << "����Ƿ�������������!" << endl;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		return false;
	}
	else if (num > right) {
		cerr << "����Χ������������!" << endl;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		return false;
	}
	return true;
}

int main() {
	int num;
	while (true) {
		cout << "���������ҵ���������";
		cin >> num;
		if (!inputCheck(num,1,1000)) {
			continue;
		}
		break;
	}
	queue<int>qA(num), qB(num);
	int temp;
	for (int i = 1; i <= num; i++) {
		if (i == 1) {
			cout << "����" << num << "λ�˿ͱ�ţ�";
		}
		cin >> temp;
		if (!inputCheck(temp, 1, INT_MAX)) {
			i = 0;              //�궨���������λ��
			qA.clear();         //��ն���qA
			qB.clear();         //��ն���qB
			continue;
		}
		if (temp % 2 != 0) {    //����������qA
			qA.push(temp);
		}
		else {                  //ż��������qB
			qB.push(temp);
		}
	}

	cout << "�˿��뿪���е�˳��" << endl;
	while (true) {
		if (!qA.isEmpty()) {				//qA�����һ����
			cout << qA.front();
			if (num != 1) { cout << " "; }  //ȷ�����һ�����û�ж���Ŀո�
			qA.pop();
			num--;

		}
		if (!qA.isEmpty()) {				//qA����ڶ�����
			cout << qA.front();
			if (num != 1) { cout << " "; }
			qA.pop();
			num--;
		}
		if (!qB.isEmpty()) {				//qB���һ����
			cout << qB.front();
			if (num != 1) { cout << " "; }
			qB.pop();
			num--;
		}
		if (qA.isEmpty() && qB.isEmpty()) {	//�����ֹ����
			break;
		}
	}
}
//8 2 1 3 9 4 11 13 15
//8 2 1 3 9 4 11 14 16
//1 6
//1 2 5 9 8 3 6 7