//最长公共子序列，dp[i][j]表示第一个字符串前i位与第二个字符串前j位的答案

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

int dp[1000][1000];

int main()
{
	char s1[1000], s2[1000];
	while (~scanf("%s%s", s1, s2)) {
		int n = strlen(s1), m = strlen(s2);
		dp[0][0] = dp[0][1] = dp[1][0] = 0;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				if (s1[i-1] == s2[j-1]) {
					dp[i][j] = dp[i - 1][j - 1] + 1;
				}
				else{
					dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
				}
			}
		}
		printf("%d\n", dp[n][m]);
	}

	return 0;
}