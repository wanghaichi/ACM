/**************************************************************

AUTHOR: Hardy

TIME:  2016年 08月 11日 星期四 10:37:14 CST

ID: poj 1163

TYPE: 动态规划 水题

DETAIL: 给一个三角形，从上到下选一条路经，使得和最大

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
const int maxn = 1e2+7, maxe = 1e6+7, maxv = 1e6+7;

int sto[maxn][maxn];

int main()
{
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++){
		for(int j = 1; j <= i; j ++){
			scanf("%d", &sto[i][j]);
		}
	}
	for(int i = n - 1; i >= 1; i --){
		for(int j = 1; j <= i; j ++){
			sto[i][j] = sto[i][j] + max(sto[i+1][j], sto[i+1][j+1]);
		}
	}
	printf("%d\n", sto[1][1]);

	return 0;
}







