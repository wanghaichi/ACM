/**************************************************************

AUTHOR: Hardy

TIME:  2016年 08月 11日 星期四 09:48:14 CST

ID: poj 1160

TYPE: 动态规划

DETAIL: 在x轴上有n个村庄，选择m个村庄建立邮局，问如何建立邮局能使得所有村庄
到离它最近的邮局的距离之和最小

TACTICS: 
dis[i][j] 表示从第i个村庄到第j个村庄建立一个邮局，最小的距离
可以看出dis[i][j] 最小策略应将邮局建立在 (i+j)/2 的位置
dis[i][j] = dis[i][j-1] + sto[j] - sto[(i+j)/2]
dp[i][j] 表示前i个村庄建立j个邮局的最小值
dp[i][j] = min(dp[i][j], dp[k][j-1] + dis[k+1][j])
前k个村庄建立j-1个邮局，k+1到j建立一个邮局

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
const int maxn = 310, maxe = 1e6+7, maxv = 1e6+7;

int sto[maxn], dp[maxn][31], dis[maxn][maxn];
int n, m;
void init(){
	CL(dis);
	for(int i = 1; i <= n; i ++){
		for(int j = i; j <= n; j ++){
			dis[i][j] = dis[i][j-1] + sto[j] - sto[(i+j)/2];
		}
	}
	memset(dp, 0x3f, sizeof(dp));
	for(int i = 0; i <= m; i ++){
		dp[i][i] = 0;
	}
}

int main()
{
	while(~scanf("%d%d", &n, &m)){
		for(int i = 1; i <= n; i ++)
			scanf("%d", &sto[i]);
		init();
		for(int i = 1; i <= n; i ++){
			for(int j = 1; j <= m && j <= i; j ++){
				for(int k = j - 1; k < i; k ++){
					dp[i][j] = min(dp[i][j], dp[k][j-1] + dis[k+1][i]);
				}
			}
		}
		printf("%d\n", dp[n][m]);
	
	}
	return 0;
}







