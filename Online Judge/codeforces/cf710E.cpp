/*************************************************************

FILENAME:                   cf710E.cpp

AUTHOR:         Hardy - wanghaichi@twtstudio.com

CREATE:                2016-08-27 13:54:58

LAST MODIFIED:         2016-08-27 14:30:16

ID: cf710E 

TYPE: 动态规划

DETAIL: 需要构造一个长度为n的字符串，全都是c，每次可以加上或者减去一个c，
花费x，或者将当前的字符串长度翻倍，花费y，求最少花费

TATICS: 注意更新 2×i 的解

************************************************************/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cmath>
#include <queue>
#include <stack>
#include <map>

#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a > b ? b : a)
#define CL(a) memset(a, 0, sizeof(a))

using namespace std;

typedef long long ll;

const ll inf = 1e18;
const int mod = 1e9+7;
const int maxn = 1e7+7;

ll dp[maxn * 2];

int main()
{
    int n, x, y;
    scanf("%d%d%d", &n, &x, &y);
    for(int i = 0; i <= 2 * n; i ++){
        dp[i] = inf;
    }
    dp[0] = 0; 
    for(int i = 1; i <= n; i ++){
        if(i & 1){
            dp[i] = min(dp[i-1] + x, dp[i]);
            dp[i] = min(dp[i+1] + x, dp[i]);
            dp[i*2] = min(dp[i*2], dp[i] + y);
        }
        else{
            dp[i] = min(dp[i-1] + x, dp[i]);
            dp[i] = min(dp[i+1] + x, dp[i]);
            dp[i] = min(dp[i/2] + y, dp[i]);
            dp[i*2] = min(dp[i*2], dp[i] + y);
        }
    }
    printf("%lld\n", dp[n]);
	return 0;
}

