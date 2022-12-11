#include <iostream>
#include <iomanip>
using namespace std;
//����
template<class T>
class list;
//����ڵ���
template <class T>
class node {
public:
	node():next(nullptr){}
	node(T val) :data(val), next(nullptr) {}
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
	list();  //���캯��
	list(const list<T>& _list);//�������캯��
	~list();//��������
	//�α���
	class iterator {
	public:
		friend class list<T>;
		explicit iterator(node<T>* p = 0) {
			current = p;
		}
		iterator(const iterator& other) {
			current = other.current;
		}
		iterator& operator++() {//ǰ����
			current = current->next;
			return *this;
		}
		iterator operator++(int) {//������
			iterator temp = *this;
			++(*this);
			return temp;
		}
		node<T>* operator->() {
			return current;
		}
		T& operator*() {//ȡ��ַ����
			return current->data;
		}
		bool operator == (const iterator& rhs)const {//��������
			return current == rhs.current;
		}
		bool operator!=(const iterator& rhs)const {//����������
			return !(*this == rhs);
		}
		operator node<T>* () {//�������
			return current;
		}
	private:
		node<T>* current;
	}; 
	iterator begin()const { return iterator(p_head->next); }//����βԪ��
	iterator end()const { return iterator(p_end); }//����ͷԪ��
	bool del_node(int index);              //ɾ��index�Žڵ㣬��Χ1~list����
	int get_length();                          //����������
	void push_back(T val);                     //������ĩβ���
	void print();                              //��ӡ����
	void makeEmpty();
private:
	node<T>* p_head;   //ͷָ�룬ָ��Ϊ�յ�ͷ���
	node<T>* p_end;    //ĩָ�룬ָ��β���ǰһ���ڵ�
	int length;        //������
};

template<class T>
list<T>::list()
{
	this->p_head = new node<T>;
	this->p_end = new node<T>;
	p_end = p_head;
	this->length = 0;
}

template<class T>
list<T>::list(const list<T>& _list)
{
	if (_list.p_head->next->next==nullptr) {    //_listΪ��ʱ
		this->p_head = new node<T>;
		this->p_end = new node<T>;
		p_end = p_head;
		this->length = 0;
	}
	else {               //_list��Ϊ��ʱ
		this->p_head = new node<T>;
		node<T>* p_copy = new node<T>;
		p_head->next = p_copy;
		//����ԭ����
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
list<T>::~list() {
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

template<class T>
bool list<T>::del_node(int index)
{
	if (index > this->length || index <= 0) {
		cerr << "��ų���Χ��\n";
		return false;
	}
	node<T>* p_findpos = this->p_head;//�ҵ�ɾ���ڵ��ǰһλ
	node<T>* p_return = nullptr;      //Ҫɾ���Ľڵ�
	for (int i = 1; i < index; i++) {
		p_findpos = p_findpos->next;
	}
	p_return = p_findpos->next;
	p_findpos->next = p_return->next;//����ָ��ָ��
	delete p_return;//�ͷ�ɾ���Ľڵ�
	if (index == this->length) {//��ɾ������β��㣬����βָ��
		this->p_end = p_findpos;
	}
	this->length--;
	return true;
}

template<class T>
int list<T>::get_length()
{
	return this->length;
}

template<class T>
void list<T>::push_back(T val)
{
	node<T>* p_new = new node<T>(val);
	this->p_end->next = p_new;
	this->p_end = p_new;
	this->length++;
}

template<class T>
inline void list<T>::print()
{
	if (length==0) {
		cout << "NULL";
		return;
	}
	node<T>* p = this->p_head->next;
	while (p!= nullptr) {
		cout << *p;
		if (p!=this->p_end){//���һ��Ԫ������޿ո�
			cout << " ";
		}
		p = p->next;
	}
	cout << endl;
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
	//��պ����½���������
	p_head = new node<T>;
	p_end = new node<T>;
	p_end = p_head;
}