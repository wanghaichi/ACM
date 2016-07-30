/**
费用流，最小费用最大流

*/
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxe = 100000, maxv = 220, inf = 1000000000;

//que为模拟队列
int head[maxv], cnt, que[maxv], dis[maxv], vis[maxv], pre[maxv];

//c表示容量 w表示费用，注意是单位流量的费用
struct node{
	int next, to, c, w;
}e[maxe];

struct MinCostFlow{
	int S, T, n;
	void init(int _S, int _T){
		S = _S; T = _T;
		n = T + 1;
		for(int i = 0; i <= n; i ++) head[i] = -1;
		cnt = 0;
	}
	void add(int _u, int _v, int _c, int _w){
		e[cnt].to = _v;
		e[cnt].c = _c;
		e[cnt].w = _w;
		e[cnt].next = head[_u];
		head[_u] = cnt++;
		//建反向边的时候，容量为0，表示开始的时候不能通过，费用为-w表示通过走反向边可以“”反悔”
		e[cnt].to = _u;
		e[cnt].c = 0;
		e[cnt].w = -1 * _w;
		e[cnt].next = head[_v];
		head[_v] = cnt ++;
	}
	//用于寻找最短路径
	bool spfa(){
		int i, front = 0, tail = 1;
		for(i = 0; i <= n; i ++){
			dis[i] = inf;
			vis[i] = 0;
		}
		dis[S] = 0;
		que[0] = S;
		vis[S] = 1;
		while(tail != front){
			int u = que[front++];
			front %= maxv;
			for(i = head[u]; i != -1; i = e[i].next){
				int v = e[i].to;
				//若当前结点容量大于0，同时可以通过u结点和当前边进行松弛，则更新回溯数组pre，和最短路径dis
				if(e[i].c && dis[v] > dis[u] + e[i].w){
					dis[v] = dis[u] + e[i].w;
					pre[v] = i;
					if(!vis[v]){
						//通过vis数组标记，使得每个结点只会入队一次
						vis[v] = 1;
						que[tail++] = v;
						tail %= maxv;
					}
				}
			}
			vis[u] = 0;
		}
		//表示从源点到汇点之间不存在增广路了
		if(dis[T] == inf) return false;
		else return true;
	}
	int end(int &flow){
		int u, p, sum = inf, ans = 0;
		//通过T沿着spfa所求的最短路，找到该路径上流量最小的边，该值为这条增广路能够增广的流量
		for(u = T; u != S; u = e[p^1].to){
			p = pre[u];
			sum = min(sum, e[p].c);
		}
		//更新增广路上的边的属性，在spfa中记录的前驱是正向边，通过p^1找到反向边
		for(u = T; u != S; u = e[p^1].to){
			p = pre[u];
			e[p].c -= sum;
			e[p^1].c += sum;
			ans += sum*e[p].w;
		}
		flow += sum;
		return ans;
	}
	int solve(){
		int ans = 0, flow = 0;
		while(spfa()){
			ans += end(flow);
		}
		return ans;
	}
}F;

