/**************************************************************

AUTHOR: Hardy

TIME: 2016年 08月 05日 星期五 15:58:45 CST

ID: sgu 520

TYPE: dfs + bfs + 博弈

DETAIL: 给定五向有环图，保证任意两点连通。1点为首都，火势从首都向相邻城市
蔓延。两个人操控一个机器人，每天向相邻的城市走，直到不能走为止。着火的城市
不能走。

TACTICS: 通过bfs标记每一个点到1的距离，每次只能向距离大1的点走。考虑当前步
数的奇偶性，N先走，因此距离为奇数的叶子节点是N的必胜态，偶数的是V的必胜态。
dfs每一条路径，对于每一个点，若当前该N走，则从当前点若能到达N的必胜态，则
该点为必胜态。V点一样。dfs回溯更新每一个点的必胜状态。

***************************************************************/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a > b ? b : a)
#define CL(a) memset(a, 0, sizeof(a));

using namespace std;

typedef long long ll;

const int inf = 1e9+7;
const int mod = 1e9+7;
const int maxn = 1e4+7, maxe = 1e4+7, maxv = 1e4+7;

int head[maxv], cnt, dis[maxv], match[maxv];

struct edge{
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
	memset(head, -1, sizeof(head));
	memset(match, -1, sizeof(match));
	CL(dis);
	cnt = 0;
}

void bfs(){
	queue<int> q;
	q.push(1);
	while(!q.empty()){
		int tmp = q.front();
		q.pop();
		for(int i = head[tmp]; i != -1; i = e[i].next){
			int v = e[i].to;
			if(dis[v] || v == 1)
				continue;
			dis[v] = dis[tmp] + 1;
			q.push(v);
		}
	}
}

void dfs(int u){
	bool flag = false;
	for(int i = head[u]; i != -1; i = e[i].next){
		int v = e[i].to;
		if(dis[v] == dis[u] + 1)
			dfs(v);
		else
			continue;
		if(dis[u] % 2 == match[v])
			flag = true;
	}
	if(!flag){
		match[u] = (dis[u] + 1) % 2;
	}
	else{
		match[u] = dis[u] % 2;
	}
}

int main()
{
	int n, m, u, v;
	init();
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; i ++){
		scanf("%d%d", &u, &v);
		add(u, v);
	}
	bfs();
	dfs(1);
	if(match[1] == 1)
		puts("Nikolay");
	else
		puts("Vladimir");
	return 0;
}








