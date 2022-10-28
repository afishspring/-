#pragma once
#include <iostream>
using namespace std;

template<class T>
struct TreeNode {
	T data;
	TreeNode<T>* firstChild, * nextSibling;
	TreeNode(T val=0,TreeNode<T>*fc=NULL,TreeNode<T>*ns=NULL)
		:data(val),firstChild(fc),nextSibling(ns){}
};

template<class T>
class Tree {
public:
	Tree() { root = current = NULL; }
	Tree(T ancestor);
	~Tree() { RemoveSubTree(root); }
	bool Root();
	bool firstChild();
	bool nextSibling();
	bool parent();
	bool find(T val);
	bool isEmpty();
	bool changeName(T nameBef, T nameNow);
	bool insertChild(T father,T val);
	bool insertSibling(T bother, T val);
	bool destroyFamily(T father);
	bool printCurrent();
	void printCurrentChild();
private:
	TreeNode<T>* root, * current;
	bool Find(TreeNode<T>* p, T val);
	void RemoveSubTree(TreeNode<T>* p);
	bool FindParent(TreeNode<T>* t, TreeNode<T>* p);
};

template<class T>
inline Tree<T>::Tree(T ancestor)
{
	TreeNode<T>* _root = new TreeNode<T>(ancestor, NULL, NULL);
	root = current = _root;
}

template<class T>
inline bool Tree<T>::Root()
{
	if (root == NULL) {
		current = root;
		return false;
	}
	current = root;
	return true;
}

template<class T>
inline bool Tree<T>::firstChild()
{
	if (current != NULL & current->firstChild != NULL) {
		current = current->firstChild;
		return true;
	}
	current = NULL;
	return false;
}

template<class T>
inline bool Tree<T>::nextSibling()
{
	if (current != NULL & current->nextSibling != NULL) {
		current = current->nextSibling;
		return true;
	}
	current = NULL;
	return false;
}

template<class T>
inline bool Tree<T>::parent()
{
	if (current == root || current == NULL) {
		current = NULL;
		return false;
	}
	return FindParent(root, current);
}

template<class T>
inline bool Tree<T>::FindParent(TreeNode<T>* t, TreeNode<T>* p)
{
	TreeNode<T>* temp = t->firstChild;
	while (temp != NULL && temp != p) {
		if (FindParent(temp, p)) {
			return true;
		}
		temp = temp->nextSibling;
	}
	if (temp != NULL && temp == p) {
		current = t;
		return true;
	}
	else {
		current = NULL;
		return false;
	}
}

template<class T>
inline bool Tree<T>::isEmpty()
{
	if (root == NULL) {
		return true;
	}
	return false;
}

template<class T>
inline bool Tree<T>::changeName(T nameBef, T nameNow)
{
	if (current->data != nameBef) {
		if (!find(nameBef)) {
			return false;
		}
	}
	current->data = nameNow;
	return true;
}

template<class T>
inline bool Tree<T>::find(T val)
{
	if (isEmpty())
		return false;
	return Find(root, val);
}

template<class T>
inline bool Tree<T>::Find(TreeNode<T>* p, T val)
{
	bool res = false;
	if (p->data == val) {
		current = p; res = true;
	}
	else {
		TreeNode<T>* temp = p->firstChild;
		while (temp != NULL && !(res = Find(temp, val))) {
			temp = temp->nextSibling;
		}
	}
	return res;
}

template<class T>
inline void Tree<T>::RemoveSubTree(TreeNode<T>* p)
{
	if (p != NULL) {
		RemoveSubTree(p->firstChild);
		RemoveSubTree(p->nextSibling);
		delete p;
	}
}

template<class T>
inline bool Tree<T>::insertChild(T father, T val)
{
	if (current->data != father) {
		if (!find(father)) {
			return false;
		}
	}
	if (current->firstChild == NULL) {
		TreeNode<T>* fc = new TreeNode<T>(val,NULL,NULL);
		current->firstChild = fc;
		return true;
	}
	else {
		return insertSibling(current->firstChild->data, val);
	}
}

template<class T>
inline bool Tree<T>::insertSibling(T bother, T val)
{
	if (current->firstChild->data != bother) {
		if (!find(bother)) {
			return false;
		}
	}
	TreeNode<T>* temp = current->firstChild;
	while (temp->nextSibling != NULL) {
		temp = temp->nextSibling;
	}
	TreeNode<T>* ns = new TreeNode<T>(val, NULL, NULL);
	temp->nextSibling = ns;
	return true;
}

template<class T>
inline bool Tree<T>::destroyFamily(T father)
{
	if (current->data != father) {
		if (!find(father)) {
			return false;
		}
	}
	RemoveSubTree(current->firstChild);
	return true;
}

template<class T>
inline bool Tree<T>::printCurrent()
{
	if (current != NULL) {
		cout << current->data;
		return true;
	}
	return false;
}

template<class T>
inline void Tree<T>::printCurrentChild()
{
	if (current != NULL) {
		if (current->firstChild == NULL) {
			cout << current->data << "还未有子女" << endl;
		}
		else {
			TreeNode<T>*temp = current->firstChild;
			while (temp != NULL) {
				cout << temp->data << " ";
				temp = temp->nextSibling;
			}
		}
	}
}
