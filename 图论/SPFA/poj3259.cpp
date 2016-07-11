// Acm.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#define inf 10000000
using namespace std;

int T, n, m, w, s, e, t, cnt = 0;

vector<pair<int, int> > edge[501];

bool spfa()
{
	int dist[501];
	int vis[501];
	memset(vis, 0, sizeof(vis));
	for (int i = 1; i <= n; i++)
		dist[i] = inf;
	dist[1] = 0;
	bool flag = true;
	queue<int>q;
	q.push(1);
	vis[1] ++;
	while (!q.empty() && flag) {
		int cur = q.front();
		q.pop();
		for (unsigned int i = 0; i < edge[cur].size(); i++) {
			int to = edge[cur][i].first;
			int cost = edge[cur][i].second;
			if (dist[to] > cost + dist[cur]) {
				q.push(to);
				dist[to] = cost + dist[cur];
				vis[to]++;
				if (vis[to] == n)
					flag = false;
			}
		}
	}
	return flag;
	
}

int main()
{
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d", &n, &m, &w);
		for (int i = 1; i <= n; i++) {
			edge[i].clear();
		}
		for (int i = 0; i < m; i++) {
			scanf("%d%d%d", &s, &e, &t);
			edge[s].push_back(make_pair(e, t));
			edge[e].push_back(make_pair(s, t));
 		}
		for (int i = 0; i < w; i++) {
			scanf("%d%d%d", &s, &e, &t);
			edge[s].push_back(make_pair(e, -t));
		}
		if (spfa())
			puts("NO");
		else
			puts("YES");
		
	}
    return 0;
}
