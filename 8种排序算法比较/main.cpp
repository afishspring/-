#include <iostream>
#include <Windows.h>
#define setwNum 28
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
	cin >> num;
	sort<int>x(num);
	x.init(0,num);
	while (true) {
		cout << setiosflags(ios::left) << setw(setwNum) << "��ѡ�������㷨��";
		cin >> oper;

		LARGE_INTEGER tick, begin, end;
		QueryPerformanceFrequency(&tick); //��ü�����Ƶ��
		QueryPerformanceCounter(&begin); //��ó�ʼӲ������������

		switch (oper) {
		case 1:
			x.BubbleSort();
			cout << setw(setwNum) << "ð�����򽻻�������";
			x.print();
			cout << setw(setwNum) << "ð����������ʱ�䣺";
			break;
		case 2:
			x.SeleteSort();
			cout << setw(setwNum) << "ѡ�����򽻻�������";
			x.print();
			cout << setw(setwNum) << "ѡ����������ʱ�䣺";
			break;
		case 3:
			x.InsertSort();
			cout << setw(setwNum) << "ֱ�Ӳ������򽻻�������";
			x.print();
			cout << setw(setwNum) << "ֱ�Ӳ�����������ʱ�䣺";
			break;
		case 4:
			x.ShellSort();
			cout << setw(setwNum) << "ϣ���������򽻻�������";
			x.print();
			cout << setw(setwNum) << "ϣ��������������ʱ�䣺";
			break;
		case 5:
			x.QuickSort();
			cout << setw(setwNum) << "�������򽻻�������";
			x.print();
			cout << setw(setwNum) << "������������ʱ�䣺";
			break;
		case 6:
			x.HeapSort();
			cout << setw(setwNum) << "�����򽻻�������";
			x.print();
			cout << setw(setwNum) << "����������ʱ�䣺";
			break;
		case 7:
			x.MergeSort();
			cout << setw(setwNum) << "�鲢���򽻻�������";
			x.print();
			cout << setw(setwNum) << "�鲢��������ʱ�䣺";
			break;
		case 8:
			x.RadixSort();
			cout << setw(setwNum) << "�������򽻻�������";
			x.print();
			cout << setw(setwNum) << "������������ʱ�䣺";
			break;
		case 9:
			exit(1);
			break;
		}
		QueryPerformanceCounter(&end);
		cout << setiosflags(ios::fixed) << setprecision(6) << double(end.QuadPart - begin.QuadPart) / tick.QuadPart << "��" << endl << endl;
	}
}