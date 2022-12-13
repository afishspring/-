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

	int num, oper;
	LARGE_INTEGER tick, begin, end;
	while (true) {
		cout << "������Ҫ������������ĸ�����";
		cin >> num;
		if (cin.fail() || num <= 1) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cerr << "����Ƿ���\n";
		}
		else
			break;
	}//���������
	sort<int>x(num);//���������Ϊnum��������
	while (true) {
		while (true) {
			cout << setiosflags(ios::left) << setw(setwNum) << "��ѡ�������㷨��";
			cin >> oper;
			if (cin.fail() || oper < 1 || oper>9) {
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cerr << "����Ƿ���\n";
			}
			else
				break;
		}//������ȷ�������㷨������
		QueryPerformanceFrequency(&tick); //��ü�����Ƶ��
		QueryPerformanceCounter(&begin); //��ó�ʼӲ������������

		switch (oper) {
		case 1:
			x.BubbleSort();
			cout << setw(setwNum) << "ð������ת�ƴ�����";
			x.printSwap();
			cout << setw(setwNum) << "ð������Ƚϴ�����";
			x.print();
			cout << setw(setwNum) << "ð����������ʱ�䣺";
			break;
		case 2:
			x.SeleteSort();
			cout << setw(setwNum) << "ѡ������ת�ƴ�����";
			x.printSwap();
			cout << setw(setwNum) << "ѡ������Ƚϴ�����";
			x.print();
			cout << setw(setwNum) << "ѡ����������ʱ�䣺";
			break;
		case 3:
			x.InsertSort();
			cout << setw(setwNum) << "ֱ�Ӳ�������ת�ƴ�����";
			x.printSwap();
			cout << setw(setwNum) << "ֱ�Ӳ�������Ƚϴ�����";
			x.print();
			cout << setw(setwNum) << "ֱ�Ӳ�����������ʱ�䣺";
			break;
		case 4:
			x.ShellSort();
			cout << setw(setwNum) << "ϣ����������ת�ƴ�����";
			x.printSwap();
			cout << setw(setwNum) << "ϣ����������Ƚϴ�����";
			x.print();
			cout << setw(setwNum) << "ϣ��������������ʱ�䣺";
			break;
		case 5:
			x.QuickSort();
			cout << setw(setwNum) << "��������ת�ƴ�����";
			x.printSwap();
			cout << setw(setwNum) << "��������Ƚϴ�����";
			x.print();
			cout << setw(setwNum) << "������������ʱ�䣺";
			break;
		case 6:
			x.HeapSort();
			cout << setw(setwNum) << "������ת�ƴ�����";
			x.printSwap();
			cout << setw(setwNum) << "������Ƚϴ�����";
			x.print();
			cout << setw(setwNum) << "����������ʱ�䣺";
			break;
		case 7:
			x.MergeSort();
			cout << setw(setwNum) << "�鲢����ת�ƴ�����";
			x.printSwap();
			cout << setw(setwNum) << "�鲢����Ƚϴ�����";
			x.print();
			cout << setw(setwNum) << "�鲢��������ʱ�䣺";
			break;
		case 8:
			x.RadixSort();
			cout << setw(setwNum) << "��������ת�ƴ�����";
			x.printSwap();
			cout << setw(setwNum) << "��������Ƚϴ�����";
			x.print();
			cout << setw(setwNum) << "������������ʱ�䣺";
			break;
		case 9:
			exit(1);
			break;
		}
		QueryPerformanceCounter(&end); //��ȡӲ������������
		cout << setiosflags(ios::fixed) << setprecision(6) << double(end.QuadPart - begin.QuadPart) / tick.QuadPart << "��" << endl << endl;
	}
}