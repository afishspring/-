#include <iostream>
#include <string>
#include "mystack.hpp"
using namespace std;

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
}

string trans(string &infix) {
	string suffix;
	stack<char>operStack(infix.size());
	for (int i = 0; i <(int) infix.size(); i++) {
		if (infix[i] >= '0' && infix[i] <= '9'
			|| infix[i] == '.'
			|| i == 0 && infix[i] == '-'
			|| i > 0 && infix[i] == '-' && infix[i - 1] != ')' && (infix[i - 1] < '0' || infix[i - 1]>'9')) {
			suffix += infix[i];
			if (i  != (int)infix.size()&&!(infix[i + 1] >= '0' && infix[i + 1] <= '9' || infix[i + 1] == '.'))suffix += " ";
		}
		else if (i == 0 && infix[i] == '+'
			|| i > 0 && infix[i] == '+' && infix[i - 1] != ')' && (infix[i - 1] < '0' || infix[i - 1]>'9')) {
			continue;
		}
		else {
			if (operStack.isEmpty()|| infix[i] == '(') {
				operStack.push_back(infix[i]);
			}
			else if (infix[i]==')') {
				while (operStack.top() != '(') {
					suffix = suffix + operStack.top() + " ";
					operStack.pop_back();
				}
				operStack.pop_back();
			}
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
	while (!operStack.isEmpty()) {
		suffix = suffix + operStack.top() + " ";
		operStack.pop_back();
	}
	return suffix;
}

void trim(string& s)
{
	int index = 0;
	if (!s.empty())
	{
		while ((index = s.find(' ', index)) != string::npos)
		{
			s.erase(index, 1);
		}
	}
}

int main() {
	string _infix, _suffix;
	getline(cin, _infix);
	trim(_infix);
	_suffix=trans(_infix);
	_suffix.erase(_suffix.find_last_not_of(" ") + 1);
	cout << _suffix;
}
//2 + 3 * ( 7 - 4 ) + 8 / 4
//( ( 2 + 3) * 4 - ( 8 + 2 ) ) / 5
//1314 + 25.5 * 12
//-2 * (+3)
//123

//2 3 7 4 - * + 8 4 / +
//2 3 + 4 * 8 2 + - 5 /
//1314 25.5 12 * +
//-2 3 *
//123