//需要内存空间16384*10000 所以使用滚动数组压缩空间

#include "stdafx.h"
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <map>
#define inf 1000000000

using namespace std;
typedef long long ll;

const int mod = 1000000007;
const int N = 16384; //2e14 表示异或值能取得的最大值
int dp[2][N], a[10001];

int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}
	memset(dp, 0, sizeof(dp));
	dp[0][a[0]] = 2;
	dp[0][0] = 1;
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < N; j++) {
			//三个10e9可能会超int，必须每一步都取模
			dp[i & 1][j] = (dp[(i - 1) & 1][j^a[i]] * 2) % mod + (dp[(i - 1) & 1][j] % mod); 
			dp[i & 1][j] %= mod;
		}
	}
	printf("%d\n", dp[(n-1)&1][0]);
	return 0;
}