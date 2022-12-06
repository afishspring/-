#pragma once
#include <iostream>
#include <cstring>
#define maxLength 10
using namespace std;

template<class T>
struct TreeNode {
	T data;
	TreeNode<T>* firstChild, * nextSibling;
	TreeNode(T val=0,TreeNode<T>*fc= nullptr,TreeNode<T>*ns= nullptr)
		:data(val),firstChild(fc),nextSibling(ns){}
};

template<class T>
class Tree {
public:
	Tree() { root = current = nullptr; }	//构造函数
	Tree(T ancestor);						//含参构造函数
	~Tree() { RemoveSubTree(root); }		//析构函数
	bool Root();							//令当前节点为根节点
	bool firstChild();						//转移到当前节点左子女节点
	bool nextSibling();						//转移到当前节点的右兄弟节点
	bool parent();							//转移到当前节点的父节点
	bool find(T val,bool isTrans);			//转移到值为val的节点
	bool isEmpty();							//判断树是否为空
	bool changeName(T nameBef, T nameNow);	//改变节点的值
	bool insertChild(T father,T val);		//添加左子女节点到father节点下
	bool insertSibling(T bother, T val);	//添加右兄弟节点到bother节点下
	bool destroyFamily(T father);			//解散father的所有后代，自身保留
	bool printCurrent();					//打印当前节点
	void printCurrentChild();				//打印当前节点的子女节点
	void print() {PrintAsTree(root, 1);}	//打印树结构
private:
	TreeNode<T>* root, * current;			//根节点和当前节点
	bool Find(TreeNode<T>* p, T val,bool isTrans);	//从p开始找值为val的节点
	void RemoveSubTree(TreeNode<T>* p);		//移除p的左分支
	bool FindParent(TreeNode<T>* t, TreeNode<T>* p);//从p开始找到t节点的父节点
	void PrintAsTree(TreeNode<T>* t, int deep);//前序遍历，输出树结构
};

template<class T>
inline Tree<T>::Tree(T ancestor)
{
	TreeNode<T>* _root = new TreeNode<T>(ancestor, nullptr, nullptr);
	root = current = _root;
}

template<class T>
inline bool Tree<T>::Root()
{
	if (root == nullptr) {
		current = root;
		return false;
	}
	current = root;
	return true;
}

template<class T>
inline bool Tree<T>::firstChild()
{
	if (current != nullptr & current->firstChild != nullptr) {
		current = current->firstChild;
		return true;
	}
	current = nullptr;
	return false;
}

template<class T>
inline bool Tree<T>::nextSibling()
{
	if (current != nullptr & current->nextSibling != nullptr) {
		current = current->nextSibling;
		return true;
	}
	current = nullptr;
	return false;
}

template<class T>
inline bool Tree<T>::parent()
{
	if (current == root || current == nullptr) {
		current = nullptr;
		return false;
	}
	return FindParent(root, current);
}

template<class T>
inline bool Tree<T>::FindParent(TreeNode<T>* t, TreeNode<T>* p)
{
	TreeNode<T>* temp = t->firstChild;
	while (temp != nullptr && temp != p) {//树的先根次序遍历
		if (FindParent(temp, p)) {
			return true;
		}
		temp = temp->nextSibling;
	}
	if (temp != nullptr && temp == p) {
		current = t;
		return true;
	}
	else {
		current = nullptr;
		return false;
	}
}

template<class T>
inline bool Tree<T>::isEmpty()
{
	if (root == nullptr) {
		return true;
	}
	return false;
}

template<class T>
inline bool Tree<T>::changeName(T nameBef, T nameNow)
{
	if (find(nameNow, false)) {//防止家庭成员重名，此搜索无需转移当前指针
		cout << "更改名与现有成员重复\n"; return false;
	}
	if (current->data != nameBef) {
		if (!find(nameBef,true)) {
			return false;
		}
	}
	current->data = nameNow;
	return true;
}

template<class T>
inline bool Tree<T>::find(T val,bool isTrans)
{
	if (isEmpty())
		return false;
	if (Find(root, val,isTrans))
		return true;
	else {
		current=root;//找不大就返回根节点
		return false;
	}
}

template<class T>
inline bool Tree<T>::Find(TreeNode<T>* p, T val,bool isTrans)
{
	bool res = false;//标记是否找到
	if (p->data == val) {//终止条件
		if (isTrans)//是否转移当前节点到所查询的对象
			current = p;
		res = true;
	}
	else {
		TreeNode<T>* temp = p->firstChild;//从第一个子女节点开始
		while (temp != nullptr && !(res = Find(temp, val,isTrans))) {//遍历其兄弟节点
			temp = temp->nextSibling;
		}
	}
	return res;
}

