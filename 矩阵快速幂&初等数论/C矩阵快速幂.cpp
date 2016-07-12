//矩阵快速幂
#include "stdafx.h"
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cmath>
#include <cstring>
#define inf 10000000000

using namespace std;

typedef long long ll;

const int N = 2;
const int mod = 10000;

struct mat {
	int m[N][N];
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
				c.m[i][j] += a.m[i][k] * b.m[k][j];
				c.m[i][j] %= mod;
			}
				
	return c;
}

mat multi(mat a,int n) {
	mat c;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			c.m[i][j] = (i == j);
	if (n == 0) {
		return c;
	}
	while (n > 0) { //与乘法快速幂类似 
		if (n & 1) c = mul(c, a);
		a = mul(a,a);
		n >>= 1;
	}
	return c;
}

int main()
{
	int n;
	while (~scanf("%d", &n) && n != -1) {
		mat f;
		f.m[0][0] = 1; f.m[0][1] = 1; f.m[1][0] = 1; f.m[1][1] = 0;
		mat c;
		c = multi(f, n);
		printf("%d\n", c.m[0][1]);
	}
	return 0;
}