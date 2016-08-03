// ACMdata.cpp : 定义控制台应用程序的入口点。
//不明确二分图中的节点属于哪个集合，于是双向建边，这样求得的最大匹配数为2倍

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
const int N = 210;

int head[N], cnt, vis[N], linker[N], judge[N], n, m;

struct node {
	int to, next;
}e[N*N];

void init() {
	cnt = 0;
	memset(head, -1, sizeof(head));
	memset(linker, -1, sizeof(linker));
	memset(judge, -1, sizeof(judge));
}

void add(int u, int v) {
	e[cnt].to = v;
	e[cnt].next = head[u];
	head[u] = cnt++;

	e[cnt].to = u;
	e[cnt].next = head[v];
	head[v] = cnt++;
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

bool panduan() {
	for (int i = 1; i <= n; i++) {
		if (judge[i] == -1) {
			judge[i] = 0;
		}
		for (int j = head[i]; j != -1; j = e[j].next) {
			if (judge[e[j].to] == -1) {
				judge[e[j].to] = judge[i] ^ 1;
			}
			else if (judge[e[j].to] == judge[i]) {
				return false;
			}
		}
	}
	return true;
}

void solve() {
	int u, v;
	while (~scanf("%d%d", &n, &m)) {
		init();
		for (int i = 0; i < m; i++) {
			scanf("%d%d", &u, &v);
			add(u, v);
		}
		if (!panduan()) {
			puts("No");
			continue;
		}
		int ans = 0;
		for (int i = 1; i <= n; i++) {
			memset(vis, 0, sizeof(vis));
			if (dfs(i))
				ans++;
		}
		printf("%d\n", ans / 2); //双向建边，所得的最大匹配除以二
	}
	return;
}

int main() 
{
	solve();
	return 0;
}