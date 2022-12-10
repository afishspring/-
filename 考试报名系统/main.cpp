#include <iostream>
#include "mylist.h"
using namespace std;

bool input(list<student>&_l,int num) {
    student temp;
    for (int i = 0; i < num; i++) {
        cin >> temp;
        if (cin.fail()) {
            cerr << "输入错误\n";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            return false;
        }
        if (_l.find(temp.no)!=-1) {
            cerr << temp.no << "号考生已存在\n";
            i--;
            continue;
        }
        _l.push_back(temp);
    }
    return true;
}

void insertData(list<student>& _l) {
    int pos;
    student newStudent;
    cout << "请输入你要插入的考生的位置：";
    cin >> pos;
    if (cin.fail()||pos>_l.get_length()+1&& _l.get_length()!=0||pos<=0) {
        cerr << "插入位置只能在"<<1<<"~"<< _l.get_length()+1<<"之间\n";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        return;
    }
    else if (_l.get_length() == 0 && pos != 1) {
        cerr << "系统数据为空时，插入位置为1\n";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        return;
    }
    cout << "请依次输入要插入的考生的考号，姓名，性别，年龄及报考类别!" << endl;
    cin >> newStudent;
    if (cin.fail()) {
        cerr << "输入错误\n";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        return;
    }
    if (_l.find(newStudent.no) != -1) {
        cerr << newStudent.no << "号考生已存在\n";
        return;
    }
    if (_l.get_length() == 0) {
        _l.push_back(newStudent);

    }
    else {
        _l.insert_node(pos - 1, newStudent);
    }
    _l.print();
}

void deleteData(list<student>& _l) {
    int no, pos;
    cout << "请输入要删除的考生的考号：";
    cin >> no;
    pos = _l.find(no);
    if (pos==-1)
    {
        cout << "查无此人!" << endl;
    }
    else {
        cout << "你删除的考生信息是：";
        _l.del_node(pos);
        _l.print();
    }
}

void findData(list<student>& _l) {
    int no;
    cout << "请选择要查找的考生的考号：";
    cin >> no;
    int isFind=_l.find(no);
    if (isFind == -1) {
        cout << "查无此人!" << endl;
    }
    else {
        cout << "考号    姓名    性别    年龄    报考类别" << endl;
        cout << _l.get_node(isFind);
    }
}

void modifyData(list<student>& _l) {
    int no;
    student temp;
    cout << "请输入要修改的考生的考号：";
    cin >> no;
    int isFind = _l.find(no);
    if (isFind == -1) {
        cout << "查无此人!" << endl;
    }
    else {
        cout << "请输入修改后的信息：";
        cin >> temp;
        _l.modify_node(isFind, temp);
    }
}

int main()
{
    list<student>system;
    int num;
    cout << "首先请建立考生信息系统!" << endl;
    while (true) {
        cout << "请输入考生人数：";
        cin >> num;
        if (cin.fail() || num <= 0) {
            cerr << "考生人数输入错误\n";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
        else
            break;
    }
    cout << "请依次输入考生的考号，姓名，性别，年龄及报考类别!" << endl;
    while (true) {
        if (input(system, num))break;
    }
    system.print();

    int oper = 0;
    cout << "\n请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作）" << endl;
    while (oper >= 0) {
        cout << "\n请选择您要进行的操作：";
        cin >> oper;
        if (cin.fail()) {
            cerr << "操作数非法，请重新输入!\n";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            continue;
        }
        switch (oper) {
        case 0:
            exit(0);
            break;
        case 1:
            insertData(system);
            break;
        case 2:
            deleteData(system);
            break;
        case 3:
            findData(system);
            break;
        case 4:
            modifyData(system);
            break;
        case 5:
            system.print();
            break;
        default:
            cerr << "操作数错误，请重新输入!\n";
            break;
        }
    }
    return 0;
}
/*
5
1 stu1 女 20 软件设计师
2 stu2 男 21 软件开发师
3 stu3 男 20 软件设计师
4 stu4 男 19 网络工程师
5 stu5 女 30 人力资源部
1
4
100 stu10 女 21 软件测试
2
3
3
3
*/