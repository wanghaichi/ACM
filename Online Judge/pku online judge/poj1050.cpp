/**************************************************************

AUTHOR: Hardy

TIME:  2016年 08月 10日 星期三 16:07:17 CST

ID: poj 1050

TYPE: 动态规划 

DETAIL: 求某个矩阵的子矩阵，使得子矩阵和最小

TACTICS: 首先考虑一维的情况，dp[i] = (dp[i-1] + num[i] , 0)
这里可以用一个变量来替代数组

在考虑二维的情况，一个矩阵求和其实可以将其高压缩成1，这样就转成了1维的情况
具体看代码

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
const int maxn = 105, maxe = 1e6+7, maxv = 1e6+7;

int sto[maxn][maxn], now[maxn];

int main()
{	
	int n;
	scanf("%d", &n);
	//这里要考虑到全是负数的情况
	int ans = -500, sum = 0;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j ++){
			scanf("%d", &sto[i][j]);
			ans = max(ans, sto[i][j]);
		}
	//处理第i行到第j行的子矩阵的最大值
	for(int i = 1; i <= n; i ++){
		//now储存当前第i行到第j行的元素的和
		//固定第i行不变，枚举第j行，枚举过程中维护最大值
		CL(now);
		for(int j = i; j <= n; j ++){
			sum = 0;
			for(int k = 1; k <= n; k ++){
				now[k] += sto[k][j];
				//与一维情况相同
				sum = max(sum + now[k], 0);
				if(sum > ans) ans = sum;
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}







