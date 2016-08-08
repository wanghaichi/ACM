/**************************************************************

AUTHOR: Hardy

TIME: 2016年 08月 08日 星期一 15:23:10 CST

ID: poj 2486

TYPE: 树形DP

DETAIL: 给出一个树，每个结点有一个权值，至多经历K条边（可以回溯），问经过的结点的权值
和最大是多少

TACTICS: 树形DP，很容易想到 dp[i][j] 表示 以i为结点的子树走j步最多能得到的权值，然而由于
可以回溯，所以需要分两种情况

状态如下：
dp[i][j][0] 表示从i结点出发，走j步，最后返回到i结点所能得到的最大权值。
dp[i][j][1] 表示从i结点出发，走j步，最后不返回i结点所能得到的最大权值。

转移方程：

从i结点出发，在其子树t上走k步，由于要回溯，所以减去i->t t->i两步，此时还剩下j-k步
dp[i][j][0] = max(dp[i][j][0], dp[t][k-2][0] + dp[i][j-k][0]);

最终不回到i结点，那么在t子树中或者剩余子树中结束
dp[i][j][1] = max(dp[i][j][1], dp[t][k-2][0] + dp[i][j-k][1], dp[t][k-1][1] + dp[i][j-k][0]);


***************************************************************/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a > b ? b : a)
#define CL(a) memset(a, 0, sizeof(a));

using namespace std;

typedef long long ll;

const int inf = 1e9+7;
const int mod = 1e9+7;
const int maxn = 1e2+7, maxe = 1e6+7, maxv = 1e6+7;

int head[maxn], cnt, n, k, w[maxn], dp[maxn][maxn*2][2];

struct edge{
	int next, to;
}e[maxn*2];

void add(int _u, int _v){
	e[cnt].to = _v;
	e[cnt].next = head[_u];
	head[_u] = cnt++;

	e[cnt].to = _u;
	e[cnt].next = head[_v];
	head[_v] = cnt++;
}

void init(){
	cnt = 0;
	memset(head, -1, sizeof(head));
	CL(dp);
}

void dfs(int u, int f){
	for(int i = 0; i <= k; i ++)
		dp[u][i][1] = dp[u][i][0] = w[u];
	for(int i = head[u]; i != -1; i = e[i].next){
		int v = e[i].to;
		if(v == f) continue;
		dfs(v, u);
		for(int j = k; j >= 1; j --){
			for(int l = 0; l < j; l ++){
				if(l <= j - 2){
					dp[u][j][1] = max(dp[u][j][1], dp[v][l][1] + dp[u][j-l-2][1]);
					dp[u][j][0] = max(dp[u][j][0], dp[v][l][1] + dp[u][j-l-2][0]);
				}
				dp[u][j][0] = max(dp[u][j][0], dp[v][l][0] + dp[u][j-l-1][1]);
			}
		}
	}
}



int main()
{
	int u, v;
	while(~scanf("%d%d", &n, &k)){
		for(int i = 1; i <= n; i ++)
			scanf("%d", &w[i]);
		init();
		for(int i = 0; i < n - 1; i ++){
			scanf("%d%d", &u, &v);
			add(u, v);
		}
		dfs(1, 0);
		printf("%d\n", dp[1][k][0]);
	}
	
	return 0;
}








