// Acm.cpp : 定义控制台应用程序的入口点。
// 不能用vector存边，会超，老老实实用邻接表

#include "stdafx.h"
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#define inf 10000000000
using namespace std;
typedef long long ll;


struct node
{
	int to;
	ll cost;
	node(int a, ll b) :to(a), cost(b) {}
};

struct cmp
{
	bool operator()(const node& n1, const node& n2) {
		return n1.cost > n2.cost;
	}
};
ll w[50001];
int cnt, head[50001];
struct edg
{
	int to, next;
	ll cost;
}edge[100011];
void init()
{
	cnt = 0;
	memset(head, -1, sizeof(head));
}
void add(int fr, int to, ll cost) {
	edge[cnt].to = to;
	edge[cnt].cost = cost;
	edge[cnt].next = head[fr];
	head[fr] = cnt++;

	edge[cnt].to = fr;
	edge[cnt].cost = cost;
	edge[cnt].next = head[to];
	head[to] = cnt++;
}


int main()
{
	int T, v, e, a, b;
	ll  c;
	scanf("%d", &T);
	while (T--) {
		init();
		scanf("%d%d", &v, &e);

		for (int i = 1; i <= v; i++)
			scanf("%I64d", &w[i]);
		for (int i = 0; i < e; i++) {
			scanf("%d%d%I64d", &a, &b, &c);
			add(a, b, c);
		}
		ll dist[50001];
		for (int i = 1; i <= v; i++)
			dist[i] = inf;
		dist[1] = 0;
		priority_queue<node, vector<node>, cmp> q;
		q.push(node(1, 0));
		while (!q.empty()) {
			int cur = q.top().to;
			q.pop();
			for (int i = head[cur]; i != -1; i = edge[i].next) {
				int to = edge[i].to;
				ll cost = edge[i].cost;
				if (dist[to] < dist[cur] + cost)
					continue;
				dist[to] = dist[cur] + cost;
				q.push(node(to, dist[to]));
			}
		}
		ll ans = 0;
		bool flag = true;
		for (int i = 1; i <= v && flag; i++) {
			if (dist[i] == inf)
				flag = false;
			else {
				ans += (dist[i] * w[i]);
			}
		}
		if (flag)
			printf("%I64d\n", ans);
		else
			puts("No Answer");

	}
	return 0;
}
