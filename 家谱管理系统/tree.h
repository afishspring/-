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
	Tree() { root = current = nullptr; }	//���캯��
	Tree(T ancestor);						//���ι��캯��
	~Tree() { RemoveSubTree(root); }		//��������
	bool Root();							//�ǰ�ڵ�Ϊ���ڵ�
	bool firstChild();						//ת�Ƶ���ǰ�ڵ�����Ů�ڵ�
	bool nextSibling();						//ת�Ƶ���ǰ�ڵ�����ֵܽڵ�
	bool parent();							//ת�Ƶ���ǰ�ڵ�ĸ��ڵ�
	bool find(T val,bool isTrans);			//ת�Ƶ�ֵΪval�Ľڵ�
	bool isEmpty();							//�ж����Ƿ�Ϊ��
	bool changeName(T nameBef, T nameNow);	//�ı�ڵ��ֵ
	bool insertChild(T father,T val);		//�������Ů�ڵ㵽father�ڵ���
	bool insertSibling(T bother, T val);	//������ֵܽڵ㵽bother�ڵ���
	bool destroyFamily(T father);			//��ɢfather�����к����������
	bool printCurrent();					//��ӡ��ǰ�ڵ�
	void printCurrentChild();				//��ӡ��ǰ�ڵ����Ů�ڵ�
	void print() {PrintAsTree(root, 1);}	//��ӡ���ṹ
private:
	TreeNode<T>* root, * current;			//���ڵ�͵�ǰ�ڵ�
	bool Find(TreeNode<T>* p, T val,bool isTrans);	//��p��ʼ��ֵΪval�Ľڵ�
	void RemoveSubTree(TreeNode<T>* p);		//�Ƴ�p�����֧
	bool FindParent(TreeNode<T>* t, TreeNode<T>* p);//��p��ʼ�ҵ�t�ڵ�ĸ��ڵ�
	void PrintAsTree(TreeNode<T>* t, int deep);//ǰ�������������ṹ
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
	while (temp != nullptr && temp != p) {//�����ȸ��������
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
	if (find(nameNow, false)) {//��ֹ��ͥ��Ա����������������ת�Ƶ�ǰָ��
		cout << "�����������г�Ա�ظ�\n"; return false;
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
		current=root;//�Ҳ���ͷ��ظ��ڵ�
		return false;
	}
}

template<class T>
inline bool Tree<T>::Find(TreeNode<T>* p, T val,bool isTrans)
{
	bool res = false;//����Ƿ��ҵ�
	if (p->data == val) {//��ֹ����
		if (isTrans)//�Ƿ�ת�Ƶ�ǰ�ڵ㵽����ѯ�Ķ���
			current = p;
		res = true;
	}
	else {
		TreeNode<T>* temp = p->firstChild;//�ӵ�һ����Ů�ڵ㿪ʼ
		while (temp != nullptr && !(res = Find(temp, val,isTrans))) {//�������ֵܽڵ�
			temp = temp->nextSibling;
		}
	}
	return res;
}

template<class T>
inline void Tree<T>::RemoveSubTree(TreeNode<T>* p)
{
	if (p != nullptr) {//��������ͷ�ָ��
		RemoveSubTree(p->firstChild);
		RemoveSubTree(p->nextSibling);
		delete p;
	}
}

template<class T>
inline bool Tree<T>::insertChild(T father, T val)
{
	if (find(val,false))return false;//���׳�Ա������
	if (current->data != father) {//�ҵ����ڵ�
		if (!find(father,true)) {
			return false;
		}
	}
	TreeNode<T>* currenttemp = current;
	if (current->firstChild == nullptr) {//���ڵ�����Ů����ӳ�ԱΪ����Ů
		TreeNode<T>* fc = new TreeNode<T>(val, nullptr, nullptr);
		current->firstChild = fc;
		return true;
	}
	else {//������Ϊ���ӵĵܵ���ӵ����ֵܽڵ�
		if (insertSibling(current->firstChild->data, val)) {
			current = currenttemp;//insertSibling��ת�Ƶ�ǰ�ڵ㵽���ӣ��ָ�ָ�򸸽ڵ�
			return true;
		}
		else
			return false;
	}
}

template<class T>
inline bool Tree<T>::insertSibling(T bother, T val)
{
	if (find(val,false))return false;//���׳�Ա������
	TreeNode<T>* temp = current->firstChild;
	if (current->firstChild->data != bother) {//�ҵ��ֵܽڵ�
		if (!find(bother,true)) {
			return false;
		}
		else
			temp = current;
	}
	while (temp->nextSibling != nullptr) {//�ҵ����Ҷ˵�λ��
		temp = temp->nextSibling;
	}
	TreeNode<T>* ns = new TreeNode<T>(val, nullptr, nullptr);
	temp->nextSibling = ns;//��ӳ�Ա���ҽڵ�
	return true;
}

template<class T>
inline bool Tree<T>::destroyFamily(T father)
{
	if (current->data != father) {//�ҵ����ڵ�
		if (!find(father,true)) {
			return false;
		}
	}
	RemoveSubTree(current->firstChild);//�ͷ����к���ڵ�
	current->firstChild = nullptr;//ע�⸸�ڵ���ָ�����
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
			cout << current->data << "��δ����Ů" << endl;
		}
		else {//��ӡ��ǰ�ڵ�������Ů
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
	if (t != nullptr) {//ǰ�����
		for (int i = 1; i < deep; i++) {//��״����
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
//�����Զ���string��
class mystring {
public:
	mystring();//���캯��
	~mystring();//��������
	mystring(const mystring& str);//�������캯��
	mystring& operator=(const mystring& str);//�ȺŸ�ֵ����
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
		cerr << "�ڴ�������!\n";
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
		cerr << "�ڴ�������!\n";
		exit(1);
	}
	_len = str._len;
	strcpy(_str, str._str);
	return *this;
}