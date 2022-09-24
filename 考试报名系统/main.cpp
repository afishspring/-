#include<iostream>
#include"mylist.hpp"
using namespace std;

void input(list<student>&_l,int num) {
    student temp;
    for (int i = 0; i < num; i++) {
        cin >> temp;
        _l.push_back(temp);
    }
}

void insertData(list<student>& _l) {
    int pos;
    student newStudent;
    cout << "请输入你要插入的考生的位置：";
    cin >> pos;
    cout << "请依次输入要插入的考生的考号，姓名，性别，年龄及报考类别!" << endl;
    cin >> newStudent;
    _l.insert_node(pos-1, newStudent);
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
        cout << _l.del_node(pos);
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
    cout << "请输入考生人数：";
    cin >> num;
    cout << "请依次输入考生的考号，姓名，性别，年龄及报考类别!" << endl;
    input(system,num);
    system.print();

    int oper = 0;
    cout << "请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作）" << endl << endl;
    while (oper >= 0) {
        cout << "请选择您要进行的操作：";
        cin >> oper;
        if (cin.fail()) {
            cerr << "操作数非法，请重新输入!";
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
            cerr << "操作数错误，请重新输入!" << endl;
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