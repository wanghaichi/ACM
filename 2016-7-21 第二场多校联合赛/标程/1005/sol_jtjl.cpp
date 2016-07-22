#include<bits/stdc++.h>

using namespace std;

struct Pt{
	long long x, y;
};

typedef pair<long long, long long> PLL;

const int MAXN = 1e3 + 10;
const int MM = 1e9 + 7;

Pt a[MAXN];
map<PLL, int> mp;

long long gcd(long long p, long long q){
	return q ? gcd(q, p % q) : p;
}

void upd(long long &x, long long y){
	x += y;
	if (x >= MM) x -= MM;
}

long long pw(long long p){
	if (p == 0) return 1;
	long long tt = pw(p / 2);
	tt = tt * tt % MM;
	if (p & 1) return tt * 2 % MM;
	else return tt;
}

int main(){
	int T;
	cin>>T;
	while(T--){
		int n;
		scanf("%d", &n);
		for(int i = 1; i <= n; i++){
			scanf("%lld%lld", &a[i].x, &a[i].y);
		}
		long long ans = 0;
		for(int i = 1; i < n; i++){
			mp.clear();
			int cnt = 0;
			for(int j = i + 1; j <= n; j++){
				long long p = a[j].x - a[i].x, q = a[j].y - a[i].y;
				if (p < 0){
					p = -p, q = -q;
				}
				int flag = 1;
				if (q < 0){
					flag = -1;
					q = -q;
				}
				long long r = gcd(p, q);
				if (p == 0 && q == 0){
					cnt++;
				}
				else if (p == 0){
					auto Nico = mp.find(PLL(0, 1));
					if (Nico == mp.end()) mp[PLL(0,1)] = 1;
					else (Nico->second)++;
				}
				else if (q == 0){
					auto Nico = mp.find(PLL(1,0));
					if (Nico == mp.end()) mp[PLL(1,0)] = 1;
					else (Nico->second)++;
				}
				else{
					p /= r, q /= r;
					q *= flag;
					auto Nico = mp.find(PLL(p, q));
					if (Nico == mp.end()) mp[PLL(p,q)] = 1;
					else (Nico->second)++;
				}
			}
			long long now = 1;
			for(auto i = mp.begin(); i != mp.end(); i++)
				upd(now,(pw(i->second) - 1));
			upd(ans, now * pw(cnt) % MM - 1);
		}
		printf("%lld\n", ans);
	}
	return 0;
} 
