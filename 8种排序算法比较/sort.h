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
	void BubbleSort();            //ð������
	void SeleteSort();            //ѡ������
	void InsertSort();            //ֱ�Ӳ�������
	void ShellSort();             //ϣ����������
	void QuickSort();             //��������
	void HeapSort();              //������
	void MergeSort();             //�鲢����
	void RadixSort();             //��������
	void print();                 //��ӡ�������������ʱ�۲�������
	void printSwap() { cout << swapN << endl; }
private:
	long long int ShellInsert(int add);                 //����Ϊadd��ϣ��������addΪ1��Ϊֱ�Ӳ�������
	void qSort(int left, int right);          //��������
	void maxHeap(int start,int end);          //�����
	void merge(int low, int mid, int high);   //�鲢
	void copyData();                          //����Դ���ݵ�res����
	int maxDigit();                           //���ڻ�����������������λ���ĺ���
	int sz;                  //���ݴ�С
	long long ifN = 0;     //�����жϴ���
	long long swapN = 0;
	T* data;  //���Դ����
	T* res;   //��ʾ������̺�������������
};

template<class T>
sort<T>::sort(int size):sz(size)
{
	data = new T[sz];
	res = new T[sz];
	srand((int)time(NULL));//���������
	for (int i = 0; i < sz; i++) {
		data[i] = rand();
	}//���������
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
	copyData();//����δ��������
	ifN = 0; swapN = 0;//�ȽϺ��ƶ���������
	long long int timeOnce = 0;
	//������Ԫ�ؿ�ʼð��
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
		}//�����һ����û����Ԫ�أ�˵������������
		swapN += timeOnce;
	}
}

template<class T>
void sort<T>::SeleteSort()
{
	copyData();//����δ��������
	ifN = 0; swapN = 0;//�ȽϺ��ƶ���������
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
	copyData();//����δ��������
	ifN = 0;//�Ƚϴ�������
	swapN =ShellInsert(1);//ShellInsert����ֵ����Ԫ���ƶ�����
}

template<class T>
void sort<T>::ShellSort()
{
	copyData();//����δ��������
	ifN = 0; swapN = 0;//�ȽϺ��ƶ���������
	int step = sz;
	while (step > 1) {//�����г��ȵ�һ�뿪ʼΪ������������Ϊ1�ȼ���ֱ�Ӳ�������
		step /= 2;
		swapN += ShellInsert(step);
	}//�����𽥼����ֱ�Ӳ�������
}

template<class T>
void sort<T>::QuickSort()
{
	copyData();//����δ��������
	ifN = 0; swapN = 0;//�ȽϺ��ƶ���������
	qSort(0, sz-1);//��ΧΪ�������еĿ���
}

template<class T>
void sort<T>::HeapSort()
{
	copyData();//����δ��������
	ifN = 0; swapN = 0;//�ȽϺ��ƶ���������
	for (int i = sz / 2 - 1; i >= 0; i--){
		maxHeap(i, sz - 1);
	}//������ѣ�ʵ�����Ƕ����з�Ҷ�ӽڵ�������µ���
	for (int i = sz - 1; i > 0; i--) {
		swapN += 3;
		T temp = res[0];//����δ��������β�������ڵ�
		res[0] = res[i];
		res[i] = temp;
		maxHeap(0, i - 1);//�����꣬���µ���Ϊ�����
	}
}

template<class T>
void sort<T>::MergeSort()
{
	copyData();//����δ��������
	ifN = 0; swapN = 0;//�ȽϺ��ƶ���������
	int rangeLen=1, low, mid, high;//rangeLenΪÿ�ι鲢�Ĵ����е����������
	while (rangeLen <= sz - 1) {
		low = 0;
		while (low + rangeLen <= sz - 1) {
			mid = low + rangeLen - 1;
			high = mid + rangeLen;
			if (high > sz - 1)//�����г������ƣ����һ�������п���������϶�
				high = sz - 1;
			merge(low, mid, high);//�鲢[low,high]
			low = high + 1;//��һ����
		}
		rangeLen *= 2;
	}//���εĹ���
}

