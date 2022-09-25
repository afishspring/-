#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

class maze {
public:
	struct point {
		int x, y;
		friend ostream& operator<<(ostream& os, const point& rhs) {
			os <<"<" <<rhs.x<<"," << rhs.y << ">";
			return os;
		}
	};
	bool check(point a) {
		if (a.x >= 1 && a.y >= 1 && a.x <=5 && a.y <=5 && mark[a.x][a.y] == 1) {
			return true;
		}
		return false;
	}
	void dfs(point now) {
		int nextx, nexty;
		for (int i = 0; i < 4; i++) {
			nextx = now.x + next[i][0];
			nexty = now.y + next[i][1];
			if (check({ nextx,nexty })) {
				mark[nextx][nexty] = 2;
				path.push_back({ nextx,nexty });
				if (nextx == end.x && nexty == end.y) {
					if (path.size() < minStep) {
						ans = path;
						minStep = path.size();
					}
					mark[nextx][nexty] = 2;
					path.pop_back();
				}
				else {
					dfs({ nextx,nexty });
				}
			}
		}
		mark[now.x][now.y] = 1;
		path.pop_back();
	}
	void printMap() {
		mark[start.x][start.y] = 2;
		for (int i = 0; i < (int)ans.size(); i++) {
			mark[ans[i].x][ans[i].y] = 2;
		}
		cout << "迷宫地图：" << endl << endl << "     ";
		for (int i = 0; i <= col; i++) {
			cout << setw(6) << i  <<"列";
		}
		cout << endl;
		for (int i = 0; i <= row; i++) {
			cout << i << "行";
			for (int j = 0; j <= col; j++) {
				if (mark[i][j] == 0) {
					cout << setw(8) << "#";
				}
				else if(mark[i][j]==2){
					cout << setw(8) << "x";
				}
				else {
					cout << setw(8) << "0";
				}
			}
			cout << endl;
		}
		cout << endl;
	}
	void printPath() {
		int i = 0;
		cout<<"迷宫路径："<<endl<<endl<<start << " ---> ";
		for (i = 0; i < (int)ans.size()-1; i++) {
			cout <<ans[i]<< " ---> ";
		}
		cout << ans[i]<< endl;
	}
private:
	const int next[4][2] = { {1, 0},{0, 1} ,{-1, 0},  {0, -1} };
	int mark[10][10] = {
			{0,0,0,0,0,0,0,0,0,0},
			{0,1,0,1,1,1,0,0,0,0},
			{0,1,0,1,0,1,0,0,0,0},
			{0,1,1,1,0,1,0,0,0,0},
			{0,1,0,1,1,1,0,0,0,0},
			{0,1,0,1,0,1,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0},
	};
	point start = { 1,1 }, end = { 5,5 };
	vector<point>path;
	vector<point>ans;
	int row = 6, col = 6;
	int minStep = INT_MAX;
};

int main() {
	maze s;
	s.dfs({ 1,1 });
	s.printMap();
	s.printPath();
}