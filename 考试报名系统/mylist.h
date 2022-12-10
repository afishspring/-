#pragma once
#include <iostream>
#include <cstring>
#include <iomanip>
#define maxLength 50
using namespace std;

//student��
typedef struct student {
	int no;						//����
	char name[maxLength];		//����
	char gender[maxLength];		//�Ա�
	int age;					//����
	char type[maxLength];		//��������
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

//����
template<class T>
class list;
//����ڵ���
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
	T data;    //������Ϣ
	node* next;//���ָ��
	friend class list<T>;
};
//�����࣬����ͷ��㡢β���
template <class T>
class list {
public:
	list();									   //���캯��
	list(const list<T>& _list);				   //�������캯��
	~list() { makeEmpty(); }				   //��������
	bool insert_node(int index, T val);        //���룺ֵΪval�Ľڵ㵽���Ϊindex֮��
	bool del_node(int index);				   //ɾ��index�Žڵ㣬��Χ1~list����
	void modify_node(int index, T val);        //�޸�index�Žڵ��ֵΪval
	T get_node(int index);                     //����index�Žڵ������               
	int find(int value);                       //����ֵΪvalue�Ľڵ�����
	int get_length();                          //����������
	void push_back(T val);                     //������ĩβ���
	void print();                              //��ӡ����
private:
	void makeEmpty();
	node<T>* p_head;   //ͷָ�룬ָ��Ϊ�յ�ͷ���
	node<T>* p_end;    //ĩָ�룬ָ��β���ǰһ���ڵ�
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
	if (_list.length()==0) {    //_listΪ��ʱ���½�����
		this->p_head = new node<T>;
		this->p_end = new node<T>;
		this->p_head = this->p_end;
		p_end->next = nullptr;
		this->length = 0;
	}
	else {               //_list��Ϊ��ʱ����һ��ֵ
		if (_list.length < this->length)makeEmpty();//����ռ�����ָ����Ҫ�ͷ�
		this->p_head = new node<T>;
		node<T>* p_copy = new node<T>;
		p_head->next = p_copy;
		for (node<T>* p_ori = _list.p_head->next; p_ori->next != nullptr; p_ori = p_ori->next) {
			//����ԭʼ��������
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
		cerr << "��ų���Χ\n";
		return false;
	}
	else {
		node<T>* p_findpos = this->p_head;//����λ�õĽڵ�
		node<T>* p_new = new node<T>(val);  //������½ڵ�
		for (int i = 1; i <= index; i++) {
			p_findpos = p_findpos->next;
		}//�ҵ�����λ��index
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
		cerr << "��ų���Χ\n";
		return false;
	}
	node<T>* p_findpos = this->p_head;//ɾ��λ�õ�ǰһ�ڵ�
	node<T>* p_return = nullptr;//ɾ��λ�ýڵ�
	for (int i = 1; i < index; i++) {
		p_findpos = p_findpos->next;
	}
	p_return = p_findpos->next;
	p_findpos->next = p_return->next;
	cout << *p_return;//����ĿҪ�����
	if (index == this->length) {
		this->p_end = p_findpos;
	}//��ɾ��β��㣬��Ҫ����β���
	this->length--;
	delete p_return;
	return true;
}

template<class T>
void list<T>::modify_node(int index, T val) {
	if (index > this->length || index <= 0) {
		cerr << "��ų���Χ\n";
		return;
	}
	if (find(val.no) != -1) {//����
		cerr <<val.no<< "�ſ����Ѵ��ڣ��޷��޸�"<<index<<"�ſ�����Ϣ\n";
		return;
	}
	node<T>* p_findpos = this->p_head;//�޸�λ�õĽڵ�
	for (int i = 1; i <= index; i++) {
		p_findpos = p_findpos->next;
	}
	p_findpos->data = val;
}

template<class T>
T list<T>::get_node(int index)
{
	if (index > this->length || index <= 0) {
		cerr << "��ų���Χ\n";
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
	//��ͷ������β
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
	//��β���ָ��������
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
	cout << endl << "����    ����    �Ա�    ����    �������" << endl;
	if (this->p_head == this->p_end) {
		cout << "ϵͳ������\n";
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
	//��ͷ��ʼ��һ�ͷ�
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
