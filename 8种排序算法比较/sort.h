#pragma once
#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

template<class T>
class sort {
public:
	sort(int size = 100);
	~sort();
	void init(int minN, int maxN);//生成minN~maxN的随机数
	void BubbleSort();            //冒泡排序
	void SeleteSort();            //选择排序
	void InsertSort();            //直接插入排序
	void ShellSort();             //希尔插入排序
	void QuickSort();             //快速排序
	void HeapSort();              //堆排序
	void MergeSort();             //归并排序
	void RadixSort();             //基数排序
	void print();                 //打印交换次数或调试时观察排序结果
private:
	int ShellInsert(int add);                 //步长为add的希尔子排序，add为1即为直接插入排序
	void qSort(int left, int right);          //快速排序
	void maxHeap(int start,int end);          //大根堆
	void merge(int low, int mid, int high);   //归并
	void swap(int x, int y);                  //交换下标为x与y的值
	void copyData();                          //复制源数据到res数组
	int maxDigit();                           //用于基数排序的求数字最高位数的函数
	int sz;                  //数据大小
	long long count = 0;     //计数判断次数
	T* data;  //存放源数据
	T* res;   //表示排序过程和排序结果的数组
};

template<class T>
inline sort<T>::sort(int size):sz(size)
{
	data = new T[sz]();
	res = new T[sz]();
}

template<class T>
inline sort<T>::~sort()
{
	delete[]data;
	delete[]res;
}

template<class T>
inline void sort<T>::init(int minN,int maxN)
{
	srand((int)time(NULL));
	for (int i = 0; i < sz; i++) {
		data[i] = (rand() % (maxN - minN + 1)) + minN;
	}
}

template<class T>
inline void sort<T>::BubbleSort()
{
	copyData();
	count = 0;
	for (int j = sz - 1; j >= 0; j--) {
		for (int i = 0; i < j; i++) {
			count++;
			if (res[i] > res[i + 1]) {
				swap(i, i + 1);
			}
		}
	}
}

template<class T>
inline void sort<T>::SeleteSort()
{
	copyData();
	count = 0;
	int minIndex;
	for (int i = 0; i < sz-1; i++) {
		minIndex = i;
		for (int j = i + 1; j < sz; j++) {
			count++;
			if (res[minIndex] > res[j]) {
				minIndex = j;
			}
		}
		if (minIndex != i) {
			swap(i, minIndex);
		}
	}
}

template<class T>
inline void sort<T>::InsertSort()
{
	copyData();
	ShellInsert(1);
}

template<class T>
inline void sort<T>::ShellSort()
{
	copyData();
	count = 0;
	int shellCount = 0;
	int step = sz;
	while (step > 1) {
		step /= 2;
		shellCount = ShellInsert(step);
		//count += shellCount;
	}
}

template<class T>
inline void sort<T>::QuickSort()
{
	copyData();
	count = 0;
	qSort(0, sz-1);
}

template<class T>
inline void sort<T>::HeapSort()
{
	copyData();
	count = 0;
	for (int i = sz / 2 - 1; i >= 0; i--)
		maxHeap(i, sz - 1);
	for (int i = sz - 1; i > 0; i--) {
		swap(0, i);
		maxHeap(0, i - 1);
	}
}

template<class T>
inline void sort<T>::MergeSort()
{
	copyData();
	count = 0;
	int rangeLen=1, low, mid, high;
	while (rangeLen <= sz - 1) {
		low = 0;
		while (low + rangeLen <= sz - 1) {
			mid = low + rangeLen - 1;
			high = mid + rangeLen;
			if (high > sz - 1)
				high = sz - 1; count++;
			merge(low, mid, high);
			low = high + 1;
		}
		rangeLen *= 2;
	}
}

