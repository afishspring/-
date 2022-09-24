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
    cout << "��������Ҫ����Ŀ�����λ�ã�";
    cin >> pos;
    cout << "����������Ҫ����Ŀ����Ŀ��ţ��������Ա����估�������!" << endl;
    cin >> newStudent;
    _l.insert_node(pos-1, newStudent);
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
        cout << _l.del_node(pos);
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
    cout << "�����뿼��������";
    cin >> num;
    cout << "���������뿼���Ŀ��ţ��������Ա����估�������!" << endl;
    input(system,num);
    system.print();

    int oper = 0;
    cout << "��ѡ����Ҫ���еĲ�����1Ϊ���룬2Ϊɾ����3Ϊ���ң�4Ϊ�޸ģ�5Ϊͳ�ƣ�0Ϊȡ��������" << endl << endl;
    while (oper >= 0) {
        cout << "��ѡ����Ҫ���еĲ�����";
        cin >> oper;
        if (cin.fail()) {
            cerr << "�������Ƿ�������������!";
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
            cerr << "��������������������!" << endl;
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