template<class T>
inline void Tree<T>::RemoveSubTree(TreeNode<T>* p)
{
	if (p != nullptr) {//后序遍历释放指针
		RemoveSubTree(p->firstChild);
		RemoveSubTree(p->nextSibling);
		delete p;
	}
}

template<class T>
inline bool Tree<T>::insertChild(T father, T val)
{
	if (find(val,false))return false;//家谱成员不重名
	if (current->data != father) {//找到父节点
		if (!find(father,true)) {
			return false;
		}
	}
	TreeNode<T>* currenttemp = current;
	if (current->firstChild == nullptr) {//父节点无子女，添加成员为左子女
		TreeNode<T>* fc = new TreeNode<T>(val, nullptr, nullptr);
		current->firstChild = fc;
		return true;
	}
	else {//否则作为长子的弟弟添加到右兄弟节点
		if (insertSibling(current->firstChild->data, val)) {
			current = currenttemp;//insertSibling会转移当前节点到长子，恢复指向父节点
			return true;
		}
		else
			return false;
	}
}

template<class T>
inline bool Tree<T>::insertSibling(T bother, T val)
{
	if (find(val,false))return false;//家谱成员不重名
	TreeNode<T>* temp = current->firstChild;
	if (current->firstChild->data != bother) {//找到兄弟节点
		if (!find(bother,true)) {
			return false;
		}
		else
			temp = current;
	}
	while (temp->nextSibling != nullptr) {//找到最右端的位置
		temp = temp->nextSibling;
	}
	TreeNode<T>* ns = new TreeNode<T>(val, nullptr, nullptr);
	temp->nextSibling = ns;//添加成员到右节点
	return true;
}

template<class T>
inline bool Tree<T>::destroyFamily(T father)
{
	if (current->data != father) {//找到父节点
		if (!find(father,true)) {
			return false;
		}
	}
	RemoveSubTree(current->firstChild);//释放所有后代节点
	current->firstChild = nullptr;//注意父节点左指针清空
	return true;
}

template<class T>
inline bool Tree<T>::printCurrent()
{
	if (current != nullptr) {
		cout << current->data;
		return true;
	}
	return false;
}

template<class T>
inline void Tree<T>::printCurrentChild()
{
	if (current != nullptr) {
		if (current->firstChild == nullptr) {
			cout << current->data << "还未有子女" << endl;
		}
		else {//打印当前节点所有子女
			TreeNode<T>*temp = current->firstChild;
			while (temp != nullptr) {
				cout << temp->data << " ";
				temp = temp->nextSibling;
			}
		}
	}
}

template<class T>
inline void Tree<T>::PrintAsTree(TreeNode<T>* t, int deep)
{
	if (t != nullptr) {//前序遍历
		for (int i = 1; i < deep; i++) {//树状修饰
			if (i == deep - 1)
				printf("+-------");
			else
				printf("|       ");
		}
		cout << t->data << endl;
		PrintAsTree(t->firstChild, deep + 1);
		PrintAsTree(t->nextSibling, deep);
	}
}

/*******************************************/
//简易自定义string类
class mystring {
public:
	mystring();//构造函数
	~mystring();//析构函数
	mystring(const mystring& str);//拷贝构造函数
	mystring& operator=(const mystring& str);//等号赋值重载
	bool operator==(const mystring& str)const { return strcmp(_str, str._str) == 0 ? true : false; }
	bool operator!=(const mystring& str)const { return strcmp(_str, str._str) != 0 ? true : false; }
	friend ostream& operator<<(ostream& os, const mystring& str){os << str._str;return os;}
	friend istream& operator>>(istream& is, const mystring& str){is >> str._str;return is;}
	int size()const { return _len; }
private:
	char* _str;
	int _len;
};

mystring::mystring() :_len(0)
{
	_str = new char[maxLength];
	_str[0] = '\0';
}

mystring::~mystring() {
	delete _str;
	_str = NULL;
}

mystring::mystring(const mystring& str)
{
	_str = new char[maxLength + 1];
	if (!_str)
	{
		cerr << "内存分配错误!\n";
		exit(1);
	}
	_len = str._len;
	strcpy(_str, str._str);
}

mystring& mystring::operator=(const mystring& str)
{
	_str = new char[maxLength + 1];
	if (!_str)
	{
		cerr << "内存分配错误!\n";
		exit(1);
	}
	_len = str._len;
	strcpy(_str, str._str);
	return *this;
}