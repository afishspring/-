#include <iostream>
#include <iomanip>
using namespace std;
//声明
template<class T>
class list;
//链表节点类
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

//链表类，附有头结点、尾结点
template <class T>
class list {
public:
	list();  //构造函数
	list(const list<T>& _list);//拷贝构造函数
	~list();//析构函数
	//游标类
	class iterator {
	public:
		friend class list<T>;
		explicit iterator(node<T>* p = 0) {
			current = p;
		}
		iterator(const iterator& other) {
			current = other.current;
		}
		iterator& operator++() {//前自增
			current = current->next;
			return *this;
		}
		iterator operator++(int) {//后自增
			iterator temp = *this;
			++(*this);
			return temp;
		}
		node<T>* operator->() {
			return current;
		}
		T& operator*() {//取地址内容
			return current->data;
		}
		bool operator == (const iterator& rhs)const {//等于重载
			return current == rhs.current;
		}
		bool operator!=(const iterator& rhs)const {//不等于重载
			return !(*this == rhs);
		}
		operator node<T>* () {//外加括号
			return current;
		}
	private:
		node<T>* current;
	}; 
	iterator begin()const { return iterator(p_head->next); }//链表尾元素
	iterator end()const { return iterator(p_end); }//链表头元素
	bool del_node(int index);              //删除index号节点，范围1~list长度
	int get_length();                          //返回链表长度
	void push_back(T val);                     //在链表末尾添加
	void print();                              //打印链表
	void makeEmpty();
private:
	node<T>* p_head;   //头指针，指向为空的头结点
	node<T>* p_end;    //末指针，指向尾结点前一个节点
	int length;        //链表长度
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
	if (_list.p_head->next->next==nullptr) {    //_list为空时
		this->p_head = new node<T>;
		this->p_end = new node<T>;
		p_end = p_head;
		this->length = 0;
	}
	else {               //_list不为空时
		this->p_head = new node<T>;
		node<T>* p_copy = new node<T>;
		p_head->next = p_copy;
		//遍历原链表
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

template<class T>
bool list<T>::del_node(int index)
{
	if (index > this->length || index <= 0) {
		cerr << "序号超范围！\n";
		return false;
	}
	node<T>* p_findpos = this->p_head;//找到删除节点的前一位
	node<T>* p_return = nullptr;      //要删除的节点
	for (int i = 1; i < index; i++) {
		p_findpos = p_findpos->next;
	}
	p_return = p_findpos->next;
	p_findpos->next = p_return->next;//更新指针指向
	delete p_return;//释放删除的节点
	if (index == this->length) {//若删除的是尾结点，更新尾指针
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
		if (p!=this->p_end){//最后一个元素输出无空格
			cout << " ";
		}
		p = p->next;
	}
	cout << endl;
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
	//清空后重新建立空链表
	p_head = new node<T>;
	p_end = new node<T>;
	p_end = p_head;
}