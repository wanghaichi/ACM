/**************************************************************

AUTHOR: Hardy

TIME: 2016年 08月 03日 星期三 16:23:08 CST

ID: poj 2356

TYPE: 鸽巢原理

DETAIL: 同poj3370

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
const int maxn = 1e4+7, maxe = 1e6+7, maxv = 1e6+7;

int s[maxn], vis[maxn], sto[maxn];

int main()
{
	int n;
	scanf("%d", &n);
	memset(vis, -1, sizeof(vis));
	s[0] = sto[0] = 0;
	for(int i = 1; i <= n; i ++){
		scanf("%d", &sto[i]);
		s[i] = sto[i];
		s[i] += s[i-1];
		s[i] %= n;
	}
	int pos = 0;
	for(int i = 0; i <= n; i ++){
		if(vis[s[i]] == -1){
			vis[s[i]] = i;
		}else{
			pos = i;
			break;
		}
	}
	printf("%d\n", pos - vis[s[pos]]);
	for(int i = vis[s[pos]] + 1; i <= pos; i ++){
		printf("%d\n", sto[i]);
	}
	return 0;
}