template<class T>
void sort<T>::RadixSort()
{
	copyData();//����δ��������
	ifN = 0; swapN = 0;//�ȽϺ��ƶ���������
	int digit = maxDigit(), base = 1;//��ȡ�������λ�������ֵ��λ��
	T* temp = new T[sz];//������ģ����У�˼�����ƾ���ת��
	int* counter = new int[10];//��¼ÿ��λ���²�ͬ���ֵĸ���
	int* startPos = new int[10];//����counter������temp�������Ӧ����λ��
	while (digit--) {//�Ӹ�λ��ʼ�����ֵ�����λ������
		memset(counter, 0, 10 * sizeof(int));
		for (int i = 0; i < sz; i++) {
			int index = res[i] / base % 10;
			counter[index]++;
		}//ͳ��������ĳ���ֲ�ֵͬ�ĸ���
		memset(startPos, 0, 10 * sizeof(int));
		for (int i = 1; i < 10; i++) {
			startPos[i] = startPos[i - 1] + counter[i - 1];
		}//���ɲ�ֵͬ��temp��ģ����е���ʼλ��
		memset(temp, 0, sz * sizeof(T));
		for (int i = 0; i < sz; i++) {
			int index = res[i] / base % 10;
			temp[(startPos[index])++] = res[i];
		}//���±������У�����λ������ֵ������
		memcpy(res, temp, sz * sizeof(T));//����temp�����������
		base *= 10;//λ����һ
	}
	delete[]temp;
	delete[]counter;
	delete[]startPos;
}

template<class T>
void sort<T>::print()
{
	//���ԣ�������ȷ�Բ���
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
	//��������������Ϊadd�������н��в�������
	long long int k = 0;//��¼�����ƶ�����
	int iPos;//����λ��
	T nowNum;//�������������
	for (int i = add; i < sz; i++) {//��ÿ�������еĵڶ�������ʼ����
		nowNum = res[i];
		iPos = i - add;
		while (iPos >= 0 && res[iPos] > nowNum) {//ѡ�����λ��
			ifN++;
			res[iPos + add] = res[iPos];
			iPos -= add;//����λ��ǰ��
			k++;
		}
		res[iPos + add] = nowNum;//����ɹ�
		k++;
	}
	return k;
}

template<class T>
void sort<T>::qSort(int left, int right)
{
	if (left >= right)//���������С�ڡ���������������������������
		return;
	T pivot = res[left];//ѡȡ����������˵�ֵΪ��׼ֵ
	int low = left, high = right;//�ֱ�Ϊ�������е�ָ��
	while (low<high) {//ѭ����ֹ����Ϊ��ָ������
		while (res[high] >= pivot && low < high) {
			high--; ifN++;
		}//��ָ����ǰ����������С�ڵ��ڻ�׼ֵ��
		if (low < high) {
			res[low++] = res[high]; swapN++;
		}//high����С�ڵ��ڻ�׼ֵ��Ԫ�ؾ���lowָ�����ݽ���
		while (res[low] <= pivot && low < high) {
			low++; ifN++;
		}//��ָ�����������������ڵ��ڻ�׼ֵ��
		if (low < high) {
			res[high--] = res[low]; swapN++;
		}//low�������ڵ��ڻ�׼ֵ��Ԫ�ؾ���highָ�����ݽ���
	}
	swapN++;
	//����whileѭ��������low��high��ָͬ��С���������Ҷ˵���
	//���׼ֵ��������֤�������廮������
	res[low] = pivot;
	qSort(left, low - 1);//�ݹ�С������
	qSort(low + 1, right);//�ݹ��������
}

template<class T>
void sort<T>::maxHeap(int start,int end)
{
	int i = start, j = 2 * start + 1;//iָ���Ҷ�ӽڵ㣬jΪi���ӽڵ�
	while (j <=end) {
		//jָ���ӽڵ��д���Ǹ�
		if (j + 1 <= end && res[j] < res[j + 1]) {
			j++; ifN++;
		}
		ifN++;
		if (res[i] > res[j])break;
		else {//���ڵ�С���ӽڵ㣬��Ҫ����
			swapN += 3;
			T temp = res[i];
			res[i] = res[j];
			res[j] = temp;
		}
		//�������µ���
		i = j;
		j = 2 * i + 1;
	}
}

template<class T>
void sort<T>::merge(int low, int mid, int high)
{
	int i = low, j = mid + 1, k = 0;
	T* temp = new T[high - low + 1]();//���ٹ鲢����
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
	}//˫ָ������������У�����ָ����ֵС�ĸ��Ƶ��鲢�����к��ٺ���
	while (i <= mid&&k< high - low + 1) {
		temp[k++] = res[i++]; swapN++;
	}//��������ʣ�࣬�����µĸ��Ƶ��鲢����
	while (j <= high&&k< high - low + 1) {
		temp[k++] = res[j++]; swapN++;
	}//������ͬ��
	for (int index = low, k = 0; index <= high; index++, k++) {
		res[index] = temp[k]; swapN++;
	}//���鲢���������Ƹ��洢�����������飬�Ա��´ι鲢ʹ��
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