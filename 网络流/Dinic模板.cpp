/**poj3281****
求网络流最大流的Dinic算法，难点在于拆点建边
*/
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxe = 250000, maxv = 500;
const int mod = 1e9+7;
const int inf = 1e9;

int head[maxv], cnt;
struct node{
	int next, to, c;
}e[maxe];
//Dinic算法求最大流核心部分
struct Max_flow{
	//S表示源点 T表示汇点 n表示总点数
	int S, T, n;
	//lev标记距离源点S的层次 q为模拟队列 cur用来优化边（大神的代码）
	int lev[maxv], q[maxv], cur[maxv], f;
	void init(int _S, int _T){
		cnt = 0;
		S = _S;
		T = _T;
		n = T + 1;
		for(int i = 0; i <= n; i ++) head[i] = -1;
	}
	//建边的时候注意加上反向边，并将反向边容量标记为0
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
	//每次dfs寻找增广路前都需要用bfs更新每个点的层次
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
					//表示更新到了汇点
					if(v == T)
						return true;
				}
			}
		}
		//若没有更新到汇点，说明已经不存在增光路径了
		return false;
	}
	//从当前点出发，在残余网络中寻找新的增广路，每次寻找可能找到多条增光路，记录在tag中，f表示寻找到当前节点所能流过的最大流量
	int dfs(int u, int f){
		//表示寻找到了汇点，返回
		if(u == T) return f;
		int tag = 0, c;
		//这里注意这个神器的取地址符号，因为对于一条边而言，从当前节点出发走过一次的时候，要么将这条边流满，要么dfs结束（min（f-tag, e[i]-c）），因此这条边在本次dfs中肯定不会用到第二次，所以加上取址更新cur，使得每条边至多走过一次
		for(int &i = cur[u]; i != -1; i = e[i].next){
			int v = e[i].to;
			if(lev[v] == lev[u] + 1 && e[i].c > 0){
				c = dfs(v, min(f - tag, e[i].c));
				//注意更新反向边
				e[i].c -= c;
				e[i^1].c += c;
				tag += c;
				//表示当前所有的流量都已经流走
				if(tag == f) return tag;
			}
		}
		return tag;
	}
	int solve(){
		int ans = 0;
		//每次使用bfs更新节点，若不能到达汇点算法结束
		while(bfs()){
			for(int i = 0; i <= n; i ++) cur[i] = head[i];
			ans += dfs(S, inf);
		}
		return ans;
	}
}Flow;


int main()
{
	//此处涉及到点序号的分配，1为源点S， 2~2+2*n-1 为牛的点（每个点需要拆成两个点）， 2*n+2 ~ 2*n+2+f-1 为实物，2*n+2+f ~ 2*n+2+f+d-1 为饮料的点，2+2*n+f+d 为汇点T 
	int n, f, d, tmp, t, tf, td;
	scanf("%d%d%d", &n, &f, &d);
	t = 2+f+2*n+d;
	Flow.init(1, t);
	//建立源点到食物的边
	for(int i = 1; i <= f; i++){
		int v = 2+2*n+i-1;
		Flow.add(1, v, 1);
	}
	//建立饮料到汇点的边
	for(int j = 1; j <= d; j ++){
		int v = 2+2*n+f+j-1;
		Flow.add(v, t, 1);
	}
	for(int i = 0; i < n; i ++){
		int cv1 = 2 + (2*i), cv2 = 2+ (2*i+1);
		//建立拆点之间的边
		Flow.add(cv1, cv2, 1);
		scanf("%d%d", &tf, &td);
		for(int j = 1; j <= tf; j ++){
			scanf("%d", &tmp);
			int v = 2+2*n+tmp-1;
			Flow.add(v, cv1, 1);
		}
		for(int j = 1; j <= td; j ++){
			scanf("%d", &tmp);
			int v = 2+2*n+f+tmp-1;
			Flow.add(cv2, v, 1);
		}
	}
	printf("%d\n", Flow.solve());
	return 0;
}
