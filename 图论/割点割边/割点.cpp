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
const int N = 110;
int head[N], cnt, dep[N], low[N], vis[N], check[N], ct;

struct edge {
	int to, next;
}e[N*N];

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
	memset(dep, -1, sizeof(dep));
	memset(low, -1, sizeof(low));
	memset(vis, 0, sizeof(vis));
	memset(check, 0, sizeof(check));
}

void dfs(int k, int v, int f) {
	low[k] = dep[k] = v;
	for (int i = head[k]; i != -1; i = e[i].next) {
		if (!vis[e[i].to]) {
			vis[e[i].to] = 1;
			dfs(e[i].to, v + 1, k);
			low[k] = min(low[k], low[e[i].to]);
			if (k == 1)
				ct++;
			else if (low[e[i].to] >= dep[k]) {
				check[k] = 1;
			}
		}
		else {
			if (e[i].to != f && low[k] > dep[e[i].to])
				low[k] = dep[e[i].to];
		}
	}
}


void solve() {
	int n, k, v;
	
	while (~scanf("%d", &n) && n) {
		init();
		while (~scanf("%d", &k) && k) {
			while (getchar() != '\n') {
				scanf("%d", &v);
				add(k, v);
			}
		}
		ct = 0;
		vis[1] = 1;
		dfs(1, 1, -1);
		int ans = 0;
		for (int i = 1; i <= n; i++) {
			if (check[i])
				ans++;
		}
		if (ct > 1)
			ans++;
		printf("%d\n", ans);
	}
}

int main() 
{
	solve();
	return 0;
}