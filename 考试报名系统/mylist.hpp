#include <iostream>
#include <iomanip>
using namespace std;
//student类
typedef struct student {
	int no;
	string name;
	string gender;
	int age;
	string type;
	student():no(-1),age(-1) {}
	friend istream& operator>>(istream& is, student& rhs) {
		is >> rhs.no >> rhs.name >> rhs.gender>> rhs.age >> rhs.type;
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
	node():next(nullptr){}
	node(T val):data(val),next(nullptr){}
	friend ostream& operator<<(ostream& os, const node& rhs) {
		os << rhs.data;
		return os;
	}
private:
	T data;
	node* next;
	friend class list<T>;
};
//链表类，附有头结点、尾结点
template <class T>
class list {
public:
	list();
	list(const list<T>& _list);
	list<T>& operator= (const list<T>& _list);
	bool insert_node(int index, T val);        //插入：值为val的节点到序号为index之后
	node<T>* del_node(int index);              //删除index号节点，范围1~list长度，返回删除的节点
	void modify_node(int index, T val);        //修改index号节点的值为val
	T get_node(int index);                     //返回index号节点的数据               
	int find(int value);                       //返回值为value的节点的序号
	int get_length();                          //返回链表长度
	void push_back(T val);                     //在链表末尾添加
	void print();                              //打印链表
	~list();
private:
	node<T>* p_head;   //头指针，指向为空的头结点
	node<T>* p_end;    //末指针，指向尾结点前一个节点
	int length;
};

template<class T>
list<T>::list()
{
	node<T>* head = new node<T>;
	node<T>* end = new node<T>;
	this->p_head = head;
	this->p_end = head;
	head->next = end;
	end->next = nullptr;
	this->length = 0;
}

template<class T>
list<T>::list(const list<T>& _list)
{
	if (_list.p_head->next->next == nullptr) {    //_list为空时
		node<T>* head = new node<T>;
		node<T>* end = new node<T>;
		this->p_head = head;
		this->p_end = head;
		head->next = end;
		end->next = nullptr;
		this->length = 0;
	}
	else {               //_list不为空时
		this->p_head = new node<T>;
		node<T>* p_copy = new node<T>;
		p_head->next = p_copy;
		for (node<T>* p_ori = _list.p_head->next; p_ori->next != nullptr; p_ori = p_ori->next) {
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
list<T>& list<T>::operator=(const list<T>& _list)
{
	// TODO: 在此处插入 return 语句
}

template<class T>
bool list<T>::insert_node(int index, T val)
{
	if (index > this->length || index < 0) {
		cerr << "index out of range";
		return false;
	}
	else {
		node<T>* p_findpos = this->p_head;
		node<T>* p_new = new node<T>;
		for (int i = 1; i <= index; i++) {
			p_findpos = p_findpos->next;
		}
		p_new->data = val;
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
node<T>* list<T>::del_node(int index)
{
	if (index > this->length || index <= 0) {
		cerr << "index out of range";
		return nullptr;
	}
	node<T>* p_findpos = this->p_head;
	node<T>* p_temp = nullptr;
	node<T>* p_return = nullptr;
	for (int i = 1; i < index; i++) {
		p_findpos = p_findpos->next;
	}
	p_temp = p_findpos->next->next;
	p_return = p_findpos->next;
	delete p_findpos->next;
	p_findpos->next = p_temp;
	if (index == this->length) {
		this->p_end = p_findpos;
	}
	this->length--;
	return p_return;
}

template<class T>
void list<T>::modify_node(int index, T val) {
	if (index > this->length || index <= 0) {
		cerr << "index out of range";
		return;
	}
	node<T>* p_findpos = this->p_head;
	node<T>* p_temp = nullptr;
	for (int i = 1; i <= index; i++) {
		p_findpos = p_findpos->next;
	}
	p_findpos->data = val;
}

template<class T>
T list<T>::get_node(int index)
{
	if (index > this->length || index <= 0) {
		cerr << "index out of range";
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
	node<T>* p_new = new node<T>;
	p_new->data = val;
	p_new->next = this->p_end->next;
	this->p_end->next = p_new;
	this->p_end = p_new;
	this->length++;
}

template<class T>
list<T>::~list()
{
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

template<class T>
inline void list<T>::print()
{
	if (this->p_head->next == this->p_end) {
		cout << "list is empty";
		return;
	}
	cout << endl << "考号    姓名    性别    年龄    报考类别" << endl;
	node<T>* p = this->p_head->next;
	while (p->next != nullptr) {
		cout << *p;
		p = p->next;
	}
}
