/**************************************************************

AUTHOR: Hardy

TIME: 2016年 08月 08日 星期一 16:24:10 CST

ID: poj 3020

TYPE: 二分图匹配

DETAIL: 给出一张图，上面有若干市区（*），在每个市区上可以建造雷达，雷达的覆盖范围只有
2，就是只能覆盖该点和他相邻的一个点，求最小雷达数

TACTICS: 最小点覆盖 = n - 最大匹配
建双向边，跑匈牙利，所得最大匹配除以二，总数一减就对了

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
const int maxn = 407, maxe = 2000, maxv = 407;

int head[maxv], cnt, linker[maxn], vis[maxn];

int st[50][20];
struct egde{
	int to, next;
}e[maxe];

void add(int _u, int _v){
	e[cnt].to = _v;
	e[cnt].next = head[_u];
	head[_u] = cnt++;

	e[cnt].to = _u;
	e[cnt].next = head[_v];
	head[_v] = cnt++;
}

void init(){
	cnt = 0;
	memset(head, -1, sizeof(head));
	memset(linker, -1, sizeof(linker));
	memset(st, -1, sizeof(st));
}

bool dfs(int u){
	for(int i = head[u]; i != -1; i = e[i].next){
		int v = e[i].to;
		if(!vis[v]){
			vis[v] = 1;
			if(linker[v] == -1 || dfs(linker[v])){
				linker[v] = u;
				return true;
			}
		}
	}
	return false;
}

char s[50][20];
int main()
{
	int T, n, m;
	scanf("%d", &T);
	while(T --){
		init();
		scanf("%d%d", &n, &m);
		for(int i = 0; i < n; i ++)
			scanf("%s", s[i]);
		int ct = 0;
		for(int i = 0; i < n; i ++)
			for(int j = 0; j < m; j ++)
				if(s[i][j] == '*')
					st[i][j] = ct++;
		for(int i = 0; i < n; i ++){
			for(int j = 0; j < m; j ++){
				if(st[i][j] != -1){
					if(st[i+1][j] != -1)
						add(st[i][j], st[i+1][j]);
					if(st[i][j+1] != -1)
						add(st[i][j], st[i][j+1]);
				}
			}
		}
		int ans = 0;
		for(int i = 0; i < ct; i ++){
			CL(vis);
			if(dfs(i))
				ans ++;
		}
		printf("%d\n", ct - ans / 2);
	}
	return 0;
}








