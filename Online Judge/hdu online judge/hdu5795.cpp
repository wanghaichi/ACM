/**************************************************************

AUTHOR: Hardy

TIME: 2016年 08月 06日 星期六 15:16:55 CST

ID: hdu 5795

TYPE: 博弈 sg打表 找规律

DETAIL: nim游戏基础上加上另一种操作，将一堆石子分成三堆,其nim和为三推的sg值
异或

TACTICS: 打表，找到规律：
sg[i] = i - 1 (i % 8 == 0)
sg[i] = i + 1 (i % 8 == 7)
sg[i] = i (其他)

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

int s[maxn], sg[maxn], vis[100];

int main()
{
	/*以下为打表程序	
	sg[0] = 0;
	for(int i = 1; i <= 50; i ++){
		CL(vis);
		for(int j = 0; j < i; j ++){
			vis[sg[j]] = 1;
		}
		for(int k = 1; k < i; k ++){
			for(int m = 1; m < i; m ++){
				int u = i - m - k;
				if(u > 0){
					int tmp = sg[k] ^ sg[m] ^ sg[u];
					vis[tmp] = 1;
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
	for(int i = 0; i <= 50; i ++){
		printf("sg[%d] = %d\n", i, sg[i] - i);
	}
	*/
	int T, n;
	scanf("%d", &T);
	while(T --){
		scanf("%d", &n);
		int ans = 0, tmp;
		for(int i = 0; i < n; i ++){
			scanf("%d", &tmp);
			if(tmp % 8 == 0)
				ans ^= (tmp - 1);
			else if (tmp % 8 == 7)
				ans ^= (tmp + 1);
			else
				ans ^= tmp;
		}
		if(ans != 0)
			puts("First player wins.");
		else
			puts("Second player wins.");


	}
	
	return 0;
}








