#pragma once
#include <iostream>
#include <cstring>
#include <iomanip>
#define maxLength 50
using namespace std;

//student类
typedef struct student {
	int no;						//考号
	char name[maxLength];		//姓名
	char gender[maxLength];		//性别
	int age;					//年龄
	char type[maxLength];		//报考类型
	friend istream& operator>>(istream& is, student& rhs) {
		is >> rhs.no>> rhs.name >> rhs.gender>> rhs.age>> rhs.type;
		return is;
	}
	friend ostream& operator<<(ostream& os, const student& rhs) {
		os << setiosflags(ios::left);
		os << setw(8) << rhs.no
			<< setw(8) << rhs.name
			<< setw(8) << rhs.gender
			<< setw(8) << rhs.age
			<< setw(8) << rhs.type << endl;
		return os;
	}
}student;

//声明
template<class T>
class list;
//链表节点类
template <class T>
class node {
public:
	node():next(nullptr) {}
	node(T val):data(val),next(nullptr){}
	friend ostream& operator<<(ostream& os, const node& rhs) {
		os << rhs.data;
		return os;
	}
private:
	T data;    //考生信息
	node* next;//后继指针
	friend class list<T>;
};
//链表类，附有头结点、尾结点
template <class T>
class list {
public:
	list();									   //构造函数
	list(const list<T>& _list);				   //拷贝构造函数
	~list() { makeEmpty(); }				   //析构函数
	bool insert_node(int index, T val);        //插入：值为val的节点到序号为index之后
	bool del_node(int index);				   //删除index号节点，范围1~list长度
	void modify_node(int index, T val);        //修改index号节点的值为val
	T get_node(int index);                     //返回index号节点的数据               
	int find(int value);                       //返回值为value的节点的序号
	int get_length();                          //返回链表长度
	void push_back(T val);                     //在链表末尾添加
	void print();                              //打印链表
private:
	void makeEmpty();
	node<T>* p_head;   //头指针，指向为空的头结点
	node<T>* p_end;    //末指针，指向尾结点前一个节点
	int length;
};

template<class T>
list<T>::list()
{
	this->p_head = new node<T>;
	this->p_end = new node<T>;
	this->p_head = this->p_end;
	p_end->next = nullptr;
	this->length = 0;
}

template<class T>
list<T>::list(const list<T>& _list)
{
	if (_list.length()==0) {    //_list为空时，新建链表
		this->p_head = new node<T>;
		this->p_end = new node<T>;
		this->p_head = this->p_end;
		p_end->next = nullptr;
		this->length = 0;
	}
	else {               //_list不为空时，逐一赋值
		if (_list.length < this->length)makeEmpty();//链表空间过大的指针需要释放
		this->p_head = new node<T>;
		node<T>* p_copy = new node<T>;
		p_head->next = p_copy;
		for (node<T>* p_ori = _list.p_head->next; p_ori->next != nullptr; p_ori = p_ori->next) {
			//遍历原始数据链表
			p_copy.data = p_ori.data;
			p_copy->next = new node<T>;
			this->p_end = p_copy;
			p_copy = p_copy->next;
		}
		p_copy->next = nullptr;
		this->length = _list.length;
	}
}

template<class T>
bool list<T>::insert_node(int index, T val)
{
	if (index > this->length || index < 0) {
		cerr << "序号超范围\n";
		return false;
	}
	else {
		node<T>* p_findpos = this->p_head;//插入位置的节点
		node<T>* p_new = new node<T>(val);  //插入的新节点
		for (int i = 1; i <= index; i++) {
			p_findpos = p_findpos->next;
		}//找到插入位置index
		p_new->next = p_findpos->next;
		p_findpos->next = p_new;
		this->length++;
		if (index == this->length) {
			this->p_end = p_new;
		}
	}
	return true;
}

template<class T>
bool list<T>::del_node(int index)
{
	if (index > this->length || index <= 0) {
		cerr << "序号超范围\n";
		return false;
	}
	node<T>* p_findpos = this->p_head;//删除位置的前一节点
	node<T>* p_return = nullptr;//删除位置节点
	for (int i = 1; i < index; i++) {
		p_findpos = p_findpos->next;
	}
	p_return = p_findpos->next;
	p_findpos->next = p_return->next;
	cout << *p_return;//按项目要求输出
	if (index == this->length) {
		this->p_end = p_findpos;
	}//若删除尾结点，需要更新尾结点
	this->length--;
	delete p_return;
	return true;
}

template<class T>
void list<T>::modify_node(int index, T val) {
	if (index > this->length || index <= 0) {
		cerr << "序号超范围\n";
		return;
	}
	if (find(val.no) != -1) {//查重
		cerr <<val.no<< "号考生已存在，无法修改"<<index<<"号考生信息\n";
		return;
	}
	node<T>* p_findpos = this->p_head;//修改位置的节点
	for (int i = 1; i <= index; i++) {
		p_findpos = p_findpos->next;
	}
	p_findpos->data = val;
}

template<class T>
T list<T>::get_node(int index)
{
	if (index > this->length || index <= 0) {
		cerr << "序号超范围\n";
	}
	node<T>* p_findpos = this->p_head;
	for (int i = 1; i <= index; i++) {
		p_findpos = p_findpos->next;
	}
	return p_findpos->data;
}

template<class T>
int list<T>::find(int value)
{
	node<T>* p_findpos = this->p_head->next;
	//从头遍历到尾
	for (int i = 1; i <= this->length; i++) {
		if (p_findpos->data.no == value) {
			return i;
		}
		p_findpos = p_findpos->next;
	}
	return -1;
}

template<class T>
int list<T>::get_length()
{
	return this->length;
}

template<class T>
void list<T>::push_back(T val)
{
	//用尾结点指针做辅助
	node<T>* p_new = new node<T>;
	p_new->data = val;
	p_new->next = nullptr;
	this->p_end->next = p_new;
	this->p_end = p_new;
	this->length++;
}

template<class T>
inline void list<T>::print()
{
	cout << endl << "考号    姓名    性别    年龄    报考类别" << endl;
	if (this->p_head == this->p_end) {
		cout << "系统无数据\n";
		return;
	}
	node<T>* p = this->p_head->next;
	while (p!= nullptr) {
		cout << *p;
		p = p->next;
	}
}

template<class T>
inline void list<T>::makeEmpty()
{
	//从头开始逐一释放
	node<T>* p1 = this->p_head;
	node<T>* p2 = p1->next;
	while (p2 != nullptr) {
		delete p1;
		p1 = p2;
		p2 = p2->next;
	}
	delete p1;
	this->length = 0;
	this->p_head = nullptr;
}
