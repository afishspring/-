#include <iostream>
#include <queue>
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
	queue<int>qA, qB;
	while (true) {
		cout << "���������ҵ���������";
		cin >> num;
		if (!inputCheck(num,1,1000)) {
			continue;
		}
		break;
	}
	int temp;
	for (int i = 1; i <= num; i++) {
		if (i == 1) {
			cout << "����" << num << "λ�˿ͱ�ţ�";
		}
		cin >> temp;
		if (!inputCheck(temp, 1, INT_MAX)) {
			i = 0;              //�궨���������λ��
			qA = queue<int>();  //��ն���qA
			qB = queue<int>();  //��ն���qB
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
		if (!qA.empty()) {
			if (num != 1) {    //ȷ�����һ�����û�ж���Ŀո�
				cout << qA.front() << " ";
			}
			else {
				cout << qA.front();
			}
			qA.pop();
			num--;
			if (qA.size() % 2 == 1) {
				if (num != 1) {
					cout << qA.front() << " ";
				}
				else {
					cout << qA.front();
				}
				qA.pop();
				num--;
			}
		}
		if (!qB.empty()) {
			if (num != 1) {
				cout << qB.front() << " ";
			}
			else {
				cout << qB.front();
			}
			qB.pop();
			num--;
		}
		if (qA.empty() && qB.empty()) {
			break;
		}
	}
}
//8 2 1 3 9 4 11 13 15
//8 2 1 3 9 4 11 14 16
//1 6