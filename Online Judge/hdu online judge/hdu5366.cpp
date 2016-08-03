/**************************************************************

AUTHOR: Hardy

TIME: 2016年 08月 03日 星期三 18:37:27 CST

ID: hdu 5366

TYPE: 动态规划

DETAIL: 有ｎ个石头，一个撒币要往上面放麻将，两个麻将之间的间隔需要大于等于2
问对于给定的ｎ有多少种方法
定义状态dp[i][0] 表示i个石头，最后一个不方麻将的方法，dp[i][1]表示最后一个
放麻将的方法
状态转移方程：
dp[i][0] = dp[i-1][0] + dp[i-1][1]
dp[i][1] = dp[i-2][0] + 1

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
const int maxn = 1e6+7, maxe = 1e6+7, maxv = 1e6+7;

ll dp[61][2];

int main()
{	
	dp[1][0] = 0; dp[1][1] = dp[2][0] = dp[2][1] = 1;
	for(int i = 3; i <= 60; i ++){
		dp[i][0] = dp[i-1][0] + dp[i-1][1];
		dp[i][1] = dp[i-2][0] + 1;
	}
	int n;
	while(~scanf("%d", &n)){
		printf("%lld\n", dp[n][0] + dp[n][1]);
	}
	return 0;
}








