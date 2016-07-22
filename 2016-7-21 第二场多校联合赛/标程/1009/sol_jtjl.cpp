#include<bits/stdc++.h> 

using namespace std;

const int MAXN = 2e3 + 10;

long long gcd(long long p, long long q){
	if (q == 0) return p;
	else return gcd(q, p % q);
}

int a[MAXN], b[MAXN];

int main(){
	int T;
	cin>>T;
	while(T--){
		int n, m;
		cin>>n>>m;
		for(int i = 1; i <= n; i++)
			a[i] = 100, b[i] = 0;
		b[1] = 1;
		a[n+1] = b[n+1] = 0;
		for(int i = 1; i <= m; i++){
			int x, y;
			scanf("%d%d", &x, &y);
			a[x] = b[x] = y;
		}
	//	puts("= -");
		int p = 3;
		while(a[p] != b[p])
			p++;
		int ans = 0, now = 0;
		for(int j = n; j >= p; j--){
			if (a[j] == b[j])
				now = a[j];
			else
				a[j] = b[j] = now;
			ans += a[j];
		}
	//	puts("= -");
		long long u = 0, v = ans;
		for(int i = now; i <= 100; i++)
			for(int j = max(i, b[2]); j <= min(a[2], 100); j++)
				for(int k = max(j, b[1]); k <= min(a[1], 100); k++)
					if ((j + k) * v >= (j + k + ans + i * (p - 3)) * u){
						u = j + k;
						v = (j + k + ans + i * (p - 3));
					}
	//	puts("= -");
		long long w = gcd(u, v);
		if (w == 0){
			v = 1, u = 0;
		}			
		else{
			v /= w, u /= w;
		}
		printf("%lld/%lld\n", u, v);
	}
	return 0;
}
