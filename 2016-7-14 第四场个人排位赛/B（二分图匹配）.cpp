// ACMdata.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<algorithm>
#include<cstdio>
#include <cstring>
#include <cmath>

using namespace std;
typedef long long ll;
const int N = 200;

struct node {
	char s[6];
}ch[N];

int head[N], cnt, vis[N], linker[N];
char s[25], sto[N][6], tmp;
struct edge {
	int to, next;
}e[32000];

void add(int u, int v) {
	e[cnt].to = v;
	e[cnt].next = head[u];
	head[u] = cnt++;

	e[cnt].to = u;
	e[cnt].next = head[v];
	head[v] = cnt++;
}
void init() {
	memset(head, -1, sizeof(head));
	cnt = 0;
}
//匈牙利算法，寻找增光路，dfs版本
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



int main()	
{

	int n;
	scanf("%s %d", s, &n);
	init();
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < 6; i++) {
			while (scanf("%c", &tmp) && (tmp == ' ' || tmp == '\n'));
			for (int j = 0; s[j]; j++) {
				if (s[j] == tmp) {
					add(j, 26 + k);
				}
			}
		}
	}

	memset(linker, -1, sizeof(linker));
	int ans = 0;
	for (int i = 0; s[i]; i++) {
		memset(vis, 0, sizeof(vis));
		vis[i] = 1;
		if (dfs(i))
			ans++;
	}
	if (ans == strlen(s))
		puts("YES");
	else
		puts("NO");

    return 0;
}
