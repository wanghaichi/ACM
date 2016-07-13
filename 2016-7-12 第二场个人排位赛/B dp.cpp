
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <map>
#define inf 10000000000

using namespace std;
typedef long long ll;
int a[100001], dp[100001][2];
int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}
	sort(a, a + n);
	dp[0][0] = 0;
	dp[0][1] = -1; //判断不合法的条件！！！
	for (int i = 1; i < n; i++) {
		if (dp[i - 1][1] == -1) {
			dp[i][0] = -1;
			dp[i][1] = dp[i - 1][0] + a[i] - a[i - 1];
		}
		else if (dp[i - 1][0] == -1) {
			dp[i][0] = dp[i - 1][1];
			dp[i][1] = dp[i - 1][1] + a[i] - a[i - 1];
		}
		else {
			dp[i][0] = dp[i-1][1];
			dp[i][1] = min(dp[i - 1][0], dp[i - 1][1]) + a[i] - a[i - 1];
		}
	}
	printf("%d\n", dp[n - 1][1]);
	return 0;
}