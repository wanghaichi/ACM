#include<bits/stdc++.h>
using namespace std;
const int N = 1e6+448;
int r;

int p[N];
int v[N], ts;
void dfs(int now, int mul = 1) {
	if(now * mul <= r)
		return;
	if(now == 1) {
		if(v[mul] == ts) r = mul;
		v[mul] = ts;
		return;
	}
	int p = ::p[now];
	do {
		now /= p;
		mul *= p; 
	} while(now % p == 0);
	while(true) {
		dfs(now, mul);
		if(mul % p) return;
		mul /= p;
	}
}

int main() {
	int T, n, a[2048];
	for(int i = 2; i < N; ++i) if(!p[i])
		for(int64_t j = (p[i] = i) * int64_t(i); j < N; j += i)
			p[j] = i;	
	for(scanf("%d", &T); T--; ) {
		++ts;
		scanf("%d", &n);
		r = 1;
		for(int i = 0; i < n; ++i) scanf("%d", a + i);
		sort(a, a + n);
		int s;
		for(s = n - 1; s; --s)
		if(a[s] == a[s-1]) {
			r = a[s];
			break;
		}
		for(int i = s; i < n; ++i)
			dfs(a[i]);
		printf("%d\n", r);
	}
}
