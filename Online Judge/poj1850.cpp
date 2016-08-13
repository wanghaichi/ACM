/**************************************************************

AUTHOR: Hardy

TIME:  2016年 08月 13日 星期六 10:07:48 CST

ID: poj 1850

TYPE: 计数 数位DP

DETAIL: 一个合法字符串要求每个位置严格递增，如abcd是一个合法的字符串，aa不
是一个合法的字符串。将所有合法的字符串排序，求给定字符串所在的位置

TACTICS: 数位dp，dp[i][j]表示长度为i以j开头的字符串共有多少个

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
const int maxn = 15, maxe = 1e6+7, maxv = 1e6+7;


bool can(char *s){
	for(int i = 1; s[i]; i ++){
		if(s[i] <= s[i-1])
			return false;
	}
	return true;
}

char s[maxn];
int dp[maxn][26], sum[maxn];
void init(){
	CL(dp);
	for(int i = 0; i < 26; i ++)
		dp[1][i] = 1;
	for(int i = 2; i <= 10; i ++){
		for(int j = 0; j < 26; j ++){
			for(int k = j + 1; k < 26; k ++){
				dp[i][j] += dp[i-1][k];
			}
		}
	}
	CL(sum);
	for(int i = 1; i <= 10; i ++){
		for(int j = 0; j < 26; j ++)
			sum[i] += dp[i][j];
		sum[i] += sum[i-1];
	}
}


int solve(){
	init();
	int len = strlen(s);
	if(len == 1){
		return s[0] - 'a' + 1;
	}
	else if (!can(s)){
		return 0;
	}
	int res = 0;
	res += sum[len - 1];
	int pre = 0;
	for(int i = 0; i < len; i ++){
		for(int j = pre; j < s[i] - 'a'; j ++){
			res += dp[len-i][j];
		}
		pre = s[i] - 'a' + 1;
	}
	res ++;
	return res;
}


int main()
{
	scanf("%s", s);
	printf("%d\n", solve());
	main();
	return 0;
}







