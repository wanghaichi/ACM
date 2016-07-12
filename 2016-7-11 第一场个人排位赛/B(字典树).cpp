//字典树静态建树

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

const int N = 1000007;
const int mod = 1000000007;

struct Tr {
	int s[26];
}a[N];

int cnt, root;

int newNode()
{
	memset(a[cnt].s, -1, sizeof(a[cnt].s));
	return cnt++;
}

int cal(char *s) {
	int cur = root;
	for (int i = 0; s[i]; i++) {
		int t = s[i] - 'a';
		if (a[cur].s[t] == -1) {
			return i + 1;
		}
		cur = a[cur].s[t];
	}
	return strlen(s);
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
	}
}

void init() {
	cnt = 0;
	root = newNode();
}

char s[N]; //开小了会超时！
int main()
{
	int T, n, ct = 1;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		init();
		ll ans = 0;
		while (n--) {
			scanf("%s", s);
			ans += cal(s);
			insert(s);
		}
		printf("Case #%d: %I64d\n", ct++, ans);
	}
	return 0;
}