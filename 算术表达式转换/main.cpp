#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "mystack.hpp"
#include "mystring.h"

using namespace std;

//�������ȼ�
int priority(char oper) {
	if (oper == '*' || oper == '/') {
		return 2;
	}
	if (oper == '+' || oper == '-') {
		return 1;
	}
	if (oper == '(') {
		return 0;
	}
	return -1;
}

//��׺->��׺
mystring trans(mystring &infix) {
	mystring suffix;
	stack<char>operStack(infix.size());
	for (int i = 0; i <=(int) infix.size(); i++) {
		//��������ֱ���������������
		if (infix[i] >= '0' && infix[i] <= '9'|| infix[i] == '.'  //�޷�������
			|| i == 0 && infix[i] == '-'  //��һ���ַ�Ϊ���ŵ�һ���Ǹ���
			|| i > 0 && infix[i] == '-' && infix[i - 1] != ')' && (infix[i - 1] < '0' || infix[i - 1]>'9')) { //"-"��������ʱ������ǰ�������ֺͺ������������
			suffix += infix[i];
			//û������ʽĩβ��������һ���ַ������������ַ���˵�������������
			if (i != (int)infix.size() + 1 && !(infix[i + 1] >= '0' && infix[i + 1] <= '9' || infix[i + 1] == '.'))suffix += " ";
		}
		//"+"��"-"ͬ�������������
		else if (i == 0 && infix[i] == '+'
			|| i > 0 && infix[i] == '+' && infix[i - 1] != ')' && (infix[i - 1] < '0' || infix[i - 1]>'9')) {
			continue;
		}
		//���Ű����ȼ�����˳��
		else {
			//ǰ����ֱ����ջ��ջΪ��ʱҲֱ����ջ
			if (operStack.isEmpty()|| infix[i] == '(') {
				operStack.push_back(infix[i]);
			}
			//�����ų��֣���ջֱ��ǰ���ų�ջ�����һ������
			else if (infix[i]==')') {
				while (operStack.top() != '(') {
					suffix = suffix + operStack.top() + " ";
					operStack.pop_back();
				}
				operStack.pop_back();
			}
			//��Զ�ǵ�ǰջ�����ȼ��ߵ�ѹ���ȼ��͵ģ�����ͳ�ջ���������
			else {
				while (priority(operStack.top()) >= priority(infix[i])) {
					suffix = suffix + operStack.top() + " ";
					operStack.pop_back();
					if (operStack.isEmpty()) {
						break;
					}
				}
				operStack.push_back(infix[i]);
			}
		}
	}
	//��ջʣ�µķ���
	while (!operStack.isEmpty()) {
		suffix = suffix + operStack.top() + " ";
		operStack.pop_back();
	}
	return suffix;
}

//���ַ���ȡһ�У������Կո�
void read(mystring& s) {
	char t = '0';
	int n = 0;
	while (true) {
		bool flag = true;
		while (t != '\n') {
			if (n > 20) {
				flag = false;
				break;
			}
			t = getchar();
			if (t >= '0' && t <= '9' || t == '+' || t == '-' || t == '*' || t == '/' || t == '(' || t == ')' || t == '.') {
				s += t; n++;
			}
			else if (t == ' ' || t == '\n');
			else {
				flag = false;
				break;
			}
		}
		if (n > 20) {
			s.clear(); t = '0'; n = 0; flag = true;
			cerr << "�����ַ�����20����" << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			continue;
		}
		else if (flag == false) {
			s .clear(); t = '0'; n = 0; flag = true;
			cerr << "�����зǷ��ַ���" << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			continue;
		}
		else {
			break;
		}
	}
}

int main() {
	mystring _infix, _suffix;
	read(_infix);
	_suffix=trans(_infix);
	_suffix.erase(_suffix.size());//ɾ������ַ�����β�Ŀո�
	cout << _suffix;
}
//��������
//2 + 3 * ( 7 - 4 ) + 8 / 4
//( ( 2 + 3) * 4 - ( 8 + 2 ) ) / 5
//1314 + 25.5 * 12
//-2 * (+3)
//123
//���Խ��
//2 3 7 4 - * + 8 4 / +
//2 3 + 4 * 8 2 + - 5 /
//1314 25.5 12 * +
//-2 3 *
//123