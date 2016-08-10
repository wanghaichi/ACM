/**************************************************************

AUTHOR: Hardy

TIME:  2016年 08月 10日 星期三 12:04:21 CST

ID: poj 1037 

TYPE: 动态规划 计数

DETAIL: 给定n个数的排列，要求每一个数要同时小于或大于两边，将所有符合条件
的数按字典序进行排列，每次询问给出n个数，问第c个合法的排列是什么

TACTICS: 由于相邻两个数满足上升或者下降的条件，同时在求长度为j的问题时，可以
用到长度为j-1的子问题，于是可以使用动态规划求解。
定义dp[i][j][0] 表示以i开头，长度为j，后一个数是上升（即大于i）的方案数
dp[i][j][1] 表示下降（小于i）的方案数
转移方程为：
dp[i][j][0] = sum(dp[(k = i -> n - 1)][j-1][1])
dp[i][j][1] = sum(dp[(k = 1 -> i - 1)][j-1][0])
即将每一个数加在之前处理过的数的前头。

同时有一个细节，当长度变化时，n也在变化
比如对于 5 4 6 2 3 1 这样一个序列 当考虑dp[5][6][1]时
后面的序列其实是 4 5 2 3 1 ， 这里6变成了5，所以在第一个状态转移方程的时候
k 是从i 到 n - 1 而不是 i + 1 到 n 。

可以发现尽管后面的数字发生了变化，但是其大小位置没有发生变化，即原本是第几
大，现在还是第几大，因此在求解过程中可以使用这个性质

在求排列的时候，首先考虑以当前第i大的数为开头的方案数，c大于该方案数，则
c减去该方案数，并考虑第i+1大的数，若c小于等于该方案数，则说明当前的数为
第i大的数（注意不是i，是当前为出现的数中第i大的数）。
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
const int maxn = 25, maxe = 1e6+7, maxv = 1e6+7;

ll dp[maxn][maxn][2];
int ans[maxn], vis[maxn];
//求出当前为使用过的数字中，第j大的数
int idx(int j){
	int sum = 0;
	for(int i = 1; i <= maxn; i ++){
		if(!vis[i])
			sum ++;
		if(sum == j)
			return i;
	}
	return -1;
}


int main()
{
	int T, n;
	ll c;
	scanf("%d", &T);
	while(T --){
		scanf("%d%lld", &n, &c);
		CL(dp);
		dp[1][1][0] = dp[1][1][1] = 1;
		for(int j = 2; j <= n; j ++){
			for(int i = 1; i <= j; i ++){
				//上面提到过的要注意的地方
				for(int k = i; k < j; k ++)
					dp[i][j][0] += dp[k][j-1][1];
				for(int k = 1; k < i; k ++)
					dp[i][j][1] += dp[k][j-1][0];
			}
		}
		CL(vis);
		//be表示开始的位置，en标记当前结束的位置，up down标记当前应该取的状态
		int be = 1, en = n, up = 1, down = 1;
		for(int i = 1, x = n; i <= n; i ++, x --){
			//x表示长度
			for(int j = be; j <= en; j ++){
				//当前状态为down，说明下一个数要比当前的数小
				if(down && c <= dp[j][x][1]){
					int k = idx(j);
					vis[k] = 1;
					ans[i] = k;
					up = 1;
					down = 0;
					be = 1;
					en = j - 1;
					break;
				}
				if(down && c > dp[j][x][1])
					c -= dp[j][x][1];
				//当前状态为up，表示下一个数要比当前状态大
				if(up && c <= dp[j][x][0]){
					int k = idx(j);
					vis[k] = 1;
					ans[i] = k;
					up = 0;
					down = 1;
					//这里仍要考虑n变化的情况，因此下一个数应从j到x-1
					be = j;
					en = x - 1;
					break;
				}
				if(up && c > dp[j][x][0])
					c -= dp[j][x][0];
			}
		}
		for(int i = 1; i <= n; i ++)
			printf("%d%c", ans[i], i == n ? '\n' : ' ');
	}
	
	return 0;
}







