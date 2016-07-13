#include "stdafx.h"
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <map>
#define inf 10000000000

using namespace std;
typedef long long ll;
int a[10], n, ans;

void dfs(int cur, int sum) {
	int shu[6], ct = 0, tmp = sum;
	while (tmp > 0) {
		shu[ct++] = tmp % 10;
		tmp /= 10;
	}
	sort(shu, shu + ct);
	if (cur == n) {
		int cr = 0;
		for (int i = 0, ep = 1; i < ct; i++, ep *= 10) {
			cr += shu[i] * ep;
		}
		ans = max(ans, cr);
		return;
	}
	do {
		int cr = 0;
		for (int i = 0, ep = 1; i < ct; i++, ep *= 10) {
			cr += shu[i] * ep;
		}
		dfs(cur + 1, a[cur] + cr);
	} while (next_permutation(shu, shu + ct)); //先对数组进行排序，快速获取全排列的方法
}



int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}
	ans = 0;
	dfs(0, 0);
	printf("%d\n", ans);
	return 0;
}