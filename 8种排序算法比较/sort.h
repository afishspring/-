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
	void BubbleSort();            //冒泡排序
	void SeleteSort();            //选择排序
	void InsertSort();            //直接插入排序
	void ShellSort();             //希尔插入排序
	void QuickSort();             //快速排序
	void HeapSort();              //堆排序
	void MergeSort();             //归并排序
	void RadixSort();             //基数排序
	void print();                 //打印交换次数或调试时观察排序结果
	void printSwap() { cout << swapN << endl; }
private:
	long long int ShellInsert(int add);                 //步长为add的希尔子排序，add为1即为直接插入排序
	void qSort(int left, int right);          //快速排序
	void maxHeap(int start,int end);          //大根堆
	void merge(int low, int mid, int high);   //归并
	void copyData();                          //复制源数据到res数组
	int maxDigit();                           //用于基数排序的求数字最高位数的函数
	int sz;                  //数据大小
	long long ifN = 0;     //计数判断次数
	long long swapN = 0;
	T* data;  //存放源数据
	T* res;   //表示排序过程和排序结果的数组
};

template<class T>
sort<T>::sort(int size):sz(size)
{
	data = new T[sz];
	res = new T[sz];
	srand((int)time(NULL));//随机数种子
	for (int i = 0; i < sz; i++) {
		data[i] = rand();
	}//生成随机数
}

template<class T>
sort<T>::~sort()
{
	delete[]data;
	delete[]res;
}

template<class T>
void sort<T>::BubbleSort()
{
	copyData();//拷贝未排序数据
	ifN = 0; swapN = 0;//比较和移动次数置零
	long long int timeOnce = 0;
	//从最大的元素开始冒泡
	for (int j =0;j <sz-1; j++) {
		timeOnce = 0;
		for (int i = 0; i < sz-j-1; i++) {
			ifN++;
			if (res[i] > res[i + 1]) {
				timeOnce += 3;
				T temp = res[i];
				res[i] = res[i+1];
				res[i+1] = temp;
			}
		}
		if (timeOnce == 0) {
			return;
		}//如果这一趟中没交换元素，说明序列已有序
		swapN += timeOnce;
	}
}

template<class T>
void sort<T>::SeleteSort()
{
	copyData();//拷贝未排序数据
	ifN = 0; swapN = 0;//比较和移动次数置零
	int minIndex;
	for (int i = 0; i < sz-1; i++) {
		minIndex = i;
		for (int j = i + 1; j < sz; j++) {
			ifN++;
			if (res[minIndex] > res[j]) {
				minIndex = j;
			}
		}
		if (minIndex != i) {
			swapN += 3;
			T temp = res[i];
			res[i] = res[minIndex];
			res[minIndex] = temp;
		}
	}
}

template<class T>
void sort<T>::InsertSort()
{
	copyData();//拷贝未排序数据
	ifN = 0;//比较次数置零
	swapN =ShellInsert(1);//ShellInsert返回值就是元素移动次数
}

template<class T>
void sort<T>::ShellSort()
{
	copyData();//拷贝未排序数据
	ifN = 0; swapN = 0;//比较和移动次数置零
	int step = sz;
	while (step > 1) {//从序列长度的一半开始为步长，到步长为1等价于直接插入排序
		step /= 2;
		swapN += ShellInsert(step);
	}//步长逐渐减半的直接插入排序
}

template<class T>
void sort<T>::QuickSort()
{
	copyData();//拷贝未排序数据
	ifN = 0; swapN = 0;//比较和移动次数置零
	qSort(0, sz-1);//范围为整个序列的快排
}

template<class T>
void sort<T>::HeapSort()
{
	copyData();//拷贝未排序数据
	ifN = 0; swapN = 0;//比较和移动次数置零
	for (int i = sz / 2 - 1; i >= 0; i--){
		maxHeap(i, sz - 1);
	}//建大根堆，实际上是对所有非叶子节点进行向下调整
	for (int i = sz - 1; i > 0; i--) {
		swapN += 3;
		T temp = res[0];//交换未排序序列尾结点与根节点
		res[0] = res[i];
		res[i] = temp;
		maxHeap(0, i - 1);//交换完，向下调整为大根堆
	}
}

template<class T>
void sort<T>::MergeSort()
{
	copyData();//拷贝未排序数据
	ifN = 0; swapN = 0;//比较和移动次数置零
	int rangeLen=1, low, mid, high;//rangeLen为每次归并的大序列的左半区长度
	while (rangeLen <= sz - 1) {
		low = 0;
		while (low + rangeLen <= sz - 1) {
			mid = low + rangeLen - 1;
			high = mid + rangeLen;
			if (high > sz - 1)//受序列长度限制，最后一个子序列可能右区间较短
				high = sz - 1;
			merge(low, mid, high);//归并[low,high]
			low = high + 1;//下一区间
		}
		rangeLen *= 2;
	}//分治的过程
}

