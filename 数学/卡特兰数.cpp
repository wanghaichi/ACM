/**********卡特兰数应用****************

对于包含ｎ个Ｘ和ｎ个Ｙ的字符串，满足任一前缀中Ｘ的数量大于Ｙ的数量的个数

卡特兰数公式：Cn = (2n)! / ((n+1)! * n!)

递推公式：Cn = (2 * (2n - 1) / (n + 1)) * Cn-1   C0 = 1

***************************************/



#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

typedef long long ll;
const ll mod = 1e9+7;

ll mul(ll a, ll b){
	ll res = 1;
	while(b > 0){
		if(b&1) res *= a;
		res %= mod;
		a *= a;
		a %= mod;
		b >>= 1;
	}
	res %= mod;
	return res;
}
//直接使用公式计算
ll solve(ll n){
	ll res = 1;
	for(ll i = 1; i <= n; i ++){
		res *= (n+i);
		res %= mod;
		res *= mul(i, mod - 2);
		res %= mod;
	}
	res *= mul(n+1, mod - 2);
	res %= mod;
	return res;
}
ll ans[10110];

int main()
{
	ans[0] = 1;
	//利用递推公式打表
	for(int i = 1; i <= 10000; i ++){
		ans[i] = ans[i-1] * 2 * (2 * i - 1);
		ans[i] %= mod;
		ans[i] *= mul(i+1, mod - 2);
		ans[i] %= mod;
	}
	ll n;
	while(~scanf("%lld", &n)){
		printf("%lld\n", ans[n]);
	}
	return 0;
}
