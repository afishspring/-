#include <iostream>
#include <iomanip>
#include <vector>
#include "mystack.hpp"
using namespace std;

class maze {
public:
	maze() :path(100), ans(100) { path.push_back(start); }
	bool check(point a) {//�ж��Ƿ��ͨ���Ƿ���ʹ�
		if (a.x >= 1 && a.y >= 1 && a.x <= row && a.y <= col && mark[a.x][a.y] == 1) {
			return true;
		}
		return false;
	}
	void dfs(point now) {
		int nextx, nexty;
		for (int i = 0; i < 4; i++) {			//�����������ҵ�·
			nextx = now.x + next[i][0];
			nexty = now.y + next[i][1];
			if (check({ nextx,nexty })) {		//�Ƿ���ʹ�
				mark[nextx][nexty] = 2;			//���Ϊ�ѷ���
				path.push_back({ nextx,nexty,i});//����·��ջ����ʾ����·�ľ����ص�
				if (nextx == end.x && nexty == end.y) {//�Ƿ񵽴��յ�
					if (path.size() < minStep) {//����·��С����·�������ջ
						ans=path;
						minStep = path.size();
					}
				}
				else {//����ȡ��һ��λ������ǰλ�õ�dfs
					dfs({ nextx,nexty });
				}
			}
		}
		//��ǰλ�ú���������·������������¼
		mark[now.x][now.y] = 1;	//��Ǵ�λ��δ����
		path.pop_back();		//����
	}
	void printMap() {
		mark[start.x][start.y] = 2;
		for (int i = 0; i < (int)ans.size(); i++) {
			mark[ans[i].x][ans[i].y] = ans[i].dire+4;//���������ڵ�ǰλ�õ���һ����+4������0��1
		}
		cout << "�Թ���ͼ��\n\n";
		for (int i = 0; i <= row; i++) {
			cout << setw(10)<<" ";
			for (int j = 0; j <= col; j++) {
				if (mark[i][j] == 0) {//ǽ��
					cout  << "�� ";
				}
				else {//��ͨ
					if (i == start.x && j == start.y || i == end.x && j == end.y)//��㡢�յ�
						cout << "��";
					else if (mark[i][j] == 1) {//������յ㣬��û����
						cout << "  ";
					}
					else if (mark[i][j] >= 2) {//������յ㣬���·��
						switch (mark[i][j] - 4) {
						case 0:cout << "��"; break;
						case 1:cout << "��"; break;
						case 2:cout << "��"; break;
						case 3:cout << "��"; break;
						}
					}
				}
			}
			cout << endl;
		}
		cout << endl;
	}
	void printPath() {
		int i = 0;
		if (ans.size() == 1) {
			cerr << "�Թ��޽�\n";
			return;
		}
		cout << "�Թ�·����" << endl;
		for (i = 0; i < ans.size() - 1; i++) {
			if (i % 5 == 0)cout << endl;
			cout << ans[i] << " ---> ";
			
		}
		cout << ans[i] << endl;
	}
private:
	const int next[4][2] = { {1, 0},{0, 1} ,{-1, 0},  {0, -1} };
	int mark[10][10] = {
			{0,0,0,0,0,0,0,0,0,0},
			{0,1,0,1,1,1,0,1,1,0},
			{0,1,0,1,0,1,0,1,1,0},
			{0,1,1,1,0,1,0,1,1,0},
			{0,1,0,1,1,0,1,0,1,0},
			{0,1,0,1,0,1,1,1,1,0},
			{0,0,1,1,0,0,0,1,1,0},
			{0,1,1,0,0,0,0,0,1,0},
			{0,1,1,1,1,1,1,1,1,0},
			{0,0,0,0,0,0,0,0,0,0},
	};
	point start = { 1,1 }, end = { 5,5 };
	stack<point>path;
	stack<point>ans;
	int row = 9, col = 9;
	int minStep = INT_MAX;

};

int main() {
	maze s;
	s.dfs({ 1,1 });
	s.printMap();
	s.printPath();
}