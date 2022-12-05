#pragma once
#include <iostream>
#include <assert.h>
using namespace std;
const int stackIncreament = 20;

struct point {
	int x, y, dire;//当前位置，上一状态到此位置的方向
	friend ostream& operator<<(ostream& os, const point& rhs) {
		os << "<" << rhs.x << "," << rhs.y << ">";
		return os;
	}
	point& operator=(const point& p) {
		this->x = p.x;
		this->y = p.y;
		this->dire = p.dire;
		return *this;
	}
};

template<class T>
class stack {
public:
	stack(int sz);							//构造函数
	stack(stack& s);						//拷贝构造函数
	stack<T>& operator= (stack<T>& _stack);	//同类赋值重载
	~stack() { delete[]elements; }			//析构函数
	void push_back(const T& x);				//入栈
	bool pop_back();						//出栈
	T top();								//返回栈顶元素
	bool isEmpty()const{ return p_top == -1 ? true : false; }
	bool isFull()const { return p_top == maxSize - 1 ? true : false; }
	int size()const { return p_top + 1; }
	void clear() { p_top = -1; }
	friend ostream& operator<<(ostream& os, const stack& rhs) {
		os << rhs;
	}
	T operator[](const int index) {
		if (index<0 || index>=maxSize) {
			cerr << "访问栈越界" << endl;
			exit(-1);
		}
		return elements[index];
	}
	void overflowProcess();//溢出时扩展栈空间
private:
	T* elements;		//栈的存储
	int p_top;			//栈顶指针
	int maxSize;		//栈当前最大值
};


template<class T>
inline stack<T>::stack(int sz) :p_top(-1), maxSize(sz)
{
	elements = new T[maxSize];
	if (elements == nullptr) {
		cerr << "存储分配失败" << endl;
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
	for (int i = 0; i <_stack.maxSize; i++) {
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
	assert(!isEmpty());
	return elements[p_top];
}

template<class T>
inline void stack<T>::overflowProcess()
{
	T* newArray = new T[maxSize + stackIncreament];
	if (newArray == nullptr) {
		cerr << "存储分配失败" << endl;
		exit(-1);
	}
	for (int i = 0; i <= p_top; i++) {
		newArray[i] = elements[i];
	}
	maxSize += stackIncreament;
	delete[] elements;
	elements = newArray;
}