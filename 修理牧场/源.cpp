#include <iostream>
#include <algorithm>
using namespace std;

bool inputCheck(int& num, const int left, const int right) {
	if (cin.fail()) {
		cerr << "输入非法，请重新输入!" << endl;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		return false;
	}
	else if (num < left||num > right) {
		cerr << "超范围，请重新输入!" << endl;
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
			cout << "输入" << n << "块木头的长度：";
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
		cout << "输入木头的数量N，范围[1,10000):";
		cin >> num;
		if (!inputCheck(num, 1, 9999)) {
			continue;
		}
		break;
	}
	init(num, _oriArr, _joinArr);
	cout <<"最终的花费为："<< solve(num, _oriArr, _joinArr);
}
//8 4 5 1 2 1 3 1 1
//1 5