#include <iostream>
#include "mystack.hpp"
using namespace std;

//符号优先级
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

//中缀->后缀
string trans(string &infix) {
	string suffix;
	stack<char>operStack(infix.size());
	for (int i = 0; i <(int) infix.size(); i++) {
		//遇到数字直接输出，包括负数
		if (infix[i] >= '0' && infix[i] <= '9'|| infix[i] == '.'  //无符号数字
			|| i == 0 && infix[i] == '-'  //第一个字符为减号的一定是负号
			|| i > 0 && infix[i] == '-' && infix[i - 1] != ')' && (infix[i - 1] < '0' || infix[i - 1]>'9')) { //"-"当减号用时，仅有前面是数字和后括号两种情况
			suffix += infix[i];
			//没到算术式末尾，并且下一个字符不是数字类字符，说明数字输出结束
			if (i  != (int)infix.size()&&!(infix[i + 1] >= '0' && infix[i + 1] <= '9' || infix[i + 1] == '.'))suffix += " ";
		}
		//"+"与"-"同理，不过不用输出
		else if (i == 0 && infix[i] == '+'
			|| i > 0 && infix[i] == '+' && infix[i - 1] != ')' && (infix[i - 1] < '0' || infix[i - 1]>'9')) {
			continue;
		}
		//符号按优先级决定顺序
		else {
			//前括号直接入栈，栈为空时也直接入栈
			if (operStack.isEmpty()|| infix[i] == '(') {
				operStack.push_back(infix[i]);
			}
			//后括号出现，出栈直到前括号出栈，配成一对括号
			else if (infix[i]==')') {
				while (operStack.top() != '(') {
					suffix = suffix + operStack.top() + " ";
					operStack.pop_back();
				}
				operStack.pop_back();
			}
			//永远是当前栈中优先级高的压优先级低的，否则就出栈到这种情况
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
	//出栈剩下的符号
	while (!operStack.isEmpty()) {
		suffix = suffix + operStack.top() + " ";
		operStack.pop_back();
	}
	return suffix;
}

//单字符读取一行，并忽略空格
void read(string& s) {
	char t = '0';
	while (t != '\n') {
		t = getchar();
		if (t >= '0' && t <= '9' || t == '+' || t == '-' || t == '*' || t == '/' || t == '(' || t == ')'||t=='.')
			s += t;
	}
}

int main() {
	string _infix, _suffix;
	read(_infix);
	_suffix=trans(_infix);
	_suffix.erase(_suffix.find_last_not_of(" ") + 1);//删除结果字符串结尾的空格
	cout << _suffix;
}
//测试数据
//2 + 3 * ( 7 - 4 ) + 8 / 4
//( ( 2 + 3) * 4 - ( 8 + 2 ) ) / 5
//1314 + 25.5 * 12
//-2 * (+3)
//123
//测试结果
//2 3 7 4 - * + 8 4 / +
//2 3 + 4 * 8 2 + - 5 /
//1314 25.5 12 * +
//-2 3 *
//123