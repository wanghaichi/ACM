/******************
无向联通图的双联通分量，具体概念保存了一个网页，上面讲的很详细。
对于一个无向联通图，对其进行tarjan算法求出low数组，则low值相等的点在同一个双联通分量中。
进行缩点之后，所有的叶子节点，就是度为1的点，需要在他们之间加边使得两个双联通分量变成一个双联通分量。最少需要添加边的数量为(leaf+1)/2原因在网页上面有说明
******************/


#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>

using namespace std;

const int N = 1e5+7;
const int mod = 1e9+7;

typedef long long ll;


int head[N], cnt, dep, dfn[N], low[N], root, rf, dp[N], leaf;

struct node{
	int to, next;
}no[N];

void add(int u, int v){
	no[cnt].to = v;
	no[cnt].next = head[u];
	head[u] = cnt++;

	no[cnt].to = u;
	no[cnt].next = head[v];
	head[v] = cnt++;
}

void Tarjan(int u, int fa){
	dfn[u] = low[u] = dep++;
	for(int i = head[u]; i != -1; i = no[i].next){
		int v = no[i].to;
		if(dfn[v] == -1){
			Tarjan(v, u);
			low[u] = min(low[u], low[v]);
			if(u == root) rf ++;
			//else if (low[v] >= dfn[u]) u是割点
			//else if (low[v] > dfn[u]) u->v 是割边
		}
		else if (v != fa){
			low[u] = min(low[u], dfn[v]);
		}
	}
}

void init(){
	memset(head, -1, sizeof(head));
	cnt = dep = rf = leaf = 0;
	root = 1;
	memset(dp, 0, sizeof(dp));
	memset(dfn, -1, sizeof(dfn));
}

int main()
{
	int n, m, u, v;
	while(~scanf("%d%d",&n , &m)){
		init();
		for(int i = 0; i < m; i ++){
			scanf("%d%d", &u, &v);
			add(u, v);
		}
		Tarjan(1, -1);
		for(int i = 1; i <= n; i ++){
			for(int j = head[i]; j != -1; j = no[j].next){
				v = no[j].to;
				if(low[i] != low[v])
					dp[low[i]] ++;
			}
		}
		for(int i = 0; i < n; i ++){
			if(dp[i] == 1)
				leaf ++;
		}
		printf("%d\n", (leaf+1)/2);
	}
	return 0;
}








