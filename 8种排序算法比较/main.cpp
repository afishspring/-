#include <iostream>
#include <Windows.h>
#define setwNum 28
#include "sort.h"
using namespace std;
int main()
{
	cout << "**                   排序算法比较                    **" << endl;
	cout << "=======================================================" << endl;
	cout << "**                  1 --- 冒泡排序                   **" << endl;
	cout << "**                  2 --- 选择排序                   **" << endl;
	cout << "**                  3 --- 直接插入排序               **" << endl;
	cout << "**                  4 --- 希尔排序                   **" << endl;
	cout << "**                  5 --- 快速排序                   **" << endl;
	cout << "**                  6 --- 堆排序                     **" << endl;
	cout << "**                  7 --- 归并排序                   **" << endl;
	cout << "**                  8 --- 基数排序                   **" << endl;
	cout << "**                  9 --- 退出  程序                 **" << endl;
	cout << "=======================================================" << endl;
	cout << "请输入要产生的随机数的个数：";

	int num, oper;
	cin >> num;
	sort<int>x(num);
	x.init(0,num);
	while (true) {
		cout << setiosflags(ios::left) << setw(setwNum) << "请选择排序算法：";
		cin >> oper;

		LARGE_INTEGER tick, begin, end;
		QueryPerformanceFrequency(&tick); //获得计数器频率
		QueryPerformanceCounter(&begin); //获得初始硬件计数器计数

		switch (oper) {
		case 1:
			x.BubbleSort();
			cout << setw(setwNum) << "冒泡排序交换次数：";
			x.print();
			cout << setw(setwNum) << "冒泡排序所用时间：";
			break;
		case 2:
			x.SeleteSort();
			cout << setw(setwNum) << "选择排序交换次数：";
			x.print();
			cout << setw(setwNum) << "选择排序所用时间：";
			break;
		case 3:
			x.InsertSort();
			cout << setw(setwNum) << "直接插入排序交换次数：";
			x.print();
			cout << setw(setwNum) << "直接插入排序所用时间：";
			break;
		case 4:
			x.ShellSort();
			cout << setw(setwNum) << "希尔插入排序交换次数：";
			x.print();
			cout << setw(setwNum) << "希尔插入排序所用时间：";
			break;
		case 5:
			x.QuickSort();
			cout << setw(setwNum) << "快速排序交换次数：";
			x.print();
			cout << setw(setwNum) << "快速排序所用时间：";
			break;
		case 6:
			x.HeapSort();
			cout << setw(setwNum) << "堆排序交换次数：";
			x.print();
			cout << setw(setwNum) << "堆排序所用时间：";
			break;
		case 7:
			x.MergeSort();
			cout << setw(setwNum) << "归并排序交换次数：";
			x.print();
			cout << setw(setwNum) << "归并排序所用时间：";
			break;
		case 8:
			x.RadixSort();
			cout << setw(setwNum) << "基数排序交换次数：";
			x.print();
			cout << setw(setwNum) << "基数排序所用时间：";
			break;
		case 9:
			exit(1);
			break;
		}
		QueryPerformanceCounter(&end);
		cout << setiosflags(ios::fixed) << setprecision(6) << double(end.QuadPart - begin.QuadPart) / tick.QuadPart << "秒" << endl << endl;
	}
}