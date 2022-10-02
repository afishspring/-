#pragma once
#include <iostream>
using namespace std;
const int stackIncreament = 20;

template<class T>
class stack {
public:
	stack(int sz);
	stack(stack& s);
	stack<T>& operator= (stack<T>& _stack);
	~stack() { delete[]elements; }
	void push_back(const T& x);
	bool pop_back();
	T top();
	bool isEmpty()const { return p_top == -1 ? true : false; }
	bool isFull()const { return p_top == maxSize - 1 ? true : false; }
	int size()const { return p_top + 1; }
	void clear() { p_top = -1; }
	friend ostream& operator<<(ostream& os, const stack& rhs) {
		os << rhs;
	}
	T operator[](const int index) {
		if (index < 0 || index >= maxSize) {
			cerr << "·ÃÎÊÕ»Ô½½ç" << endl;
			exit(-1);
		}
		return elements[index];
	}
	void overflowProcess();
private:
	T* elements;
	int p_top;
	int maxSize;
};


template<class T>
inline stack<T>::stack(int sz) :p_top(-1), maxSize(sz)
{
	elements = new T[maxSize];
	if (elements == nullptr) {
		cerr << "´æ´¢·ÖÅäÊ§°Ü" << endl;
		exit(-1);
	}
}
template<class T>
inline stack<T>::stack(stack& s)
{
	this->elements = new T(*(s.elements));
}

template<class T>
inline stack<T>& stack<T>::operator=(stack<T>& _stack)
{
	this->~stack();
	elements = new T[_stack.maxSize];
	for (int i = 0; i < _stack.maxSize; i++) {
		this->elements[i] = _stack[i];
	}

	this->p_top = _stack.p_top;
	return *this;
}

template<class T>
inline void stack<T>::push_back(const T& x)
{
	if (isFull()) {
		overflowProcess();
	}
	elements[++p_top] = x;
}

template<class T>
inline bool stack<T>::pop_back()
{
	if (isEmpty()) {
		return false;
	}
	elements[p_top--];
	return true;
}

template<class T>
inline T stack<T>::top() {
	if (isEmpty()) {
		return elements[0];
	}
	return elements[p_top];
}

template<class T>
inline void stack<T>::overflowProcess()
{
	T* newArray = new T[maxSize + stackIncreament];
	if (newArray == nullptr) {
		cerr << "´æ´¢·ÖÅäÊ§°Ü" << endl;
		exit(-1);
	}
	for (int i = 0; i <= p_top; i++) {
		newArray[i] = elements[i];
	}
	maxSize += stackIncreament;
	delete[] elements;
	elements = newArray;
}