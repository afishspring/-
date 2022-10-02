#include <iostream>
#include <algorithm>
using namespace std;

bool inputCheck(int& num, const int left, const int right) {
	if (cin.fail()) {
		cerr << "����Ƿ�������������!" << endl;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		return false;
	}
	else if (num < left||num > right) {
		cerr << "����Χ������������!" << endl;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		return false;
	}
	return true;
}

void init(const int n, int*& oriArr, int*& joinArr) {
	oriArr = new int[n+1];
	joinArr = new int[n];
	for (int i = 0; i <n; i++) {
		if (i == 0) {
			cout << "����" << n << "��ľͷ�ĳ��ȣ�";
		}
		cin >> oriArr[i];
		if (!inputCheck(oriArr[i], 1, INT_MAX)) {
			i = -1;
			continue;
		}
		joinArr[i] = INT_MAX;
	}
	oriArr[n] = INT_MAX;
	sort(oriArr,oriArr+n);
}

int solve(const int num,int*& oriArr, int*& joinArr) {
	int  sum = 0, i = 0, j = 0;
	int w;
	for(int k=1;k<num;k++){
		if (oriArr[i] < joinArr[j]) {
			w = oriArr[i];
			i++;
		}
		else {
			w = joinArr[j];
			j++;
		}
		if (oriArr[i] < joinArr[j]) {
			w += oriArr[i];
			i++;
		}
		else {
			w += joinArr[j];
			j++;
		}
		joinArr[k-1] = w;
		sum += w;
	}
	return sum;
}

int main() {
	int num;
	int* _oriArr, * _joinArr;
	while (true) {
		cout << "����ľͷ������N����Χ[1,10000):";
		cin >> num;
		if (!inputCheck(num, 1, 9999)) {
			continue;
		}
		break;
	}
	init(num, _oriArr, _joinArr);
	cout <<"���յĻ���Ϊ��"<< solve(num, _oriArr, _joinArr);
}
//8 4 5 1 2 1 3 1 1
//1 5