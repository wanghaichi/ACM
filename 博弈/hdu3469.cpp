/**************************************************************

AUTHOR: Hardy

TIME: 2016年 08月 05日 星期五 12:40:29 CST

ID: HDU 2469

TYPE: 找规律 水题

DETAIL: n个房间,警察抓小偷,警察每天选择一个房间检查,小偷每天会移动到相邻的
房间去。
策略：从第2间房开始向后查，查到第n-1间，这样可以保证小偷当前在最后一间
或者前n-2间中，再从n-1查到第2间。可以发现小偷要么想要活到最后只能最开始在
第一间，又因为当查回到第2间的时候，移动了偶数次，小偷不可能还在最开始的位置
因此当n>2的时候，至少需要2*n-4步

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

int main()
{
	int T, n, cnt = 1;
	scanf("%d", &T);
	while(T --){
		scanf("%d", &n);
		if(n == 1 || n == 2){
			printf("Case %d: %d\n", cnt++, n);
		}else{
			printf("Case %d: %d\n", cnt++, n * 2 - 4);
		}
	}
	return 0;
}








