#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

const int maxv = 1e3+7, maxe = 1e5+7, inf = 1e9;
int head[maxv], head1[maxv], cnt, dist[maxe], S, T, k, pcount;
struct edge{
	int next, to, w;
	edge(){}
	edge(int _next, int _to, int _w):next(_next),to(_to),w(_w){}
}e[maxe * 2];

void add(int _u, int _v, int _w){
	e[cnt].to = _v;
	e[cnt].w = _w;
	e[cnt].next = head[_u];
	head[_u] = cnt++;

	e[cnt].to = _u;
	e[cnt].w = _w;
	e[cnt].next = head1[_v];
	head1[_v] = cnt++;
}

void Dijstra(){
	queue<int> q;
	dist[T] = 0;
	q.push(T);
	while(!q.empty()){
		int u = q.front();
		q.pop();
		for(int i = head1[u]; i != -1; i = e[i].next){
			int v = e[i].to;
			if(dist[v] > dist[u] + e[i].w){
				q.push(v);
				dist[v] = dist[u] + e[i].w;
			}
		}
	}
}

void init(int n){
	pcount = cnt = 0;
	for(int i = 0; i <= n; i ++){
		head[i] = head1[i] = -1;
		dist[i] = inf;
	}
}

struct node{
	int u, f, h, g;
	void cal_f(){
		f = h + g;
	}
	node(int _u, int _h, int _g):u(_u), h(_h), g(_g){}
};
struct cmp{
	bool operator () (const node& n1, const node& n2) const{
		return n1.f == n2.f ? n1.h > n2.h : n1.f > n2.f;
	}	
};
int a_star(){
	priority_queue<node, vector<node>, cmp > q;
	node st(S, dist[S], 0);
	st.cal_f();
	q.push(st);
	while(!q.empty()){
		node cur = q.top();
		q.pop();
		int u = cur.u;
		if(u == T){
			pcount ++;
			if(pcount == k)
				return cur.g;
		}
		for(int i = head[u]; i != -1; i = e[i].next){
			if(dist[e[i].to] == inf)
				continue;
			node v(e[i].to, dist[e[i].to], cur.g + e[i].w);
			v.cal_f();
			q.push(v);
		}
	}
	return -1;
}


int main()
{
	int n, m, u, v, t;
	scanf("%d%d", &n, &m);
	init(n);
	for(int i = 1; i <= m; i ++){
		scanf("%d%d%d", &u, &v, &t);
		add(u, v, t);
	}
	scanf("%d%d%d", &S, &T, &k);
	if(S == T)
		k ++;
	Dijstra();
	if(dist[S] == inf)
		puts("-1");
	else{
		printf("%d\n", a_star());
	}
	return 0;
}
