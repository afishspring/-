#include <iostream>
#include "sort.h"
using namespace std;
int main()
{
	cout << "**                   �����㷨�Ƚ�                    **" << endl;
	cout << "=======================================================" << endl;
	cout << "**                  1 --- ð������                   **" << endl;
	cout << "**                  2 --- ѡ������                   **" << endl;
	cout << "**                  3 --- ֱ�Ӳ�������               **" << endl;
	cout << "**                  4 --- ϣ������                   **" << endl;
	cout << "**                  5 --- ��������                   **" << endl;
	cout << "**                  6 --- ������                     **" << endl;
	cout << "**                  7 --- �鲢����                   **" << endl;
	cout << "**                  8 --- ��������                   **" << endl;
	cout << "**                  9 --- �˳�  ����                 **" << endl;
	cout << "=======================================================" << endl;
	cout << "������Ҫ������������ĸ�����";

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