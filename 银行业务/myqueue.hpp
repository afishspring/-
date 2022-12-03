#pragma once
using namespace std;
template<class T>
class queue {
public:
	queue(int sz);
	~queue() { delete[]elements; }
	bool push(const T& val);
	bool pop();
	T front()const;	//返回队列首元素
	void clear() { p_front = p_rear = 0; }
	bool isEmpty()const { return (length==0) ? true : false; }
	bool isFull()const { return (length==maxSize) ? true : false; }
	int size()const { return length; }
	//队列按其出列规则输出，用于调试
	friend ostream& operator <<(ostream& os, queue<T>& rhs) {
		for (int i = rhs.p_front; i != rhs.p_rear; i = (i + 1) % rhs.maxSize) {
			os << rhs.elements[i] << " ";
		}
		os << endl;
		return os;
	}
private:
	int p_rear, p_front;	//队列尾指针，头指针
	T* elements;			//存放队列元素
	int maxSize;			//队列最大大小
	int length = 0;			//队列当前大小
};

template<class T>
queue<T>::queue(int sz) :p_front(0), p_rear(0), maxSize(sz) {
	elements = new T[maxSize];
	if (elements == nullptr) {
		cerr << "存储分配失败" << endl;
		exit(-1);
	}
}
//入队列
template<class T>
bool queue<T>::push(const T& val) {
	if (isFull()) {
		return false;
	}
	elements[p_rear] = val;
	p_rear = (p_rear + 1) % maxSize;
	length++;
	return true;
}
//出队列
template<class T>
bool queue<T>::pop() {
	if (isEmpty()) {
		return false;
	}
	p_front = (p_front + 1) % maxSize;
	length--;
	return true;
}
//队列头元素
template<class T>
T queue<T>::front()const {
	if (isEmpty()) {
		return elements[0];
	}
	return elements[p_front];
}