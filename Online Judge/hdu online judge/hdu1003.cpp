//求最大子区间和，dp[i]表示以第i位结尾的最大和 dp[i] = dp[i-1] > 0 ? dp[i-1] + a[i] : a[i];

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

const int N = 1000000;
const int mod = 9973;

int main()
{
	int T, n, a[100001],dp[100001], ans = 0, b, e, ct = 1;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%d", &a[i]);
		}
		dp[0] = a[0];
		ans = dp[0]; //初始化不能为0！
		b = e = 0;
		for (int i = 1; i < n; i++) {
			dp[i] = dp[i - 1] + a[i] > a[i] ? dp[i - 1] + a[i] : a[i];
			if (dp[i] > ans) {
				ans = dp[i];
				e = i;
			}
		}
		int tmp = 0;
		for (int i = e; i >= 0; i --) {
			tmp += a[i];
			if (ans == tmp)
				b = i;
		}
		printf("Case %d:\n%d %d %d\n",ct ++, ans, b+1, e+1);
		if (T) {
			printf("\n");
		}
	}
	return 0;
}