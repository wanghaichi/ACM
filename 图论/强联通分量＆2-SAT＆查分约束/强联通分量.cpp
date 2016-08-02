/*
	poj2553 强联通分量

	求解出度为零的强联通分量

	Tarjan算法
*/


#include <iostream>
#include <cstdio>
#include <cstring>
#include <stack>
#define CL(a) memset(a, 0, sizeof(a))
#define CF(a) memset(a, -1, sizeof(a))
using namespace std;

const int maxv = 5001, maxe = 5001 * 5001;
int head[maxv], cnt, dep;
struct egde{
	int next, to;
}e[maxe];

void add(int _u, int _v){
	e[cnt].to = _v;
	e[cnt].next = head[_u];
	head[_u] = cnt++;
}
//dfn保存每个节点的搜索时间，sccsno保存缩点后的序号，sccout保存缩点后每个点的出度
int dfn[maxv], low[maxv], sccsno[maxv], scnt, sccout[maxv];
//保存当前在搜索树中的点
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
	//若当前点的low与dfn相等，则说明以当前点为根的搜索子树属于同一个强联通分量
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
	while(~scanf("%d", &n) && n){
		scanf("%d", &m);
		init();
		int u, v;
		for(int i = 0; i < m; i ++){
			scanf("%d%d", &u, &v);
			add(u, v);
		}
		getScc(n);
		//记录缩点后每个强联通分量的出度
		for(int i = 1; i <= n; i ++){
			for(int j = head[i]; j != -1; j = e[j].next){
				int v = e[j].to;
				if(sccsno[i] == sccsno[v])
					continue;
				sccout[sccsno[i]]++;
			}
		}
		for(int i = 1; i <= n; i ++){
			if(!sccout[sccsno[i]])
				printf("%d ", i);
		}
		printf("\n");
	}
	return 0;	
}