template<class T>
void sort<T>::RadixSort()
{
	copyData();//拷贝未排序数据
	ifN = 0; swapN = 0;//比较和移动次数置零
	int digit = maxDigit(), base = 1;//获取序列最高位，即最大值的位数
	T* temp = new T[sz];//用数组模拟队列，思想类似矩阵转置
	int* counter = new int[10];//记录每个位数下不同数字的个数
	int* startPos = new int[10];//根据counter生成在temp数组里对应队列位置
	while (digit--) {//从个位开始，最大值的最高位数结束
		memset(counter, 0, 10 * sizeof(int));
		for (int i = 0; i < sz; i++) {
			int index = res[i] / base % 10;
			counter[index]++;
		}//统计排序码某部分不同值的个数
		memset(startPos, 0, 10 * sizeof(int));
		for (int i = 1; i < 10; i++) {
			startPos[i] = startPos[i - 1] + counter[i - 1];
		}//生成不同值在temp中模拟队列的起始位置
		memset(temp, 0, sz * sizeof(T));
		for (int i = 0; i < sz; i++) {
			int index = res[i] / base % 10;
			temp[(startPos[index])++] = res[i];
		}//重新遍历序列，根据位数的数值进队列
		memcpy(res, temp, sz * sizeof(T));//复制temp到结果数组中
		base *= 10;//位数加一
	}
	delete[]temp;
	delete[]counter;
	delete[]startPos;
}

template<class T>
void sort<T>::print()
{
	//调试，排序正确性测试
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
	cout << ifN << endl;
}

template<class T>
long long int sort<T>::ShellInsert(int add)
{
	//对所有序列增量为add的子序列进行插入排序
	long long int k = 0;//记录数据移动次数
	int iPos;//插入位置
	T nowNum;//即将插入的数据
	for (int i = add; i < sz; i++) {//从每个子序列的第二个数开始插入
		nowNum = res[i];
		iPos = i - add;
		while (iPos >= 0 && res[iPos] > nowNum) {//选择插入位置
			ifN++;
			res[iPos + add] = res[iPos];
			iPos -= add;//插入位置前移
			k++;
		}
		res[iPos + add] = nowNum;//插入成功
		k++;
	}
	return k;
}

template<class T>
void sort<T>::qSort(int left, int right)
{
	if (left >= right)//快速排序的小于、大于区间至少有两个才能排序
		return;
	T pivot = res[left];//选取子序列最左端的值为基准值
	int low = left, high = right;//分别为遍历序列的指针
	while (low<high) {//循环终止条件为两指针相遇
		while (res[high] >= pivot && low < high) {
			high--; ifN++;
		}//右指针向前遍历至遇到小于等于基准值的
		if (low < high) {
			res[low++] = res[high]; swapN++;
		}//high遇到小于等于基准值的元素就与low指针内容交换
		while (res[low] <= pivot && low < high) {
			low++; ifN++;
		}//左指针向后遍历至遇到大于等于基准值的
		if (low < high) {
			res[high--] = res[low]; swapN++;
		}//low遇到大于等于基准值的元素就与high指针内容交换
	}
	swapN++;
	//上面while循环结束后，low和high共同指向小于区间最右端的数
	//与基准值交换，保证序列整体划分有序
	res[low] = pivot;
	qSort(left, low - 1);//递归小于区间
	qSort(low + 1, right);//递归大于区间
}

template<class T>
void sort<T>::maxHeap(int start,int end)
{
	int i = start, j = 2 * start + 1;//i指向非叶子节点，j为i的子节点
	while (j <=end) {
		//j指向子节点中大的那个
		if (j + 1 <= end && res[j] < res[j + 1]) {
			j++; ifN++;
		}
		ifN++;
		if (res[i] > res[j])break;
		else {//根节点小于子节点，需要交换
			swapN += 3;
			T temp = res[i];
			res[i] = res[j];
			res[j] = temp;
		}
		//继续向下调整
		i = j;
		j = 2 * i + 1;
	}
}

template<class T>
void sort<T>::merge(int low, int mid, int high)
{
	int i = low, j = mid + 1, k = 0;
	T* temp = new T[high - low + 1]();//开辟归并数组
	if (!temp) {
		cerr << "error" << endl;
		exit(-1);
	}
	while (i <= mid && j <= high) {
		ifN++; swapN++;
		if (res[i] <= res[j])
			temp[k++] = res[i++];
		else
			temp[k++] = res[j++];
	}//双指针遍历两子序列，将两指针数值小的复制到归并数组中后再后移
	while (i <= mid&&k< high - low + 1) {
		temp[k++] = res[i++]; swapN++;
	}//若左序列剩余，将余下的复制到归并数组
	while (j <= high&&k< high - low + 1) {
		temp[k++] = res[j++]; swapN++;
	}//右序列同理
	for (int index = low, k = 0; index <= high; index++, k++) {
		res[index] = temp[k]; swapN++;
	}//将归并数组结果复制给存储排序结果的数组，以备下次归并使用
	delete[]temp;
}

template<class T>
void sort<T>::copyData()
{
	for (int i = 0; i < sz; i++) {
		res[i] = data[i];
	}
}

template<class T>
int sort<T>::maxDigit()
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