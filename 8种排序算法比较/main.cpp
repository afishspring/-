#include <iostream>
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
	sort<int>x(15);
	x.init(0,100);
	x.BubbleSort();
	cout << "bubble";
	x.print();

	x.SeleteSort();
	cout << "select";
	x.print();

	x.InsertSort();
	cout << "insert";
	x.print();

	x.ShellSort();
	cout << "shell";
	x.print();

	x.QuickSort();
	cout << "quick";
	x.print();

	x.HeapSort();
	cout << "heap";
	x.print();

	x.MergeSort();
	cout << "merge";
	x.print();

	x.RadixSort();
	cout << "radix";
	x.print();
}