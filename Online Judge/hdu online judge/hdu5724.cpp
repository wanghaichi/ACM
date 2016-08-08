/**************************************************************

AUTHOR: Hardy

TIME: 2016年 08月 08日 星期一 10:38:01 CST

ID: hdu 5724 多校第一场

TYPE: 状压博弈 SG函数

DETAIL: n行棋盘，每一行有若干棋子，每次可以选择一行，选择一个棋子向右移动
一格，如果其右边有石子则跳过，移动到第一个没有棋子的地方

TACTICS: 状压枚举每一种状态，求出每个状态下的SG函数值。

***************************************************************/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a > b ? b : a)
#define CL(a) memset(a, 0, sizeof(a));

using namespace std;

typedef long long ll;

const int inf = 1e9+7;
const int mod = 1e9+7;
const int maxn = 21, maxe = 1e6+7, maxv = 1e6+7;

int sg[1<<maxn], vis[maxn];

void init(){
	CL(sg);
	for(int i = 0; i < (1 << maxn); i ++){
		CL(vis);
		for(int j = 20; j >= 0; j --){
			int tmp = i;
			if(tmp & (1<<j)){
				for(int k = j - 1; k >= 0; k --){
					if(!(tmp & (1 << k))){
						tmp ^= (1 << j);
						tmp ^= (1 << k);
						vis[sg[tmp]] = 1;
						break;
					}
				}
			}
		}
		for(int x = 0; ; x ++){
			if(!vis[x]){
				sg[i] = x;
				break;
			}
		}
	}
}

int main()
{
	int T, n, k, cur, ans, num;
	init();
	scanf("%d", &T);
	while(T --){
		scanf("%d", &n);
		ans = 0;
		for(int i = 0; i < n; i ++){
			scanf("%d", &k);
			cur = 0;
			for(int j = 0; j < k; j ++){
				scanf("%d", &num);
				cur |= (1 << (20-num));
			}
			ans ^= sg[cur];
		}
		if(ans == 0){
			puts("NO");
		}
		else{
			puts("YES");
		}
	}
	
	return 0;
}








