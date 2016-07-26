#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int maxe = 100000, maxv = 100000, inf = 1e9;

int ne, nv, tmp, s, t, index;
struct node{
	int next, pair, v, cap, flow;
}e[maxe];

int net[maxv];

int isap(){
	int numb[maxv], dist[maxv], curedge[maxv], pre[maxv];
	int cur_flow, max_flow, u, tmp, neck, i;
	memset(dist, 0, sizeof(dist));
	memset(numb, 0, sizeof(numb));
	memset(pre, -1, sizeof(pre));
	for(int i = 1; i <= nv; i ++){
		curedge[i] = net[i];
	}
	numb[nv] = nv;
	max_flow = 0;
	u = s;
	while(dist[s] < nv){
		if(u == t){
			cur_flow = inf;
			for(i = s; i != t; i = e[curedge[i]].v){
				if(cur_flow > e[curedge[i]].cap){
					neck = i;
					cur_flow = edge[curedge[i]].cap;
				}
			}
			for(i = s; i != t; i = e[curedge[i]].v){
				tmp = curedge[i];
				e[tmp].cap -= cur_flow;
				e[tmp].flow += cur_flow;
				tmp = e[tmp].pair;
				e[tmp].cap += cur_flow;
				e[tmp].flow -= cur_flow;
			}
			max_flow += cur_flow;
			u = neck;
		}
		for(i = curedge[u]; i != -1; i = e[i].next)
			if(edge[i].cap > 0 && dist[u] == dist[e[i].v] + 1) break;
		if(i != -1){
			curedge[u] = i;
			pre[edge[i].v] = u;
			u = e[i].v;
		}
		else{
			if(0 == --numb[dist[u]]) break;
			curedge[u] = net[u];
			for(tmp = nv, i = net[u]; i != -1; i = e[i].next){
				if(e[i].cap > 0){
					tmp = tmp < dist[e[i].v] ? tmp : dist[edge[i].v];
				}
			}
			dist[u] = tmp + 1;
			++numb[dist[u]];
			if(u != s) u = pre[u];
		}
	}
	return max_flow;
}






