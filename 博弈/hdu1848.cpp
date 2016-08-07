/**************************************************************

AUTHOR: Hardy

TIME: 2016年 08月 06日 星期六 15:45:44 CST

ID: hdu 1848

TYPE: nim 游戏 打表

DETAIL: 简单nim游戏，每次只能取斐波那契数个数个石子

TACTICS: 打表

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
int sg[1001], vis[1001];
int main()
{
	
	int f[17];
	f[1] = 1; f[2] = 2;
	for(int i = 3; i < 17; i ++)
		f[i] = f[i - 1] + f[i - 2];
	sg[0] = 0;
	for(int i = 1; i <= 1000; i ++){
		CL(vis);
		for(int j = 1; j < 17; j ++){
			int u = i - f[j];
			if(u >= 0){
				vis[sg[u]] = 1;
			}
			else
				break;
		}
		for(int x = 0; ; x++){
			if(!vis[x]){
				sg[i] = x;
				break;
			}
		}
	}
	int sto[3];
	while(~scanf("%d%d%d", &sto[0], &sto[1], &sto[2]) && sto[0]){
		int ans = 0;
		for(int i = 0; i < 3; i ++){
			ans ^= sg[sto[i]];
		}
		if(ans)
			puts("Fibo");
		else
			puts("Nacci");
	}	
	return 0;
}








