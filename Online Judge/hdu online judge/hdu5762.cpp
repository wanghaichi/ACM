/**************************************************************

AUTHOR: Hardy

TIME: 2016年 08月 03日 星期三 15:15:13 CST

ID: hdu5762

TYPE: 暴力　用到了鸽巢原理的思想，证明出暴力可过

DETAIL:　给出 100000 个点，求是否存在点对(A, B) 和 (C, D)使得两个点对的曼哈
顿距离相等。其中A < B && C < D && (A != C || B != D) 
根据鸽巢原理，曼哈顿距离在100000的范围内，只能存在200000种不同的曼哈顿距离，
即最多处理200000组点对就可知道是否存在相等的解，因此直接暴力就可以

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
const int maxn = 1e6+7, maxe = 1e6+7, maxv = 1e5+7;

struct node{
	int x, y;
}no[maxv];

int vis[maxv * 2];

int main()
{
	int T, n, m;
	scanf("%d", &T);
	while(T --){
		scanf("%d%d", &n, &m);
		for(int i = 0; i < n; i ++){
			scanf("%d%d", &no[i].x, &no[i].y);
		}
		CL(vis);
		bool flag = false;
		for(int i = 0; i < n; i ++){
			for(int j = i + 1; j < n; j ++){
				int dx = abs(no[i].x - no[j].x);
				int dy = abs(no[i].y - no[j].y);
				if(vis[dx+dy]){
					flag = true;
					break;
				}
				else{
					vis[dx+dy] = 1;
				}
			}
		}
		if(flag)
			puts("YES");
		else
			puts("NO");
	}
	return 0;
}








