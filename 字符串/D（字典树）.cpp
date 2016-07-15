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

const int N = 1000000;

struct Tr {
	int s[26], num;
}a[N];

int cnt, root;

int newNode()
{
	memset(a[cnt].s, -1, sizeof(a[cnt].s));
	a[cnt].num = 0;
	return cnt++;
}

int cal(char *s) {
	int cur = root;
	for (int i = 0; s[i]; i++) {
		int t = s[i] - 'a';
		cur = a[cur].s[t];
		if (cur == -1)
			return 0;
		if (s[i + 1] == '\0')
			return a[cur].num;
	}
}

void insert(char *s)
{
	int cur = root;
	for (int i = 0; s[i]; i++) {
		int t = s[i] - 'a';
		if (a[cur].s[t] == -1) {
			a[cur].s[t] = newNode();
		}
		cur = a[cur].s[t];
		a[cur].num++;
	}
}

void init() {
	cnt = 0;
	root = newNode();
}

int main()
{
	init();
	char s[20];
	while (gets_s(s) && *s) {
		insert(s);
	}
	while (gets_s(s)) {
		printf("%d\n", cal(s));
	}

	return 0;
}