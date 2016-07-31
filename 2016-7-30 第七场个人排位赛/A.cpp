#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

const int maxn = 1e6+7;

typedef long long ll;
int vis[5005], sto[100010];
int main()
{
	int T, n, m;
	scanf("%d", &T);
	while(T --){
		int tmp;
		scanf("%d%d", &n, &m);
		sto[0] = 0;
		for(int i = 1; i <= n; i ++){
			scanf("%d", &sto[i]);
			sto[i] += sto[i-1];
		}
		memset(vis, 0, sizeof(vis));
		bool flag = false;
		for(int i = 1; i <= n && !flag; i ++){
			sto[i] %= m;
			vis[sto[i]]++;
			if(vis[sto[i]] == 2)
				flag = true;
		}
		if(flag)
			puts("YES");
		else
			puts("NO");
	}
	return 0;
}