template<class T>
inline void sort<T>::RadixSort()
{
	copyData();
	count = 0;
	int digit = maxDigit(), base = 1;
	T* temp = new T[sz];
	int* counter = new int[10];
	int* startPos = new int[10];
	while (digit--) {
		memset(counter, 0, 10 * sizeof(int));
		for (int i = 0; i < sz; i++) {
			int index = res[i] / base % 10;
			counter[index]++;
		}
		memset(startPos, 0, 10 * sizeof(int));
		for (int i = 1; i < 10; i++) {
			startPos[i] = startPos[i - 1] + counter[i - 1];
		}
		memset(temp, 0, sz * sizeof(T));
		for (int i = 0; i < sz; i++) {
			int index = res[i] / base % 10;
			temp[(startPos[index])++] = res[i];
		}
		memcpy(res, temp, sz * sizeof(T));
		base *= 10;
	}
	delete[]temp;
	delete[]counter;
	delete[]startPos;
}

template<class T>
inline void sort<T>::print()
{
	//cout << endl << "before:" << endl;
	//for (int i = 0; i < sz; i++) {
	//	if (i % 5 == 0)cout << endl;
	//	cout << setiosflags(ios::left) << setw(10) << data[i];
	//}
	//cout << endl << "after:" << endl;
	//for (int i = 0; i < sz; i++) {
	//	if (i % 5 == 0)cout << endl;
	//	cout << setiosflags(ios::left) << setw(10) << res[i];
	//}
	cout << count << endl;
}

template<class T>
inline int sort<T>::ShellInsert(int add)
{
	int k = 0, iPos;
	T nowNum;
	for (int i = add; i < sz; i++) {
		nowNum = res[i];
		iPos = i - add;
		while (iPos >= 0 && res[iPos] > nowNum) {
			count++;
			res[iPos + add] = res[iPos];
			iPos -= add;
			k++;
		}
		res[iPos + add] = nowNum;
		k++;
	}
	return k;
}

template<class T>
inline void sort<T>::qSort(int left, int right)
{
	count++;
	if (left >= right)
		return;
	T pivot = res[left];
	int low = left, high = right;
	while (low<high) {
		while (res[high] >= pivot && low < high)
			high--; count++;
		if(low<high)
			res[low++] = res[high]; count++;
		while (res[low] <= pivot && low < high)
			low++; count++;
		if(low<high)
			res[high--] = res[low]; count++;
	}

	res[low] = pivot;
	qSort(left, low - 1);
	qSort(low + 1, right);
}

template<class T>
inline void sort<T>::maxHeap(int start,int end)
{
	int i = start, j = 2 * start + 1;
	while (j <=end) {
		if (j + 1 <= end && res[j] < res[j + 1]) {
			j++; count++;
		}
		count++;
		if (res[i] > res[j])break;
		else {
			swap(i, j);
			i = j;
			j = 2 * i + 1;
		}
	}
}

template<class T>
inline void sort<T>::merge(int low, int mid, int high)
{
	int i = low, j = mid + 1, k = 0;
	T* temp = new T[high - low + 1];
	if (!temp) {
		cerr << "error" << endl;
		exit(-1);
	}
	while (i <= mid && j <= high) {
		count++;
		if (res[i] <= res[j])
			temp[k++] = res[i++];
		else
			temp[k++] = res[j++];
	}
	while (i <= mid)
		temp[k++] = res[i++]; count++;
	while (j <= high)
		temp[k++] = res[j++]; count++;
	for (int index = low, k = 0; index <= high; index++, k++)
		res[index] = temp[k];
	delete[]temp;
}

template<class T>
inline void sort<T>::swap(int x, int y)
{
	T temp = res[x];
	res[x] = res[y];
	res[y] = temp;
}

template<class T>
inline void sort<T>::copyData()
{
	for (int i = 0; i < sz; i++) {
		res[i] = data[i];
	}
}

template<class T>
inline int sort<T>::maxDigit()
{
	T maxNum = res[0];
	for (int i = 1; i < sz; i++) {
		if (res[i] > maxNum)
			maxNum = res[i];
	}
	int maxDigit = 0;
	while (maxNum) {
		maxNum /= 10;
		maxDigit++;
	}
	return maxDigit;
}