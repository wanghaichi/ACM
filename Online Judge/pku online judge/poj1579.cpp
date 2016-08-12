/**************************************************************

AUTHOR: Hardy

TIME:  2016年 08月 11日 星期四 10:47:01 CST

ID: poj 1579

TYPE: 记忆化搜索 动态规划

DETAIL: 水题

TACTICS:

***************************************************************/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <queue>
#include <stack>

#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a > b ? b : a)
#define CL(a) memset(a, 0, sizeof(a));

using namespace std;

typedef long long ll;

const int inf = 1e9+7;
const int mod = 1e9+7;
const int maxn = 25, maxe = 1e6+7, maxv = 1e6+7;

int w[maxn][maxn][maxn];

int solve(int a, int b, int c){
	if(a <= 0 || b <= 0 || c <= 0)
		return 1;
	if(a > 20 || b > 20 || c > 20)
		return w[20][20][20] = solve(20, 20, 20);
	if(w[a][b][c])
		return w[a][b][c];
	if(a < b && b < c)
		return w[a][b][c] = solve(a, b, c-1) + solve(a, b-1, c - 1) - solve(a, b-1, c);
	else
		return w[a][b][c] = solve(a-1, b, c) + solve(a-1, b-1, c) + solve(a-1, b, c-1) - solve(a-1, b-1, c-1);
}

int main()
{
	CL(w);
	int a, b, c;
	while(~scanf("%d%d%d", &a, &b, &c) && (a != -1 || b != -1 || c != -1)){
		printf("w(%d, %d, %d) = %d\n", a, b, c, solve(a, b, c));
	}
	return 0;
}







