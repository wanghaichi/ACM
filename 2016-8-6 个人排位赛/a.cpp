/**************************************************************

AUTHOR: Hardy

TIME: 2016年 08月 06日 星期六 18:58:08 CST

ID:

TYPE:

DETAIL:

TACTICS:

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

ll q[maxn];

int main()
{
	int n, m, T;
	scanf("%d", &T);
	while(T --){
		ll v = 0, tmp;
		scanf("%d%d", &n, &m);
		for(int i = 0; i < n; i ++){
			scanf("%I64d", &tmp);
			v += tmp;
		}
		for(int i = 0; i < m; i ++){
			scanf("%I64d", &tmp);
			if(tmp <= v)
				printf("0");
			else
				printf("1");
		}
		printf("\n");
	}	
	return 0;
}








