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

int Next[1000001];
char s[1000001];
void getNext() {
	int j = 0, k = -1;
	Next[0] = -1;
	while (s[j] != '\0') {
		while (k != -1 && s[k] != s[j])
			k = Next[k];
		Next[++j] = ++k;
	}
}


int main()	
{
	int n ,cnt = 1;
	while (~scanf("%d", &n) && n) {
		scanf("%s", s);
		getNext();
		printf("Test case #%d\n", cnt++);
		for (int i = 1; i <= n; i++) {
			// 表示前缀完全由这个循环节构成，如果取模不等于0的话说明是aaaab这种情况，a是最小循环节,但只能构成某个字串
			if (Next[i] > 0 && i%(i-Next[i]) == 0) {
				printf("%d %d\n", i, i / (i - Next[i]));
			}
		}
		printf("\n");
	}



    return 0;
}
