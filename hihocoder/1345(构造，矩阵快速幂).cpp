// ACMdata.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<algorithm>
#include<cstdio>
#include <cstring>
#include <cmath>
#include <string>
#include <map>
#include <vector>
#include <queue>
using namespace std;
typedef long long ll;

const int N = 2;
const int mod = 1000000007;

struct mat {
	ll m[N][N];
	void init(ll k1, ll k2) {  //构造an = k2 * an-1 + k1 * an-2 这样一个矩阵
		m[0][0] = k1;
		m[0][1] = 1;
		m[1][0] = k2;
		m[1][1] = 0;
	}
	void init() {
		memset(m, 0, sizeof(m));
	}
};

mat mul(mat a, mat b) {
	mat c;
	c.init();
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			for (int k = 0; k < N; k++) {
				c.m[i][j] += (a.m[i][k] * b.m[k][j]) % mod;
				c.m[i][j] %= mod;
			}

	return c;
}

mat multi(mat a, ll n) {
	mat c;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			c.m[i][j] = (i == j);
	if (n == 0) {
		return c;
	}
	while (n > 0) { //与乘法快速幂类似 
		if (n & 1) c = mul(c, a);
		a = mul(a, a);
		n >>= 1;
	}
	return c;
}

ll mmul(ll a, ll b) {
	ll res = 1;
	while (b > 0) {
		if (b & 1) {
			res *= a;
			res %= mod;
		}
		a = a * a;
		a %= mod;
		b >>= 1;
	}
	return res;
}

int main() 
{
	ll k1, k2, x, y, ax, ay, z, a1, a2, k11, k12, k21, k22, tmp, az;
	scanf("%lld%lld%lld%lld%lld%lld%lld", &k1, &k2, &x, &y, &ax, &ay, &z);
	mat tm; 
	tm.init(k1, k2);
	mat mat1, mat2, mat3;
	mat1 = multi(tm, x - 2);
	tm.init(k1, k2);
	mat2 = multi(tm, y - 2);
	k11 = mat1.m[0][0];
	k12 = mat1.m[1][0];
	k21 = mat2.m[0][0];
	k22 = mat2.m[1][0];
	a2 = (ax*k22%mod - ay*k12%mod + mod) % mod;
	tmp = (k11*k22%mod - k21*k12%mod + mod) % mod;
	a2 *= mmul(tmp, mod - 2);
	a2 %= mod;

	a1 = (ax*k21%mod - ay*k11%mod + mod) % mod;
	tmp = (k21*k12%mod - k11*k22%mod + mod) % mod;
	a1 *= mmul(tmp, mod - 2);
	a1 %= mod;

	tm.init(k1, k2);
	mat3 = multi(tm, z - 2);
	az = a2*mat3.m[0][0] % mod + a1*mat3.m[1][0] % mod;
	az %= mod;

	printf("%lld\n", az);

	return 0;
}