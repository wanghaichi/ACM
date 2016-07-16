// ACMdata.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<algorithm>
#include<cstdio>
#include <cstring>
#include <cmath>
#include <string>
#include <map>
#include <vector>
#include <queue>
using namespace std;
const int N = 1010;

int head[N], cnt, linker[N], vis[N];

struct node {
	int to, next;
}e[2*N];


void add(int u, int v) {
	e[cnt].to = v;
	e[cnt].next = head[u];
	head[u] = cnt++;

	e[cnt].to = u;
	e[cnt].next = head[v];
	head[v] = cnt++;
}

void init() {
	cnt = 0;
	memset(head, -1, sizeof(head));
	memset(linker, -1, sizeof(linker));
}

bool dfs(int v) {
	for (int i = head[v]; i != -1; i = e[i].next) {
		if (!vis[e[i].to]) {
			vis[e[i].to] = 1;
			if (linker[e[i].to] == -1 || dfs(linker[e[i].to])) {
				linker[e[i].to] = v;
				return true;
			}
		}
	}
	return false;
}



void solve() {
	int k, m, n, u, v;
	while (~scanf("%d", &k) && k){
		init();
		scanf("%d%d", &m, &n);
		for(int i = 0; i < k; i ++){
			scanf("%d%d", &u, &v);
			add(u, v + 500);
		}
		int ans = 0;
		for (int i = 1; i <= m; i++) {
			memset(vis, 0, sizeof(vis));
			if (dfs(i))
				ans++;
		}
		printf("%d\n", ans);
	}


}


int main() 
{
	solve();
	return 0;
}