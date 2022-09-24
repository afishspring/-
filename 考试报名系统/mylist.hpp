#include <iostream>
#include <iomanip>
using namespace std;
//student��
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
//����
template<class T>
class list;
//����ڵ���
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
//�����࣬����ͷ��㡢β���
template <class T>
class list {
public:
	list();
	list(const list<T>& _list);
	list<T>& operator= (const list<T>& _list);
	bool insert_node(int index, T val);        //���룺ֵΪval�Ľڵ㵽���Ϊindex֮��
	node<T>* del_node(int index);              //ɾ��index�Žڵ㣬��Χ1~list���ȣ�����ɾ���Ľڵ�
	void modify_node(int index, T val);        //�޸�index�Žڵ��ֵΪval
	T get_node(int index);                     //����index�Žڵ������               
	int find(int value);                       //����ֵΪvalue�Ľڵ�����
	int get_length();                          //����������
	void push_back(T val);                     //������ĩβ���
	void print();                              //��ӡ����
	~list();
private:
	node<T>* p_head;   //ͷָ�룬ָ��Ϊ�յ�ͷ���
	node<T>* p_end;    //ĩָ�룬ָ��β���ǰһ���ڵ�
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
	if (_list.p_head->next->next == nullptr) {    //_listΪ��ʱ
		node<T>* head = new node<T>;
		node<T>* end = new node<T>;
		this->p_head = head;
		this->p_end = head;
		head->next = end;
		end->next = nullptr;
		this->length = 0;
	}
	else {               //_list��Ϊ��ʱ
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
	// TODO: �ڴ˴����� return ���
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
	cout << endl << "����    ����    �Ա�    ����    �������" << endl;
	node<T>* p = this->p_head->next;
	while (p->next != nullptr) {
		cout << *p;
		p = p->next;
	}
}
