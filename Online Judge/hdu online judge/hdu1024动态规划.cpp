#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

typedef long long ll;
const ll mod = 1e9+7;
const int maxn = 1e6+7;
int dp[2][maxn], a[maxn];

int solve(int m, int n){
	int t = 1;
	for(int i = 1; i <= m; i ++, t = !t){
		dp[t][i] = dp[!t][i-1] + a[i];
		dp[!t][i] = max(dp[!t][i], dp[!t][i-1]);
		for(int j = i + 1; j <= n - m + i; j ++){
			dp[t][j] = max(dp[!t][j-1], dp[t][j-1]) + a[j];
			dp[!t][j] = max(dp[!t][j], dp[!t][j-1]);
		}
	}
	int res = -(1<<30);
	for(int i = m; i <= n; i ++){
		res = max(res, dp[m&1][i]);
	}
	return res;
}


int main()
{
	int n, m;
	while(~scanf("%d%d", &m, &n)){
		for(int i = 1; i <= n; i ++){
			scanf("%d", &a[i]);
			dp[0][i] = dp[1][i] = 0;
		}
		printf("%d\n", solve(m, n));
	}
	
	return 0;
}
