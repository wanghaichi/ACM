/**************************************************************

AUTHOR: Hardy

TIME:  2016年 08月 11日 星期四 09:12:42 CST

ID: poj 1159

TYPE: 动态规划

DETAIL: 给定字符串,求将其变成回文串最少需要加上的字符数

TACTICS: 
dp[i][j] 为从第i位到第j位需要加上的最少的字符数
s[i] == s[j] dp[i][j] = dp[i+1][j-1];
s[i] != s[j] dp[i][j] = min(dp[i+1][j], dp[i][j-1]) + 1;

妈哒要是开dp[maxn][maxn]会MLE,改成short才行!

然后用滚动数组，可以看到dp[i][j]只能从dp[i+1][]转移过来，所以缩掉第一维

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
const int maxn = 5100, maxe = 1e6+7, maxv = 1e6+7;

char s[maxn];
//short int dp[maxn][maxn];

int dp[2][maxn];

int main()
{
	int n;
	scanf("%d", &n);
	scanf("%s", s);
	CL(dp);
	//非滚动数组
	/*for(int k = 1; k < n; k ++){
		for(int i = 0; i < n; i ++){
			int j = i + k;
			if(s[i] == s[j])
				dp[i][j] = dp[i+1][j-1];
			else{
				dp[i][j] = min(dp[i+1][j], dp[i][j - 1]) + 1;
			}
		}
	}*/
	//printf("%d\n", dp[0][n-1]);
	//滚动数组
	int k = 0;
	for(int i = n - 2; i >= 0; i --){
		for(int j = i; j < n; j ++){
			if(s[i] == s[j]){
				dp[k][j] = dp[1-k][j-1];
			}
			else{
				dp[k][j] = min(dp[1-k][j], dp[k][j-1]) + 1;
			}
		}
		k = 1 - k;
	}
	printf("%d\n", dp[1-k][n-1]);
	
	return 0;
}







