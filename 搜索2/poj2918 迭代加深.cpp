#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int maxn = 400000;
int cantor[9] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320};
int vis[maxn], des = 0;


struct node{
	int ma[3][3], hash, h, d;
	node(){}

	bool operator < (const node& n1) const{
		return h > n1.h;
	}

	void get_h(){
		char k = 1;
		int res = 0;
		for(int i = 0; i < 3; i ++)
			for(int j = 0; j < 3; j ++)
				if(ma[i][j] == k++)
					res ++;
		h = (res + 3) / 4;
	}
	void getHash(){
		hash = 0;
		int a[9], k = 0;
		for(int i = 0; i < 3; i ++ )
			for(int j = 0; j < 3; j ++)
				a[k++] = ma[i][j];
		for(int i = 0; i < 9; i ++){
			k = 0;
			for(int j = 0; j < i; j ++){
				if(a[i] < a[j])
					k ++;
			}
			hash += cantor[i] * k;
		}
	}
	void Al(){
		Lroutate(0, 0);
	}
	void Ar(){
		Rroutate(0, 0);
	}
	void Bl(){
		Lroutate(0, 1);
	}
	void Br(){
		Rroutate(0, 1);
	}
	void Cl(){
		Lroutate(1, 0);
	}
	void Cr(){
		Rroutate(1, 0);
	}
	void Dl(){
		Lroutate(1, 1);
	}
	void Dr(){
		Rroutate(1, 1);
	}
	void Rroutate(int i, int j){
		int tmp = ma[i][j];
		ma[i][j] = ma[i+1][j];
		ma[i+1][j] = ma[i+1][j+1];
		ma[i+1][j+1] = ma[i][j+1];
		ma[i][j+1] = tmp;
	}
	void Lroutate(int i, int j){
		int tmp = ma[i][j];
		ma[i][j] = ma[i][j+1];
		ma[i][j+1] = ma[i+1][j+1];
		ma[i+1][j+1] = ma[i+1][j];
		ma[i+1][j] = tmp;
	}
	void routate(int i){
		switch(i){
			case 0:
				Al();
				break;
			case 1:
				Ar();
				break;
			case 2:
				Bl();
				break;
			case 3:
				Br();
				break;
			case 4:
				Cl();
				break;
			case 5:
				Cr();
				break;
			case 6:
				Dl();
				break;
			case 7:
				Dr();
				break;
		}
	}
};

bool bfs(node u, int mind){
	priority_queue<node> q;
	q.push(u);
	vis[u.hash] = 1;
	while(!q.empty()){
		node cur = q.top();
		q.pop();
		if(cur.hash == des)
			return true;
		if(cur.d >= mind)
			continue;
		for(int i = 0; i < 8; i ++){
			node v = cur;
			v.routate(i);
			v.getHash();
			v.get_h();
			v.d++;
			if(!vis[v.hash]){
				vis[v.hash] = 1;
				q.push(v);
			}
		}
	}
	return false;
}

int main()
{
	char s[15];
	int count = 1;
	while(~scanf("%s", s) && s[1] != '0'){
		int k = s[0] - '0';
		node st;
		int ct = 1;
		for(int i = 0; i < 3; i ++){
			for(int j = 0; j < 3; j ++){
				st.ma[i][j] = s[ct++] - '0';
			}
		}
		st.getHash();
		st.get_h();
		st.d = 0;
		if(st.hash == des){
			printf("%d. 0\n", count++);
			continue;
		}
		if(k == 0){
			printf("%d. -1\n", count++);
			continue;
		}
		bool flag = false;
		int i;
		for(i = 1; i <= k; i ++){
			memset(vis, 0, sizeof(vis));
			if(bfs(st, i)){
				flag = true;
				break;
			}
		}
		if(flag){
			printf("%d. %d\n", count++, i);
		}
		else
			printf("%d. -1\n", count++);
	}
	return 0;
}
