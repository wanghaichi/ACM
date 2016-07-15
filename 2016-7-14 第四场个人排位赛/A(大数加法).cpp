// ACMdata.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<algorithm>
#include<cstdio>
#include <cstring>
#include <cmath>

using namespace std;

int len;
char ans[110];


void revers(char *s) {
	int l = strlen(s);
	int i = 0, j = l - 1;
	char a;
	while(i < j) {
		a = s[i];
		s[i] = s[j];
		s[j] = a;
		i++;
		j--;
	}
}

struct node {
	char s[110];
};
node hh[3];

void add(node n1, node n2) {
	int len1 = strlen(n1.s);
	int len2 = strlen(n2.s);

	int jin = 0;
	int i = 0, j = 0, k = 0;
	while (i < len1 && j < len2) {
		if (n1.s[i] + n2.s[j] - '0' - '0' + jin >= 10) {
			ans[k] = n1.s[i] + n2.s[j] + jin - '0' - 10;
			jin = 1;
		}
		else {
			ans[k] = n1.s[i] + n2.s[j] + jin - '0';
			jin = 0;
		}
		k++;
		i++;
		j++;
	}
	while (i < len1) {
		if (n1.s[i] - '0' + jin >= 10) {
			ans[k] = n1.s[i] + jin - 10;
			jin = 1;
		}
		else {
			ans[k] = n1.s[i] + jin;
			jin = 0;
		}
			
		i++;
		k++;
	}
	while (j < len2) {
		if (n2.s[j] - '0' + jin >= 10) {
			jin = 1;
			ans[k] = n2.s[j] + jin - 10;
		}
		else {
			ans[k] = n2.s[j] + jin;
			jin = 0;
		}
			
		j++;
		k++;
	}
	if (jin == 1) {
		ans[k++] = '1';
	}
	ans[k] = '\0';
}

bool solve() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				add(hh[i], hh[j]);
				if (strcmp(ans, hh[k].s) == 0) {
					return true;
				}
			}
		}
	}
	return false;
}




int main()
{
	node a, b, c;
	scanf("%s%s%s", a.s, b.s, c.s);
	revers(a.s);
	revers(b.s);
	revers(c.s);

	hh[0] = a;
	hh[1] = b;
	hh[2] = c;

	if (solve()) {
		puts("YES");
	}
	else {
		puts("NO");
	}

    return 0;
}

