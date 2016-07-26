#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxe = 100000, maxv = 220, inf = 1000000000;

int head[maxv], cnt, que[maxv], dis[maxv], vis[maxv], pre[maxv];

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

		e[cnt].to = _u;
		e[cnt].c = 0;
		e[cnt].w = -1 * _w;
		e[cnt].next = head[_v];
		head[_v] = cnt ++;
	}
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
				if(e[i].c && dis[v] > dis[u] + e[i].w){
					dis[v] = dis[u] + e[i].w;
					pre[v] = i;
					if(!vis[v]){
						vis[v] = 1;
						que[tail++] = v;
						tail %= maxv;
					}
				}
			}
			vis[u] = 0;
		}
		if(dis[T] == inf) return false;
		else return true;
	}
	int end(int &flow){
		int u, p, sum = inf, ans = 0;
		for(u = T; u != S; u = e[p^1].to){
			p = pre[u];
			sum = min(sum, e[p].c);
		}
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

int n, m, pp, hh;
char ch[111][111];
int X[111], Y[111];

int main()
{
	while(scanf("%d%d", &n, &m) && n){
		pp = hh = 0;
		F.init(maxv-2, maxv-3);
		for(int i = 0; i < n; i ++){
			scanf("%s", ch[i]);
			for(int j = 0; j < m; j ++){
				if(ch[i][j] == 'H'){
					F.add(F.S, hh, 1, 0);
					X[hh] = i;
					Y[hh++] = j;
				}
			}
		}
		for(int i = 0; i < n; i ++){
			for(int j = 0; j < m; j++){
				if(ch[i][j] == 'm'){
					F.add(hh+pp, F.T, 1, 0);
					for(int k = 0; k < hh; k ++){
						F.add(k, hh+pp, 1, abs(i-X[k]) + abs(j - Y[k]));
					}
					pp++;
				}
			}
		}
		printf("%d\n", F.solve());
	}
	return 0;
}
