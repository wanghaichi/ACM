// Acm.cpp : 定义控制台应用程序的入口点。

#include "stdafx.h"
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cmath>
#include <cstring>
#define inf 10000000000

using namespace std;

typedef long long ll;

const int N = 2001;
const int mod = 1000000007;

int dp[N][N];

int main()
{
	int T, a = 0, b = 0, ans1, ans2, cnt = 1;
	scanf("%d", &T);
	while (T--) {
		scanf("%d-%d", &a, &b);
		memset(dp, 0, sizeof(dp));
		dp[1][0] = 1;
		for (int i = 2; i <= a; i++) {
			for (int j = 0; j < i && j <= b; j++) {
				if (i - 1 > j) {
					dp[i][j] += dp[i - 1][j];
					dp[i][j] %= mod;
				}
					
				if (j > 0) {
					dp[i][j] += dp[i][j - 1];
					dp[i][j] %= mod;
				}
			}
		}
		ans1 = dp[a][b];
		memset(dp, 0, sizeof(dp));
		dp[0][0] = 1; //这个初始条件我也是醉了！！！！！！
		for (int i = 0; i <= a; i++) {
			for (int j = min(i, b); j <= b; j++) {
				if ((i > 0 && i - 1 <= j) || (j == b && i > b)) {
					dp[i][j] += dp[i - 1][j];
					dp[i][j] %= mod;
				}
				if (i <= j - 1) {
					dp[i][j] += dp[i][j - 1];
					dp[i][j] %= mod;
				}
			}
		}
		if (b == 0)
			ans2 = 1;
		else 
			ans2 = dp[a][b];
		printf("Case #%d: %d %d\n", cnt++, ans1, ans2);
	}
	return 0;
}
