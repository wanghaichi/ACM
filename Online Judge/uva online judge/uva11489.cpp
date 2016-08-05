/**************************************************************

AUTHOR: Hardy

TIME: 2016年 08月 05日 星期五 13:01:33 CST

ID: UVA 11489

TYPE: 简单博弈

DETAIL: 给出一串长度为n的数字，S T 两个人每次可以从中拿走一个数字，拿走后
需要满足剩下的数字的和是3的倍数，或者没有数字。最先不能拿的输

策略：记录下来所有数字中3的倍数的个数和不是3的倍数的个数。

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

char s[1100];
int vis[5];
int main()
{
	int T, cnt = 1;
	scanf("%d", &T);
	while(T --){
		scanf("%s", s);
		int len = strlen(s), tmp, sum1 = 0, sum2 = 0;
		memset(vis, 0, sizeof(vis));
		for(int i = 0; i < len; i ++){
			tmp = s[i] - '0';
			if(tmp % 3 == 0)
				sum1 ++;
			else{
				vis[tmp%3] = 1;
				sum2 += tmp;
			}
		}
		printf("Case %d: ", cnt ++);
		if(sum2 % 3 == 0){
			if(sum1 % 2 == 0)
				puts("T");
			else
				puts("S");
		}
		else{
			if(vis[sum2%3]){
				if(sum1 % 2 == 0)
					puts("S");
				else
					puts("T");
			}
			else{
				puts("T");
			}
		}
	}
	return 0;
}








