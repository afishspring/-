#pragma once
#include <iostream>
#include <cstring>
using namespace std;
const int maxLength = 100;//字符串的最大长度

class mystring {
public:
    mystring();
    mystring(const char* str);
    ~mystring();
    mystring(const mystring& str);

    mystring& operator=(const mystring& str);
    mystring& operator+=(const mystring& str);
    mystring& operator+=(const char& ch);
    friend mystring operator+(const mystring& str1, const mystring& str2);
    friend mystring operator+(const mystring& str1, const char&ch);
    bool operator==(const mystring& str)const { return strcmp(_str, str._str) == 0 ? true : false; }
    bool operator!=(const mystring& str)const { return strcmp(_str, str._str) != 0 ? true : false; }
    char operator[](int index){ return _str[index]; }
    friend ostream& operator<<(ostream& os, const mystring& str);
    friend istream& operator>>(istream& is, const mystring& str);
    int size()const { return _len; }
    void clear();
    mystring& subString(int position, int len);
    mystring& erase(int pos);
private:
    char* _str;
    int _len;
};

mystring::mystring() :_len(0)
{
    _str = new char[1];
    _str[0] = '\0';
}

mystring::mystring(const char* str)
{
    _str = new char[maxLength + 1];
    if (!_str)
    {
        cerr << "内存分配错误!\n";
        exit(1);
    }
    _len = strlen(str);
    strcpy(_str, str);
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

mystring& mystring::operator+=(const mystring& str)
{
    char* temp = _str;//将*this->ch赋给temp
    _len = _len + str._len;//*this->curLen为两字符串的总长度
    _str = new char[_len + 1];
    if (!_str)
    {
        cerr << "内存分配错误!\n";
        exit(1);
    }
    strcpy(_str, temp);
    strcat(_str, str._str);
    delete[] temp;
    return *this;
}

mystring& mystring::operator+=(const char& ch)
{
    char* temp = new char[_len + 2];
    if (!temp)
    {
        cerr << "内存分配错误!\n";
        exit(1);
    }
    strcpy(temp, _str);
    temp[_len] = ch;
    temp[_len + 1] = '\0';
    _len++;
    _str = new char[_len + 1];
    if (!_str)
    {
        cerr << "内存分配错误!\n";
        exit(1);
    }
    strcpy(_str, temp);
    delete[]temp;
    return *this;
}

mystring operator+(const mystring& str1, const mystring& str2)
{
    int len = str1._len + str2._len;//两个长度加起来
    char* str0 = new char[len + 1];
    if (!str0)
    {
        cerr << "内存分配错误!\n";
        exit(1);
    }
    strcpy(str0, str1._str);
    strcat(str0, str2._str);
    mystring str(str0);
    delete[] str0;
    return str;
}

mystring operator+(const mystring& str1, const char& ch)
{
    int len = str1._len +1;//两个长度加起来
    char* str0 = new char[len + 1];
    if (!str0)
    {
        cerr << "内存分配错误!\n";
        exit(1);
    }
    strcpy(str0, str1._str);
    str0[len - 1] = ch;
    str0[len] = '\0';
    mystring str(str0);
    delete[] str0;
    return str;
}

ostream& operator<<(ostream& os, const mystring& str)
{
    os << str._str;
    return os;
}

istream& operator>>(istream& is, const mystring& str)
{
    is >> str._str;
    return is;
}

void mystring::clear()
{
    for (int i = 0; i < _len; i++)
        _str[i] = '\0';
    _len = 0;
}

mystring& mystring::subString(int position, int len)
{
    if (position < 0 || position + len - 1 >= maxLength || len < 0) //超范围，不取任何子串
    {
        _len = 0;
        _str[0] = '\0';
    }
    else
    {
        if (position + len - 1 >= _len)//子串长度太长，就截取到尾零
            len = _len - position;
        _len = len;
        for (int i = 0, j = position; i < len; i++, j++)
            _str[i] = _str[j];
        _str[len] = '\0';
    }
    return *this;
}

mystring& mystring::erase(int pos)
{
    if (pos < 0 || pos > _len) {
        cerr << "清除失败！\n";
    }
    for (int i = pos; i < _len; i++) {
        _str[i] = _str[i + 1];
    }
    return *this;
}