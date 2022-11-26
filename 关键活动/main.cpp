#include <iostream>
#include "AOE.h"
using namespace std;
int main() {
	AGraph a;
	if (!a.TopSort()) {
		exit(1);
	}
	a.CriticalPath();
	return 0;
}
/*
8 10
1 2 8
1 3 12
2 4 14
3 4 10
3 6 28
4 5 6
4 6 8
5 7 18
6 7 6
7 8 12
*/
/*
7 8
1 2 4
1 3 3
2 4 5
3 4 3
4 5 2
4 6 6
5 7 5
6 7 2
*/
/*
9 11
1 2 6
1 3 4
1 4 5
2 5 1
3 5 1
4 6 2
5 7 9
5 8 7
6 8 4
7 9 2
8 9 4
*/