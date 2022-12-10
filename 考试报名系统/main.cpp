#include <iostream>
#include "mylist.h"
using namespace std;

bool input(list<student>&_l,int num) {
    student temp;
    for (int i = 0; i < num; i++) {
        cin >> temp;
        if (cin.fail()) {
            cerr << "�������\n";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            return false;
        }
        if (_l.find(temp.no)!=-1) {
            cerr << temp.no << "�ſ����Ѵ���\n";
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
    cout << "��������Ҫ����Ŀ�����λ�ã�";
    cin >> pos;
    if (cin.fail()||pos>_l.get_length()+1&& _l.get_length()!=0||pos<=0) {
        cerr << "����λ��ֻ����"<<1<<"~"<< _l.get_length()+1<<"֮��\n";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        return;
    }
    else if (_l.get_length() == 0 && pos != 1) {
        cerr << "ϵͳ����Ϊ��ʱ������λ��Ϊ1\n";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        return;
    }
    cout << "����������Ҫ����Ŀ����Ŀ��ţ��������Ա����估�������!" << endl;
    cin >> newStudent;
    if (cin.fail()) {
        cerr << "�������\n";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        return;
    }
    if (_l.find(newStudent.no) != -1) {
        cerr << newStudent.no << "�ſ����Ѵ���\n";
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
    cout << "������Ҫɾ���Ŀ����Ŀ��ţ�";
    cin >> no;
    pos = _l.find(no);
    if (pos==-1)
    {
        cout << "���޴���!" << endl;
    }
    else {
        cout << "��ɾ���Ŀ�����Ϣ�ǣ�";
        _l.del_node(pos);
        _l.print();
    }
}

void findData(list<student>& _l) {
    int no;
    cout << "��ѡ��Ҫ���ҵĿ����Ŀ��ţ�";
    cin >> no;
    int isFind=_l.find(no);
    if (isFind == -1) {
        cout << "���޴���!" << endl;
    }
    else {
        cout << "����    ����    �Ա�    ����    �������" << endl;
        cout << _l.get_node(isFind);
    }
}

void modifyData(list<student>& _l) {
    int no;
    student temp;
    cout << "������Ҫ�޸ĵĿ����Ŀ��ţ�";
    cin >> no;
    int isFind = _l.find(no);
    if (isFind == -1) {
        cout << "���޴���!" << endl;
    }
    else {
        cout << "�������޸ĺ����Ϣ��";
        cin >> temp;
        _l.modify_node(isFind, temp);
    }
}

int main()
{
    list<student>system;
    int num;
    cout << "�����뽨��������Ϣϵͳ!" << endl;
    while (true) {
        cout << "�����뿼��������";
        cin >> num;
        if (cin.fail() || num <= 0) {
            cerr << "���������������\n";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
        else
            break;
    }
    cout << "���������뿼���Ŀ��ţ��������Ա����估�������!" << endl;
    while (true) {
        if (input(system, num))break;
    }
    system.print();

    int oper = 0;
    cout << "\n��ѡ����Ҫ���еĲ�����1Ϊ���룬2Ϊɾ����3Ϊ���ң�4Ϊ�޸ģ�5Ϊͳ�ƣ�0Ϊȡ��������" << endl;
    while (oper >= 0) {
        cout << "\n��ѡ����Ҫ���еĲ�����";
        cin >> oper;
        if (cin.fail()) {
            cerr << "�������Ƿ�������������!\n";
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
            cerr << "��������������������!\n";
            break;
        }
    }
    return 0;
}
/*
5
1 stu1 Ů 20 ������ʦ
2 stu2 �� 21 �������ʦ
3 stu3 �� 20 ������ʦ
4 stu4 �� 19 ���繤��ʦ
5 stu5 Ů 30 ������Դ��
1
4
100 stu10 Ů 21 �������
2
3
3
3
*/