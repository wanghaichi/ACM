// ACMdata.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<algorithm>
#include<cstdio>
#include <cstring>
#include <cmath>
#include <string>

using namespace std;

char s[110010], s1[220010];
int a[220010];
int manacher() {
	a[0] = 0;
	int ls = strlen(s1);
	int i = 0, j, ans = 0;
	while (i < ls) {
		while (i - a[i] > 0 && s1[i + a[i] + 1] == s1[i - a[i] - 1])
			a[i]++;
		ans = max(ans, a[i]);
		j = i + 1;
		while (j <= i + a[i] && i - a[i] != i + i - j - a[i + i - j]) {
			a[j] = min(a[i + i - j], i + a[i] - j);
			j++;
		}
		a[j] = max(0, i + a[i] - j);
		i = j;
	}
	return ans;
}

int main()
{
	while (~scanf("%s", s)) {
		int i = 0, j = 0;
		while (s[i] != '\0') {
			s1[j++] = '@';
			s1[j++] = s[i++];
		}
		s1[j++] = '@';
		s1[j++] = '\0';
		printf("%d\n", manacher());
		
	}
	return 0;
}