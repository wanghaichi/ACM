// ACMdata.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<algorithm>
#include<cstdio>
#include <cstring>
#include <cmath>

using namespace std;
typedef long long ll;
ll ma[110][110], s[110], w[110], p;

int main()
{
	ll n;
	scanf("%I64d", &n);
	if (n == 1)
		printf("0\n");
	else {
		p = 0;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				scanf("%I64d", &ma[i][j]);
				if (i + j == n - 1) {
					p += ma[i][j];
				}
			}
		for (int i = 0; i < n; i++) {
			s[i] = 0;
			w[i] = 0;
			for (int j = 0; j < n; j++) {
				s[i] += ma[i][j];
				w[i] += ma[j][i];
			}
		}
		if (n % 2 == 0) {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (i == j) {
						printf("%I64d ", p - s[i]);
					}
					else {
						printf("%I64d ", ma[i][j]);
					}
				}
				printf("\n");
			}
		}
		else {
			ll ans = 0, x0;
			for (int i = 1; i < n; i++) {
				ans += (s[0] - s[i]);
			}
			x0 = (s[0] - ans) / (n - 1);
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (i == j) {
						printf("%I64d ", s[0] - s[i] + x0);
					}
					else {
						printf("%I64d ", ma[i][j]);
					}
				}
				printf("\n");
			}
		}
	}




    return 0;
}

