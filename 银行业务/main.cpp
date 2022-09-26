#include <iostream>
#include <queue>
using namespace std;
//对输入数据进行检验合法
//[left,right]为数据范围
bool inputCheck(int& num, const int left, const int right) {
	if (cin.fail() || num < left) {
		cerr << "输入非法，请重新输入!" << endl;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		return false;
	}
	else if (num > right) {
		cerr << "超范围，请重新输入!" << endl;
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
		cout << "请输入办理业务的人数：";
		cin >> num;
		if (!inputCheck(num,1,1000)) {
			continue;
		}
		break;
	}
	int temp;
	for (int i = 1; i <= num; i++) {
		if (i == 1) {
			cout << "输入" << num << "位顾客编号：";
		}
		cin >> temp;
		if (!inputCheck(temp, 1, INT_MAX)) {
			i = 0;              //标定重新输入的位置
			qA = queue<int>();  //清空队列qA
			qB = queue<int>();  //清空队列qB
			continue;
		}
		if (temp % 2 != 0) {    //奇数进队列qA
			qA.push(temp);
		}
		else {                  //偶数进队列qB
			qB.push(temp);
		}
	}

	cout << "顾客离开银行的顺序：" << endl;
	while (true) {
		if (!qA.empty()) {
			if (num != 1) {    //确保最后一个编号没有多余的空格
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