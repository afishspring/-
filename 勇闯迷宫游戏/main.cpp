#include <iostream>
#include <iomanip>
#include <vector>
#include "mystack.hpp"
using namespace std;

class maze {
public:
	maze() :path(100), ans(100) { path.push_back(start); }
	bool check(point a) {//判断是否可通，是否访问过
		if (a.x >= 1 && a.y >= 1 && a.x <= row && a.y <= col && mark[a.x][a.y] == 1) {
			return true;
		}
		return false;
	}
	void dfs(point now) {
		int nextx, nexty;
		for (int i = 0; i < 4; i++) {			//遍历上下左右的路
			nextx = now.x + next[i][0];
			nexty = now.y + next[i][1];
			if (check({ nextx,nexty })) {		//是否访问过
				mark[nextx][nexty] = 2;			//标记为已访问
				path.push_back({ nextx,nexty,i});//加入路径栈，表示此线路的经过地点
				if (nextx == end.x && nexty == end.y) {//是否到达终点
					if (path.size() < minStep) {//此线路更小则复制路径到结果栈
						ans=path;
						minStep = path.size();
					}
				}
				else {//否则取下一步位置做当前位置的dfs
					dfs({ nextx,nexty });
				}
			}
		}
		//当前位置后续所有线路已搜索过并记录
		mark[now.x][now.y] = 1;	//标记此位置未访问
		path.pop_back();		//回溯
	}
	void printMap() {
		mark[start.x][start.y] = 2;
		for (int i = 0; i < (int)ans.size(); i++) {
			mark[ans[i].x][ans[i].y] = ans[i].dire+4;//标记数组对于当前位置的上一步骤+4以区分0和1
		}
		cout << "迷宫地图：\n\n";
		for (int i = 0; i <= row; i++) {
			cout << setw(10)<<" ";
			for (int j = 0; j <= col; j++) {
				if (mark[i][j] == 0) {//墙体
					cout  << "█ ";
				}
				else {//可通
					if (i == start.x && j == start.y || i == end.x && j == end.y)//起点、终点
						cout << "●";
					else if (mark[i][j] == 1) {//非起点终点，但没经过
						cout << "  ";
					}
					else if (mark[i][j] >= 2) {//非起点终点，最短路径
						switch (mark[i][j] - 4) {
						case 0:cout << "↓"; break;
						case 1:cout << "→"; break;
						case 2:cout << "↑"; break;
						case 3:cout << "←"; break;
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
			cerr << "迷宫无解\n";
			return;
		}
		cout << "迷宫路径：" << endl;
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