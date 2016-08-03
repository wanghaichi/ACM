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

int head[N], cnt, vis[N], linker[N], n, m, u0, v0, pipei[N];

struct node {
	int to, next;
}e[N*N];

void init() {
	cnt = 0;
	memset(head, -1, sizeof(head));
	memset(linker, -1, sizeof(linker));
	memset(pipei, 0, sizeof(pipei));
	u0 = v0 = -1;
}

void add(int u, int v) {
	e[cnt].to = v;
	e[cnt].next = head[u];
	head[u] = cnt++;
}

bool dfs(int v) {
	for (int i = head[v]; i != -1; i = e[i].next) {
		if (v == u0 && e[i].to == v0) {
			continue;
		}
		if (!vis[e[i].to]) {
			vis[e[i].to] = 1;
			if (linker[e[i].to] == -1 || dfs(linker[e[i].to])) {
				linker[e[i].to] = v;
				pipei[v] = 1;
				return true;
			}
		}
	}
	return false;
}

void solve() {
	int u, v, cnt = 1, k;
	while (~scanf("%d%d%d", &n, &m, &k)) {
		init();
		for (int i = 0; i < k; i++) {
			scanf("%d%d", &u, &v);
			add(u, v);
		}

		int tans = 0,ans = 0, tmp;
		for (int i = 1; i <= n; i++) {
			memset(vis, 0, sizeof(vis));
			if (dfs(i))
				tans++;
		}
		//依次遍历每一个匹配边，找到重要的匹配边（即重要点）
		for (int i = 1; i <= m; i++) {
			tmp = 0;
			if (linker[i] == -1)
				continue;
			u0 = linker[i];
			v0 = i;
			linker[i] = -1;
			pipei[u0] = 0;
			//每次从一个未匹配点出发，寻找增广路，若找到则说明该点存在于所有的最大匹配中
			for (int j = 1; j <= n; j ++) {
				if (!pipei[j]) {
					memset(vis, 0, sizeof(vis));
					if (dfs(j)) {
						tmp = 1;
						break;
					}
				}
			}
			if (tmp == 0) {
				ans++;
				linker[i] = u0;
				pipei[u0] = 1;
			}
		}
		printf("Board %d have %d important blanks for %d chessmen.\n", cnt++, ans, tans);

	}
	return;
}

int main() 
{
	solve();
	return 0;
}