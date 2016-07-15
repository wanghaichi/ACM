// ACMdata.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<algorithm>
#include<cstdio>
#include <cstring>
#include <cmath>

using namespace std;

int main()
{
	char s[100001];
	int num0 = 0, num1 = 0;
	scanf("%s", s);
	for (int i = 0; s[i]; i++) {
		if (s[i] == '0')
			num0++;
		else
			num1++;
	}
	printf("%d\n", min(num0, num1));
    return 0;
}

