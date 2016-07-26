#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e5+7;
const int mod = 1e9+7;

typedef long long ll;
ll mpow[33];
int main()
{
	mpow[0]=1;
	for(int i = 1; i <= 33; i ++){
		mpow[i] = 2*mpow[i-1]; 
	}
	int T, k;
	ll n, m;
	scanf("%d", &T);
	while(T --){
		scanf("%I64d%I64d", &n, &m);
		if(m >= 32)
			m = 32;
		
		int ans = 0;
		while(n > 0){
			k = 0;
			while(mpow[k] <= n && k <= m)
				k ++;
			k --;
			ans += n/mpow[k];
			n %= mpow[k];
		}
		printf("%d\n", ans);
		
	}
	return 0;
}
