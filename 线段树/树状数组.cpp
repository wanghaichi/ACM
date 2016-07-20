#include<iostream>
#include<cstdio>
#include<string.h>
using namespace std;

const int N = 50001;
int a[N], b[N];
int n, m;
int lb(int i)
{
	return i & -i;	
}

void add(int v,int c)
{
	while(v <= n){
		b[v] += c;
		v += lb(v);
	}
}
int query(int v)
{
	int res = 0;
	while(v > 0){
		res += b[v];
		v -= lb(v);
	}
	return res;
}


int main()
{
	int T, cnt = 1;
	scanf("%d", &T);
	char s[5];
	while(T --){
		printf("Case %d:\n", cnt++);
		scanf("%d", &n);
		memset(b, 0, sizeof(b));
		for(int i  = 1; i <= n; i ++){
			scanf("%d", &a[i]);
			add(i, a[i]);
		}
		int x, y;
		while(~scanf("%s", s) && s[0] != 'E'){
			scanf("%d%d", &x, &y);
			if (s[0] == 'A'){
				add(x, y);
			}
			else if (s[0] == 'S'){
				add(x, -1*y);
			}
			else if (s[0] == 'Q'){
				printf("%d\n", query(y) - query(x-1));
			}
		}
	
		
	}
	return 0;	
}
