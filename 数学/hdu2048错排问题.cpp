/***********************hdu2048************

求给定排列中错排出现的概率。

给定一个排列，若１－ｎ没有出现在原来的位置，则说明这是一个错排

这里算的贼麻烦，用的容斥原理

错排的递推公式为D(n) = (n - 1) * (D(n - 1) + D(n - 2))

最终的公式是：（欧拉大神做出来的）ｎ的错排数量为[(n!/e)+0.5] 这里[]表示向下取整

*******************************************/




#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

typedef long long ll;


ll zuhe(ll a, ll b){
	if(a > b - a)
		a = b - a;
	ll res = 1;
	for(ll i = 1; i <= a; i ++){
		res = res * (b - i + 1 )/i;
	}
	return res;
}

ll jie(ll n){
	ll res = 1;
	for(ll i = 1; i <= n; i ++){
		res *= i;
	}
	return res;
}

int main()
{
	ll n, ans, m;
	int T;
	scanf("%d", &T);
	while(T --){
		scanf("%I64d", &n);
		ans = 0;
		m = jie(n);
		for(int i = 0; i <= n; i ++){
			if(i & 1){
				ans -= (zuhe(i, n)*jie(n-i));
			}else{
				ans += (zuhe(i, n)*jie(n-i));
			}
		}
		double res = (double)ans / (double)m;
		res *= 100;
		printf("%.2f%c\n", res, '%');
	}
	return 0;
}

