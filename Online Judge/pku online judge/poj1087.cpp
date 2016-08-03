#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <map>
#include <string>
using namespace std;

const int maxe = 250000, maxv = 500;
const int mod = 1e9+7;
const int inf = 1e9;

int head[maxv], cnt;
struct node{
	int next, to, c;
}e[maxe];

struct Max_flow{
	int S, T, n;
	int lev[maxv], q[maxv], cur[maxv], f;
	void init(int _S, int _T){
		cnt = 0;
		S = _S;
		T = _T;
		n = T + 1;
		for(int i = 0; i <= n; i ++) head[i] = -1;
	}
	void add(int u, int v, int c){
		e[cnt].to = v;
		e[cnt].c = c;
		e[cnt].next = head[u];
		head[u] = cnt++;

		e[cnt].to = u;
		e[cnt].c = 0;
		e[cnt].next = head[v];
		head[v] = cnt++;
	}
	bool bfs(){
		for(int i = 0; i <= n; i ++) lev[i] = 0;
		lev[S] = 1;
		f = 0;
		q[f++] = S;
		for(int i = 0; i < f; i ++){
			int u = q[i];
			for(int j = head[u]; j != -1; j = e[j].next){
				int v = e[j].to;
				if(lev[v] == 0 && e[j].c > 0){
					lev[v] = lev[u] + 1;
					q[f++] = v;
					if(v == T)
						return true;
				}
			
			}
		}
		return false;
	}
	int dfs(int u, int f){
		if(u == T) return f;
		int tag = 0, c;
		for(int &i = cur[u]; i != -1; i = e[i].next){
			int v = e[i].to;
			if(lev[v] == lev[u] + 1 && e[i].c > 0){
				c = dfs(v, min(f - tag, e[i].c));
				e[i].c -= c;
				e[i^1].c += c;
				tag += c;
				if(tag == f) return tag;
			}
		}
		return tag;
	}
	int solve(){
		int ans = 0;
		while(bfs()){
			for(int i = 0; i <= n; i ++) cur[i] = head[i];
			ans += dfs(S, inf);
		}
		return ans;
	}
}Flow;

map<string, int> ma;
int main()
{
	int n, m, k;
	string tmp, u, v;
	cin >> n;
	int S = 1, T = 410, ctplu = 2, ctdev = 302;
	Flow.init(S, T);
	for(int i = 0; i < n; i ++){
		cin >> tmp;
		Flow.add(ctplu, T, 1);
		ma[tmp] = ctplu++;
	}
	cin >> m;
	for(int i = 0; i < m; i ++){
		cin >> u >> v;
		Flow.add(S, ctdev, 1);
		ma[u] = ctdev++;
		if(ma[v] == 0){
			ma[v] = ctplu++;
		}
		Flow.add(ma[u], ma[v], 1);
	}
	cin >> k;
	for(int i = 0; i < k; i ++){
		cin >> u >> v;
		if(ma[u] == 0) {
			ma[u] = ctplu++;
		}
		if(ma[v] == 0){
			ma[v] = ctplu++;
		}
		Flow.add(ma[u], ma[v], inf);
	}
	cout << m - Flow.solve() << endl;
	return 0;
}




