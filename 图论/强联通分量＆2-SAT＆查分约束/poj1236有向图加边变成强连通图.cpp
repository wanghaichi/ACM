/******poj1236******************

给出一个有向图
首先求强联通分量并缩点得到DAG图

第一问求入度为0的点

第二问求至少加上多少条边能够变成SCC图

SCC图要求每个点的入度和出度都不能为０

显然答案为入度和出度为０的点多的那个（在出度为零的点和入度为零的点连上一条边）

***************************/




#include <iostream>
#include <cstdio>
#include <cstring>
#include <stack>
#define CL(a) memset(a, 0, sizeof(a))
#define CF(a) memset(a, -1, sizeof(a))
using namespace std;

const int maxv = 110, maxe = 110 * 110;
int head[maxv], cnt, dep;
struct egde{
	int next, to;
}e[maxe];

void add(int _u, int _v){
	e[cnt].to = _v;
	e[cnt].next = head[_u];
	head[_u] = cnt++;
}
int dfn[maxv], low[maxv], sccsno[maxv], scnt, sccout[maxv], sccin[maxv];
stack<int> s;
void Tarjan(int _u){
	dfn[_u] = low[_u] = ++dep;
	s.push(_u);
	for(int i = head[_u]; i != -1; i = e[i].next){
		int v = e[i].to;
		if(!dfn[v]){
			Tarjan(v);
			low[_u] = min(low[_u], low[v]);
		}
		else if (!sccsno[v]){
			low[_u] = min(low[_u], dfn[v]);
		}
	}
	if(low[_u] == dfn[_u]){
		scnt++;
		int v;
		do{
			v = s.top();
			s.pop();
			sccsno[v] = scnt;
		}while(v != _u);
	}
}

void init(){
	cnt = dep = scnt = 0;
	CF(head);
	CL(sccsno);
	CL(dfn);
	CL(low);
	CL(sccout);
	CL(sccin);
}

void getScc(int n){
	for(int i = 1; i <= n; i ++){
		if(!dfn[i]){
			Tarjan(i);
		}
	}
}

int main()
{
	int n, m;
	scanf("%d", &n);
	init();
	int u, v;
	for(int i = 1; i <= n; i ++){
		while(~scanf("%d", &v) && v){
			add(i, v);	
		}
	}
	
	getScc(n);
	for(int i = 1; i <= n; i ++){
		for(int j = head[i]; j  != -1; j = e[j].next){
			if(sccsno[i] == sccsno[e[j].to])
				continue;
			sccout[sccsno[i]]++;
			sccin[sccsno[e[j].to]]++;
		}
	}
	int ans1 = 0, ans2 = 0;
	for(int i = 1; i <= scnt; i ++){	
		if(sccout[i] == 0){
			ans1++;
		}
		if (sccin[i] == 0){
			ans2 ++;
		}
	}
	ans1 = max(ans1, ans2);
	if(scnt == 1)
		ans1 = 0;
	printf("%d\n%d\n", ans2, ans1);
	return 0;	
}
