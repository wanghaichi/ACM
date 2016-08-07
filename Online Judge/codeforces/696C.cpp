/**************************************************************

AUTHOR: Hardy

TIME: 2016年 08月 07日 星期日 13:06:03 CST

ID:

TYPE:

DETAIL:

TACTICS:

***************************************************************/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a > b ? b : a)
#define CL(a) memset(a, 0, sizeof(a));

using namespace std;

typedef long long ll;

const int inf = 1e9+7;
const int mod = 1e9+7;
const int maxn = 1e6+7, maxe = 1e6+7, maxv = 1e6+7;

ll mul(ll a, ll b){
	ll res = 1;
	while( b > 0 ){
		if(b&1)res *= a;
		res %= mod;
		a *= a;
		a %= mod;
		b >>= 1;
	}
	return res;
}

struct mat{
	ll m[2][2];
	void clear(){
		CL(m);
	}
	void init1(){
		for(int i = 0; i < 2; i ++){
			for(int j = 0; j < 2; j ++){
				m[i][j] = (i == j);
			}
		}
	}
	void init(){
		m[0][0] = m[0][1] = 1;
		m[1][0] = 2; m[1][1] = 0;
	}
	mat(ll a, ll b, ll c, ll d){
		m[0][0] = a; m[0][1] = b; m[1][0] = c; m[1][1] = d;
	}
	mat(){}
	mat operator * (const mat& m1){
		mat res;
		res.clear();
		for(int i = 0; i < 2; i ++){
			for(int j = 0; j < 2; j ++){
				for(int k = 0; k < 2; k ++){
					res.m[i][j] += m[i][k] * m1.m[k][j];
					res.m[i][j] %= mod;
				}
			}
		}
		return res;
	}
};

mat mmul(mat m, ll a){
	mat res;
	res.init1();
	while(a > 0){
		if(a&1)res = res * m;
		m = m * m;
		a >>= 1;
	}
	return res;	
}

int main()
{
	int n;
	ll tmp, b = 1;
	scanf("%d", &n);
	mat mm, res;
	mm.init();
	res.m[0][0] = res.m[0][1] = res.m[1][0] = 1;
	res.m[1][1] = 0;
	for(int i = 0; i < n; i ++){
		scanf("%lld", &tmp);
		if(i == 0)
			b = mul(2, tmp);
		else{
			b = mul(b, tmp);
		}
		mm = mmul(mm, tmp);
	}
	res = res * mm;
	b = b * mul(2, mod - 2);
	b %= mod;
	ll a = res.m[1][0] - res.m[1][1];
	a = (a + mod) % mod;
	a *= mul(2, mod-2);
	a %= mod;
	/*ll c = __gcd(a, b);
	a *= mul(c, mod-2);
	a %= mod;
	b *= mul(c, mod-2);
	b %= mod;*/
	printf("%lld/%lld\n", a , b);
	return 0;
}








