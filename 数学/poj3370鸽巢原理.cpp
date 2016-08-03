/**************************************************************

AUTHOR: Hardy

TIME: 2016年 08月 03日 星期三 15:49:23 CST

ID: poj3370

TYPE: 鸽巢原理

DETAIL: 给出n, m, 给出长度为m的序列，问是否可以选择序列中的某几个数，使得其
和为n的倍数
领s[i]表示前i个数的和，则s[i]有m+1组解（包括s[0]）若存在s[i] - s[j] = k*n
则序列i+1 ... j 为所求。考虑s[i]%n 共可能出现n种不同的情况，又因为n <= m　
于是必然存在解（鸽巢原理）

***************************************************************/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a > b ? b : a)
#define CL(a) memset(a, 0, sizeof(a));

using namespace std;

typedef long long ll;

const int inf = 1e9+7;
const int mod = 1e9+7;
const int maxn = 1e6+7, maxe = 1e6+7, maxv = 1e6+7;
int s[maxn], vis[maxn];
int main()
{
	int n, m;
	while(~scanf("%d%d", &n, &m) && (n != 0 || m != 0)){
		memset(vis, -1, sizeof(vis));
		s[0] = 0;
		for(int i = 1; i <= m; i ++){
			scanf("%d", &s[i]);
			s[i] += s[i-1];
			s[i] %= n;
		}
		int pos;
		for(int i = 0; i <= m; i++){
			if(vis[s[i]] == -1){
				vis[s[i]] = i;
			}else{
				pos = i;
				break;
			}
		}
		for(int j = vis[s[pos]] + 1; j <= pos; j ++){
			printf("%d%c", j, j == pos ? '\n' : ' ' );
		}
	}
	return 0;
}








