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
const int N = 15;

int dp[(1 << N)], tmp; 

bool judge(int x, int y, int z) {
	if (x + y > z && x + z > y && y + z > x) 
		return true;
	return false;
}


int main()	
{
	int n, a[N], tmp;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}
	if (n <= 2)
		puts("0");
	else {
		memset(dp, 0, sizeof(dp));
		for (int i = 0; i < (1 << n); i++) {
			for (int j = 0; j < n; j++) {
				for (int k = j + 1; k < n; k++) {
					for (int l = k + 1; l < n; l++) {
						//判断当前有效位，进行转移，即那些为零的位，转移到下一种状态
						//dp[j] = max(dp[j], dp[k] + 1); (k | 1 << a | 1 << b | 1 << c = j)表示a，b，c位置变成1
						if (!((i >> j) & 1) && !((i >> k) & 1) && !((i >> l) & 1)) { 
							if (judge(a[j], a[k], a[l])) {
								dp[i | (1 << j) | (1 << k) | (1 << l)] = max(dp[i | (1 << j) | (1 << k) | (1 << l)], dp[i] + 1);
							}
						}
					}
				}
			}
		}
		printf("%d\n", dp[(1 << n) - 1]);
	}
    return 0;
}
