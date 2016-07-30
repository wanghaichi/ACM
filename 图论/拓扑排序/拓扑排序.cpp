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
const int N = 510;
int n, m, s[N], a, b;
int head[N], cnt;

struct edge {
	int to, next;
}e[N*N];

void add(int u, int v) {
	e[cnt].to = v;
	e[cnt].next = head[u];
	head[u] = cnt++;
}

void init() {
	cnt = 0;
	memset(head, -1, sizeof(head));
	memset(s, 0, sizeof(s));
}

int getm(int *t) { //找到当前入度最小的点返回
	int res = 10000, pos;
	for (int i = 1; i <= n; i++) {
		if (t[i] == -1)
			continue;
		if (res > t[i]) {
			pos = i;
			res = t[i];
		}
	}
	return pos;
}

void solve() {
	while (~scanf("%d%d", &n, &m)) {
		init();
		for (int i = 0; i < m; i++) {
			scanf("%d%d", &a, &b);
			add(a, b);
			s[b]++;
		}
		
		for (int i = 0; i < n; i++) {
			int pos = getm(s);
			printf("%d", pos);
			if (i != n - 1)
				printf(" ");
			else
				break;
			for (int j = head[pos]; j != -1; j = e[j].next) { //根据当前入度最小的点更新与其相连的点的入度
				s[e[j].to]--;
			}
			s[pos] --;
		}
		printf("\n");

	}


	return;
}

int main() 
{
	solve();
	return 0;
}
