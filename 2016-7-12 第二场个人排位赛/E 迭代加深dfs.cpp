//迭代加深的dfs，每次深度递增一层

#include "stdafx.h"
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <map>
#define inf 1000000000

using namespace std;
typedef long long ll;

const int mod = 1000000007;
const int N = 16384;
int mind, b[10];
int n, a[21], ans = 0, vis[10], flag;

void canSplited(int c, int sum, int index) {
	if (flag == 1)
		return;
	if (c == sum) {
		flag = 1;
		return;
	}
	if (c < sum)
		return;
	for (int i = index; i <= mind; i++) {
		if (!vis[i]) {
			vis[i] = 1;
			canSplited(c, sum + b[i], index+1);
			vis[i] = 0;
		}
	}
}

void dfs(int step) {
	if (ans > 0)
		return;
	if (step == mind) {
		int i;
		for (i = 0; i < n; i++) {
			memset(vis, 0, sizeof(vis));
			flag = 0;
			canSplited(a[i], 0, 1);
			if (flag == 1) {
				continue;
			}
			else {
				break;
			}
		}
		if (i == n) {
			ans = step;
		}
		return;
	}
	for (int i = b[step]; i <= 50; i++) { //数据量小，直接暴力搜索
		b[step + 1] = i;
		dfs(step + 1);
	}
}



int main()
{
	scanf("%d", &n);
	memset(a, 0, sizeof(a));
	for(int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}
	b[0] = 1;
	for (mind = 1; mind <= 5; mind++) {
		dfs(0);
	}
	if (ans == 0)
		printf("6\n");
	else
		printf("%d\n", ans);

	return 0;
}