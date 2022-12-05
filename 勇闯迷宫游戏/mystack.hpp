#pragma once
#include <iostream>
#include <assert.h>
using namespace std;
const int stackIncreament = 20;

struct point {
	int x, y, dire;//��ǰλ�ã���һ״̬����λ�õķ���
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
	stack(int sz);							//���캯��
	stack(stack& s);						//�������캯��
	stack<T>& operator= (stack<T>& _stack);	//ͬ�ำֵ����
	~stack() { delete[]elements; }			//��������
	void push_back(const T& x);				//��ջ
	bool pop_back();						//��ջ
	T top();								//����ջ��Ԫ��
	bool isEmpty()const{ return p_top == -1 ? true : false; }
	bool isFull()const { return p_top == maxSize - 1 ? true : false; }
	int size()const { return p_top + 1; }
	void clear() { p_top = -1; }
	friend ostream& operator<<(ostream& os, const stack& rhs) {
		os << rhs;
	}
	T operator[](const int index) {
		if (index<0 || index>=maxSize) {
			cerr << "����ջԽ��" << endl;
			exit(-1);
		}
		return elements[index];
	}
	void overflowProcess();//���ʱ��չջ�ռ�
private:
	T* elements;		//ջ�Ĵ洢
	int p_top;			//ջ��ָ��
	int maxSize;		//ջ��ǰ���ֵ
};


template<class T>
inline stack<T>::stack(int sz) :p_top(-1), maxSize(sz)
{
	elements = new T[maxSize];
	if (elements == nullptr) {
		cerr << "�洢����ʧ��" << endl;
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
		cerr << "�洢����ʧ��" << endl;
		exit(-1);
	}
	for (int i = 0; i <= p_top; i++) {
		newArray[i] = elements[i];
	}
	maxSize += stackIncreament;
	delete[] elements;
	elements = newArray;
}