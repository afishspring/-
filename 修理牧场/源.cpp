//贪心思想，每次合并最短的那两根木头，总费用最少
#include <iostream>
using namespace std;

//输入正确性检验
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

//用在快排里的交换函数
void swap(int*arr, int a, int b) {
	int temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
}

//三路划分快排
void quickSort(int* arr, const int left, const int right) {
	if (right <= left) { //三路快排终止条件
		return;
	}
	int p, q, i, j, pivot;
	i = p = left;
	j = q = right - 1;
	pivot = arr[right];
	while (true) {
		//从左遍历，找到<=pivot的，将等于的归入左侧等于区间
		while (i < right && arr[i] <= pivot) {
			if (arr[i] == pivot) {
				swap(arr, i, p++);
			}
			i++;
		}
		//从右遍历，找到>=pivot的，将等于的归入右侧等于区间
		while (left <= j && arr[j] >= pivot) {
			if (arr[j] == pivot) {
				swap(arr, j, q--);
			}
			j--;
		}
		//这一趟遍历结束
		if (i >= j) {
			break;
		}
		//此时，左边i指向的是大于pivot的项，j指向的是小于pivot的项（亦即两while终止条件）
		//现交换arr[i]和arr[j]，以便可再次遍历下去
		swap(arr, i++, j--);
	}
	//调换左等于区间与小于区间
	i--;
	p--;
	while (p >= left) {
		swap(arr, i--, p--);
	}
	//调换右等于区间与大于区间
	j++;
	q++;
	while (q <= right) {
		swap(arr, j++, q++);
	}
	//递归小于区间和大于区间
	quickSort(arr, left, i);
	quickSort(arr, j, right);
}

//oriArr输入、joinArr全赋值INT_MAX和oriArr的初始排序
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
	quickSort(oriArr,0,n-1);
}

//计算合并木头的代价
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