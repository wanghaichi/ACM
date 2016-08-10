/**************************************************************

AUTHOR: Hardy

TIME:  2016年 08月 10日 星期三 16:48:56 CST

ID: poj 1088

TYPE: 动态规划 记忆化搜索

DETAIL: 给一个矩阵，只有当i点大于j点时，才能从i走到j，问最长路径

TACTICS: 就是个dfs，然后记录下来每个点的结果，记忆化搜索

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

int sto[maxn][maxn], dp[maxn][maxn];

int way[4][2] = {{1, 0}, {0, 1}, {0, -1}, {-1, 0}};
int n, m;

int dfs(int x, int y){
	if(dp[x][y])
		return dp[x][y];
	int tmp = 0;
	for(int i = 0; i < 4; i ++){
		int dx = x + way[i][0];
		int dy = y + way[i][1];
		if(dx >= 1 && dx <= n && dy >= 1 && dy <= m){
			if(sto[dx][dy] < sto[x][y])
				tmp = max(tmp, dfs(dx, dy));
		}
	}
	return dp[x][y] = tmp + 1;
}

int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++)
			scanf("%d", &sto[i][j]);
	CL(dp);
	int ans = 0;
	for(int i = 1; i <= n; i ++){
		for(int j = 1; j <= m; j ++){
			ans = max(ans, dfs(i, j));
		}
	}	
	printf("%d\n", ans);
	return 0;
}







