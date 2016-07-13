//凹四边形的特点：满足任意三边之和大于第四边，四条边不能全部相等。实际上任何凸四边形（除了四边相等的）都可以变成凹四边形

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

int main()
{
	int n, a[10001], ans = -1;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}
	sort(a, a + n);
	for (int i = n-4; i >=0; i--) {
		if (a[i] + a[i + 1] + a[i + 2] > a[i + 3]) {
			if ((a[i] != a[i + 1]) || a[i] != a[i + 2] || a[i] != a[i + 3]) {
				ans = a[i] + a[i + 1] + a[i + 2] + a[i + 3];
				break;
			}
			else {
				for (int j = i - 1; j >= 0; j--) {
					if (a[j] != a[i]) {
						ans = a[i] * 3 + a[j];
						break;
					}
				}
				break;
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}