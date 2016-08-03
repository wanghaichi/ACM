/**************************************************************

AUTHOR: Hardy

TIME: 2016年 08月 03日 星期三 14:59:29 CST

ID: hdu 1205

TYPE: 数学　鸽巢原理

DETAIL: 给出ｎ种糖果和每种糖果的数量，吃糖的时候相邻两次不能吃同一中糖果，
求是否能将所有的糖果吃完。考虑所有糖果中数量最多的那一种，设数量为maxn，则
若想将这种糖果吃完至少需要 maxn - 1 个其他种类的糖果。因此若
maxn + maxn - 1 > sum 无解。
若满足maxn + maxn - 1 <= sum 则将多余的糖果穿插在数量最多的糖果之间，必然
能吃完.

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
	int T, n;
	scanf("%d", &T);
	while(T --){
		ll ma = 0, sum = 0, tmp;
		scanf("%d", &n);
		for(int i = 0; i < n; i ++){
			scanf("%I64d", &tmp);
			sum += tmp;
			ma = MAX(ma, tmp);
		}
		if(ma * 2 <= sum + 1)
			puts("Yes");
		else
			puts("No");
	}
	return 0;
}








